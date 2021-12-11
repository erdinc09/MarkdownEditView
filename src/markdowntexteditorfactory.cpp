/*
 * Copyright (c) 2020-2021 Ahmet Erdinç Yılmaz -- <ahmeterdinc09@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 */

#include "markdowntexteditorfactory.h"

#include <coreplugin/editormanager/editormanager.h>
#include <texteditor/textdocument.h>
#include <texteditor/texteditor.h>
#include <texteditor/texteditoractionhandler.h>

#include <QDir>
#include <QDirIterator>
#include <QFile>
#include <QFileInfo>
#include <QSettings>
#include <QString>
#include <QTextCodec>
#include <QVariant>
#include <stdexcept>

#include "eb/eventbus.h"
#include "markdowneditviewconstants.h"
#include "markdowntexteditorwidget.h"
#include "textchangedevent.h"

using EditorManager = Core::EditorManager;

namespace MarkdownEditView {
namespace Internal {

static TextEditor::TextDocument* createMarkdownDocument();

MarkdownTextEditorFactory::MarkdownTextEditorFactory() {
  setId(Constants::MARKDOWN_EDITOR_ID);
  setDisplayName("Markdown Edit & View");
  addMimeType(Constants::MARKDOWN_MIME_TYPE);
  setEditorCreator([]() { return new MarkdownTextEditor; });
  setEditorWidgetCreator([]() { return new MarkdownTextEditorWidget{}; });
  setDocumentCreator(createMarkdownDocument);

  setEditorActionHandlers(TextEditor::TextEditorActionHandler::None);
  ensureMarkDownEditViewHomeFolderExists();

  connect(EditorManager::instance(),
          SIGNAL(currentEditorChanged(Core::IEditor*)), this,
          SLOT(currentEditorChanged(Core::IEditor*)));
}

static TextEditor::TextDocument* createMarkdownDocument() {
  auto doc = new TextEditor::TextDocument{Constants::MARKDOWN_EDITOR_ID};
  doc->setId(Constants::MARKDOWN_EDITOR_ID);
  doc->setMimeType(Constants::MARKDOWN_MIME_TYPE);
  qDebug() << "createMarkdownDocument()";
  return doc;
}

static bool fileExtensionBelongsToFilesInQrc(QFile& out) {
  return out.fileName().endsWith(".html") || out.fileName().endsWith(".css") ||
         out.fileName().endsWith(".md") || out.fileName().endsWith(".png") ||
         out.fileName().endsWith(".jpg") || out.fileName().endsWith(".txt") ||
         out.fileName().endsWith(".js") || out.fileName().endsWith(".ini");
}

static bool doesResorceFolderNeedUpdate(QDir& markdownEditViewDir);

// From the files that are loaded from qrc, the local files can not be reached.
// In Qt5 there was not a problem, I think it is a bug. Moreover In
// QWebEnginePage, it is already documented that "By default, local schemes like
// file:// and qrc:// are considered to be in the same security origin, and can
// access each other's resources." it can not. Threfore, we first export qrc
// file in home folder as a workaround.
void MarkdownTextEditorFactory::ensureMarkDownEditViewHomeFolderExists() {
  auto markdownEditViewDir =
      QDir(QDir::home().absolutePath() + QDir::separator() +
           Constants::MARKDOWNEDITVIEW_HOME_FOLDER);
  if (doesResorceFolderNeedUpdate(markdownEditViewDir)) {
    QDirIterator it(Constants::MARKDOWNEDITVIEW_QRC_PREFIX,
                    QDirIterator::Subdirectories);
    while (it.hasNext()) {
      auto filePathRelToQrc = it.next();
      qDebug() << "it.next() = " + filePathRelToQrc;
      QFile out(markdownEditViewDir.absoluteFilePath(filePathRelToQrc.mid(
          Constants::MARKDOWNEDITVIEW_QRC_PREFIX.length() + 1)));
      auto outDir = QFileInfo(out).dir();
      qDebug() << "entry:" << out.fileName();
      if (!outDir.exists()) {
        qDebug() << "creating dir: " << outDir.absolutePath();
        if (!QDir::home().mkpath(outDir.absolutePath())) {
          qDebug() << "error creating dir: " << outDir.absolutePath();
        }
      }
      if (fileExtensionBelongsToFilesInQrc(out) &&
          out.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "writing:" << out.fileName();
        QTextStream stream(&out);
        QFile in(filePathRelToQrc);
        if (in.open(QIODevice::ReadOnly | QIODevice::Text)) {
          stream << in.readAll();
          in.close();
        }
        out.close();
      } else {
        qDebug() << "file extension does not belong to qrc or cannot open: "
                 << out.fileName();
      }
    }
  }
}

static bool doesResorceFolderNeedUpdate(QDir& markdownEditViewDir) {
  auto resourceVersionInUser =
      QSettings(markdownEditViewDir.absoluteFilePath("version.ini"),
                QSettings::IniFormat)
          .value("resource/version", "-1")
          .toInt();
  qDebug() << "resource version in user: " << resourceVersionInUser;

  auto resourceVersionInLibrary =
      QSettings(":/markdowneditview/version.ini", QSettings::IniFormat)
          .value("resource/version", "-1")
          .toInt();
  qDebug() << "resource version in library: " << resourceVersionInLibrary;

  if (resourceVersionInLibrary < 0) {
    throw std::runtime_error("invalid resourceVersion in library");
  }

  return resourceVersionInLibrary != resourceVersionInUser;
}

void MarkdownTextEditorFactory::currentEditorChanged(
    Core::IEditor* editor) const {
  MarkdownTextEditorWidget* currentWidget;
  if (editor != nullptr &&
      (currentWidget =
           dynamic_cast<MarkdownTextEditorWidget*>(editor->widget()))) {
    qDebug("sending non empty text event");
    aeb::postEvent(TextChangedEvent{currentWidget->document()->toPlainText(),
                                    QString{currentWidget->textDocument()
                                                ->filePath()
                                                .absolutePath()
                                                .toString()}});

    qDebug() << "editor->document()->id(): " << editor->document()->id();
  } else {
    qDebug("sending empty text event");
    aeb::postEvent(TextChangedEvent{});
  }
}

const QString MarkdownTextEditorFactory::getText() const {
  auto currentTexteditor = dynamic_cast<MarkdownTextEditorWidget*>(
      MarkdownTextEditorWidget::currentTextEditorWidget());
  return currentTexteditor != nullptr
             ? currentTexteditor->document()->toPlainText()
             : QString{};
}

const QString MarkdownTextEditorFactory::getPath() const {
  auto currentTexteditor = dynamic_cast<MarkdownTextEditorWidget*>(
      MarkdownTextEditorWidget::currentTextEditorWidget());
  return currentTexteditor != nullptr
             ? QString{currentTexteditor->textDocument()
                           ->filePath()
                           .absolutePath()
                           .toString()}
             : QString{};
}

int MarkdownTextEditorFactory::getFirstLineNumberInEditor() const {
  auto currentTexteditor = dynamic_cast<MarkdownTextEditorWidget*>(
      MarkdownTextEditorWidget::currentTextEditorWidget());
  return currentTexteditor != nullptr
             ? currentTexteditor->getFirstNonEmptyLineNumer()
             : -1;
}

MarkdownTextEditorFactory::~MarkdownTextEditorFactory() {
  auto editorManager = EditorManager::instance();
  disconnect(editorManager, &::Core::EditorManager::currentEditorChanged, this,
             &::MarkdownEditView::Internal::MarkdownTextEditorFactory::
                 currentEditorChanged);
}

}  // namespace Internal
}  // namespace MarkdownEditView
