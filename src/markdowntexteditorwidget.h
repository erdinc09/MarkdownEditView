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

#ifndef MARKDOWNTEXTEDITORWIDGET_H
#define MARKDOWNTEXTEDITORWIDGET_H

#include <texteditor/texteditor.h>

#include <QMap>
#include <QPointer>
#include <QSharedPointer>
#include <QString>
#include <QWheelEvent>

#include "eb/eventlistener.h"
#include "firstlinenumberinpreviewchangedevent.h"
#include "markdownhighlighter.h"

namespace MarkdownEditView {
namespace Internal {

class MarkdownTextEditorWidget
    : public TextEditor::TextEditorWidget,
      private aeb::EventListener<FirstLineNumberInPreviewChangedEvent> {
  Q_OBJECT

 public:
  MarkdownTextEditorWidget();

  void openFinishedSuccessfully() override;
  void finalizeInitialization() override;
  bool eventFilter(QObject *obj, QEvent *event) override;
  int getFirstNonEmptyLineNumer() const;

 private slots:
  void contentsChangedWithPosition(int position, int charsRemoved,
                                   int charsAdded);
  void verticalScrollbarValueChanged(int value);

 private:
  bool handleReturnEntered();
  bool openLinkAtCursorPosition();
  QString getMarkdownUrlAtPosition(const QString &text, int position);
  QMap<QString, QString> parseMarkdownUrlsFromText(const QString &text);
  void handleEvent(const FirstLineNumberInPreviewChangedEvent &event) override;
  bool isValidUrl(const QString &urlString);
  void openUrl(const QString &urlString);

  int firstLineNumberInPreviewChangedEventCount = 0;
  int lastScrollValueSet = 0;
  QSharedPointer<MarkdownHighlighter> highlighter;
};

}  // namespace Internal
}  // namespace MarkdownEditView

#endif  // MARKDOWNTEXTEDITORWIDGET_H
