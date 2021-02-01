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
#include <QString>

#include "markdownhighlighter.h"

namespace MarkdownEditView {
namespace Internal {

class MarkdownTextEditorWidget : public TextEditor::TextEditorWidget {
  Q_OBJECT
 public:
  void openFinishedSuccessfully() override;
  MarkdownTextEditorWidget();
  void finalizeInitialization() override;
  bool eventFilter(QObject *obj, QEvent *event) override;
 private slots:
  void contentsChangedWithPosition(int position, int charsRemoved,
                                   int charsAdded);

 private:
  bool handleReturnEntered();
  bool openLinkAtCursorPosition();
  QString getMarkdownUrlAtPosition(const QString &text, int position);
  QMap<QString, QString> parseMarkdownUrlsFromText(const QString &text);
  bool isValidUrl(const QString &urlString);
  void openUrl(const QString &urlString);

  QPointer<MarkdownHighlighter> highlighter;
};

}  // namespace Internal
}  // namespace MarkdownEditView

#endif  // MARKDOWNTEXTEDITORWIDGET_H
