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

#include "eb/eventbus.h"
#include "markdowneditviewconstants.h"
#include "markdowntexteditorwidget.h"
#include "textchangedevent.h"

using EditorManager = Core::EditorManager;

namespace MarkdownEditView {
namespace Internal {

MarkdownTextEditorFactory::MarkdownTextEditorFactory() {
  setId(Constants::MARKDOWN_EDITOR_ID);
  setDisplayName("Markdown Edit & View");
  addMimeType("text/plain");
  addMimeType("text/markdown");

  setDocumentCreator([]() {
    return new TextEditor::TextDocument(Constants::MARKDOWN_EDITOR_ID);
  });
  setEditorCreator([]() { return new TextEditor::BaseTextEditor; });

  setEditorWidgetCreator([=]() { return new MarkdownTextEditorWidget{}; });

  auto editorManager = EditorManager::instance();
  connect(editorManager, &EditorManager::currentEditorChanged, this,
          &::MarkdownEditView::Internal::MarkdownTextEditorFactory::
              currentEditorChanged);
}

void MarkdownTextEditorFactory::currentEditorChanged(
    Core::IEditor* editor) const {
  MarkdownTextEditorWidget* currentWidget;
  if (editor != nullptr &&
      (currentWidget =
           dynamic_cast<MarkdownTextEditorWidget*>(editor->widget()))) {
    aeb::postEvent(TextChangedEvent{currentWidget->document()->toPlainText(),
                                    QString{currentWidget->textDocument()
                                                ->filePath()
                                                .absolutePath()
                                                .toString()}});
  } else {
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
             ? currentTexteditor->firstVisibleBlockNumber() + 1
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
