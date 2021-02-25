/*
 *
 *
 * Copyright (c) 2014-2021 Patrizio Bekerle -- <patrizio@bekerle.com>
 * (Some methods are taken from qmarkdowntextedit)
 * Copyright (c) 2020-2021 Ahmet Erdinç Yılmaz -- <ahmeterdinc09@gmail.com>
 *
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

#include "markdowntexteditorwidget.h"

#include <texteditor/textdocument.h>

#include <QDebug>
#include <QDesktopServices>
#include <QGuiApplication>
#include <QScrollBar>

#include "eb/eventbus.h"
#include "firstlinenumberineditorchangedevent.h"
#include "textchangedevent.h"

namespace MarkdownEditView {
namespace Internal {

MarkdownTextEditorWidget::MarkdownTextEditorWidget()
    : highlighter{new MarkdownHighlighter} {
  installEventFilter(this);
  viewport()->installEventFilter(this);
}

void MarkdownTextEditorWidget::finalizeInitialization() {
  setMarksVisible(true);
  setLineSeparatorsAllowed(true);
  textDocument()->setSyntaxHighlighter(highlighter.data());
  setCodeFoldingSupported(false);
}

void MarkdownTextEditorWidget::openFinishedSuccessfully() {
  TextEditorWidget::openFinishedSuccessfully();

  connect(textDocument(),
          &TextEditor::TextDocument::contentsChangedWithPosition, this,
          &MarkdownTextEditorWidget::contentsChangedWithPosition);

  connect(verticalScrollBar(), SIGNAL(valueChanged(int)), this,
          SLOT(verticalScrollbarValueChanged(int)));

  aeb::postEvent<>(TextChangedEvent{
      document()->toPlainText(),
      QString{textDocument()->filePath().absolutePath().toString()}});
}

void MarkdownTextEditorWidget::contentsChangedWithPosition(int, int, int) {
  aeb::postEvent<>(TextChangedEvent{
      document()->toPlainText(),
      QString{textDocument()->filePath().absolutePath().toString()}});
}

void MarkdownTextEditorWidget::verticalScrollbarValueChanged(int) {
  aeb::postEvent<>(
      FirstLineNumberInEditorChangedEvent{firstVisibleBlockNumber() + 1});
}

bool MarkdownTextEditorWidget::eventFilter(QObject *obj, QEvent *event) {
  if (event->type() == QEvent::KeyPress) {
    auto *keyEvent = static_cast<QKeyEvent *>(event);
    if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) {
      return handleReturnEntered();
    }
    // set cursor to pointing hand if control key was pressed
    else if (keyEvent->modifiers().testFlag(Qt::ControlModifier)) {
      QWidget *viewPort = this->viewport();
      viewPort->setCursor(Qt::PointingHandCursor);
    }

  } else if (event->type() == QEvent::KeyRelease) {
    auto *keyEvent = static_cast<QKeyEvent *>(event);

    // reset cursor if control key was released
    if (keyEvent->key() == Qt::Key_Control) {
      QWidget *viewPort = viewport();
      viewPort->setCursor(Qt::IBeamCursor);
    }

    return false;
  } else if (event->type() == QEvent::MouseButtonRelease) {
    auto *mouseEvent = static_cast<QMouseEvent *>(event);
    // track `Ctrl + Click` in the text edit
    if ((obj == this->viewport()) && (mouseEvent->button() == Qt::LeftButton) &&
        (QGuiApplication::keyboardModifiers() == Qt::ExtraButton24)) {
      // open the link (if any) at the current position
      // in the noteTextEdit
      openLinkAtCursorPosition();
      return true;
    }
  }
  return QPlainTextEdit::eventFilter(obj, event);
}

bool MarkdownTextEditorWidget::handleReturnEntered() {
  QTextCursor cursor = this->textCursor();
  int position = cursor.position();

  cursor.movePosition(QTextCursor::StartOfBlock, QTextCursor::KeepAnchor);
  QString currentLineText = cursor.selectedText();

  // if return is pressed and there is just a list symbol then we want to
  // remove the list symbol
  // Valid listCharacters: '+ ', '-' , '* ', '+ [ ] ', '+ [x] ', '- [ ] ', '-
  // [x] ', '* [ ] ', '* [x] '.
  QRegularExpression regex("^(\\s*)([+|\\-|\\*] \\[(x| )\\]|[+\\-\\*])(\\s+)$");
  QRegularExpressionMatchIterator iterator = regex.globalMatch(currentLineText);
  if (iterator.hasNext()) {
    cursor.removeSelectedText();
    return true;
  }

  // Check if we are in a list.
  // We are in a list when we have '* ', '- ' or '+ ', possibly with preceding
  // whitespace. If e.g. user has entered '**text**' and pressed enter - we
  // don't want do anymore list-stuff.
  QChar char0 = currentLineText.trimmed()[0];
  QChar char1 = currentLineText.trimmed()[1];
  bool inList =
      ((char0 == '*' || char0 == '-' || char0 == '+') && char1 == ' ');

  if (inList) {
    // if the current line starts with a list character (possibly after
    // whitespaces) add the whitespaces at the next line too
    // Valid listCharacters: '+ ', '-' , '* ', '+ [ ] ', '+ [x] ', '- [ ] ', '-
    // [x] ', '* [ ] ', '* [x] '.
    regex =
        QRegularExpression("^(\\s*)([+|\\-|\\*] \\[(x| )\\]|[+\\-\\*])(\\s+)");
    iterator = regex.globalMatch(currentLineText);
    if (iterator.hasNext()) {
      QRegularExpressionMatch match = iterator.next();
      QString whitespaces = match.captured(1);
      QString listCharacter = match.captured(2);
      QString whitespaceCharacter = match.captured(4);

      cursor.setPosition(position);
      cursor.insertText("\n" + whitespaces + listCharacter +
                        whitespaceCharacter);

      // scroll to the cursor if we are at the bottom of the document
      ensureCursorVisible();
      return true;
    }
  }

  return false;
}

/**
 * @brief Opens the link (if any) at the current cursor position
 */
bool MarkdownTextEditorWidget::openLinkAtCursorPosition() {
  QTextCursor cursor = this->textCursor();
  const int clickedPosition = cursor.position();

  // select the text in the clicked block and find out on
  // which position we clicked
  cursor.movePosition(QTextCursor::StartOfBlock);
  const int positionFromStart = clickedPosition - cursor.position();
  cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);

  const QString selectedText = cursor.selectedText();

  // find out which url in the selected text was clicked
  const QString urlString =
      getMarkdownUrlAtPosition(selectedText, positionFromStart);
  const QUrl url = QUrl(urlString);
  const bool isRelativeFileUrl =
      urlString.startsWith(QLatin1String("file://.."));
  const bool isLegacyAttachmentUrl =
      urlString.startsWith(QLatin1String("file://attachments"));

  if ((url.isValid() && isValidUrl(urlString)) || isRelativeFileUrl ||
      isLegacyAttachmentUrl) {
    openUrl(urlString);
    return true;
  }

  return false;
}

/**
 * Handles clicked urls
 *
 * examples:
 * - <https://www.qownnotes.org> opens the webpage
 * - <file:///path/to/my/file/QOwnNotes.pdf> opens the file
 *   "/path/to/my/file/QOwnNotes.pdf" if the operating system supports that
 *  handler
 */
void MarkdownTextEditorWidget::openUrl(const QString &urlString) {
  qDebug() << "MarkdownTextEditorWidget " << __func__
           << " - 'urlString': " << urlString;

  QDesktopServices::openUrl(QUrl(urlString));
}

/**
 * Checks if urlString is a valid url
 *
 * @param urlString
 * @return
 */
bool MarkdownTextEditorWidget::isValidUrl(const QString &urlString) {
  const QRegularExpressionMatch match =
      QRegularExpression(R"(^\w+:\/\/.+)").match(urlString);
  return match.hasMatch();
}

/**
 * @brief Returns the markdown url at position
 * @param text
 * @param position
 * @return url string
 */
QString MarkdownTextEditorWidget::getMarkdownUrlAtPosition(const QString &text,
                                                           int position) {
  QString url;

  // get a map of parsed markdown urls with their link texts as key
  const QMap<QString, QString> urlMap = parseMarkdownUrlsFromText(text);
  QMap<QString, QString>::const_iterator i = urlMap.constBegin();
  for (; i != urlMap.constEnd(); ++i) {
    const QString &linkText = i.key();
    const QString &urlString = i.value();

    const int foundPositionStart = text.indexOf(linkText);

    if (foundPositionStart >= 0) {
      // calculate end position of found linkText
      const int foundPositionEnd = foundPositionStart + linkText.size();

      // check if position is in found string range
      if ((position >= foundPositionStart) && (position <= foundPositionEnd)) {
        url = urlString;
        break;
      }
    }
  }

  return url;
}

/**
 * @brief Returns a map of parsed markdown urls with their link texts as key
 *
 * @param text
 * @return parsed urls
 */
QMap<QString, QString> MarkdownTextEditorWidget::parseMarkdownUrlsFromText(
    const QString &text) {
  QMap<QString, QString> urlMap;
  QRegularExpression regex;
  QRegularExpressionMatchIterator iterator;

  // match urls like this: <http://mylink>
  //    re = QRegularExpression("(<(.+?:\\/\\/.+?)>)");
  regex = QRegularExpression(QStringLiteral("(<(.+?)>)"));
  iterator = regex.globalMatch(text);
  while (iterator.hasNext()) {
    QRegularExpressionMatch match = iterator.next();
    QString linkText = match.captured(1);
    QString url = match.captured(2);
    urlMap[linkText] = url;
  }

  // match urls like this: [this url](http://mylink)
  //    QRegularExpression re("(\\[.*?\\]\\((.+?:\\/\\/.+?)\\))");
  regex = QRegularExpression(R"((\[.*?\]\((.+?)\)))");
  iterator = regex.globalMatch(text);
  while (iterator.hasNext()) {
    QRegularExpressionMatch match = iterator.next();
    QString linkText = match.captured(1);
    QString url = match.captured(2);
    urlMap[linkText] = url;
  }

  // match urls like this: http://mylink
  regex = QRegularExpression(R"(\b\w+?:\/\/[^\s]+[^\s>\)])");
  iterator = regex.globalMatch(text);
  while (iterator.hasNext()) {
    QRegularExpressionMatch match = iterator.next();
    QString url = match.captured(0);
    urlMap[url] = url;
  }

  // match reference urls like this: [this url][1] with this later:
  // [1]: http://domain
  regex = QRegularExpression(R"(\[(.*?)\]\[(.+?)\])");
  iterator = regex.globalMatch(text);
  while (iterator.hasNext()) {
    QRegularExpressionMatch match = iterator.next();
    QString linkText = match.captured(1);
    QString referenceId = match.captured(2);

    // search for the referenced url in the whole text edit
    QRegularExpression refRegExp(QStringLiteral("\\[") +
                                 QRegularExpression::escape(referenceId) +
                                 QStringLiteral("\\]: (.+?)"));
    QRegularExpressionMatch urlMatch = refRegExp.match(toPlainText());

    if (urlMatch.hasMatch()) {
      QString url = urlMatch.captured(1);
      urlMap[linkText] = url;
    }
  }

  return urlMap;
}

}  // namespace Internal
}  // namespace MarkdownEditView
