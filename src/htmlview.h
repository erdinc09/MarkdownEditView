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
#ifndef HTMLVIEW_H
#define HTMLVIEW_H

#include <QList>
#include <QWebEngineView>

#include "eb/eventlistener.h"
#include "firstlinenumberineditorchangedevent.h"
#include "imarkdowneditview.h"
#include "textchangedevent.h"

namespace MarkdownEditView {
namespace Internal {

/*
 *between C++ and js side ...
 */
class Mediator : public QObject {
  Q_OBJECT
 public:
  Mediator(const IMarkdownEditView *markdownEditView_)
      : markdownEditView{markdownEditView_} {}

  Q_INVOKABLE void pageLoaded() const;  // is called from JS
  Q_INVOKABLE void firstLineNumberInPreviewChanged(
      int lineNumber) const;  // is called from JS

 signals:
  void textChanged(const QString &text, const QString &path) const;
  void firstLineNumberInEditorChanged(const int lineNumber) const;

 private:
  mutable int firstLineNumberInEditorChangedEventCount = 0;
  const IMarkdownEditView *markdownEditView;
};

class HtmlView
    : public QWebEngineView,
      public aeb::EventListener<TextChangedEvent>,
      public aeb::EventListener<FirstLineNumberInEditorChangedEvent> {
  Q_OBJECT
 public:
  HtmlView(IMarkdownEditView *markdownEditView_, bool darkTheme_);

 private:
  Mediator mediator;
  const IMarkdownEditView *markdownEditView;
  const bool darkTheme;
  void handleEvent(const TextChangedEvent &event) override;
  void handleEvent(const FirstLineNumberInEditorChangedEvent &event) override;
};

}  // namespace Internal
}  // namespace MarkdownEditView
#endif  // HTMLVIEW_H
