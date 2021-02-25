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

#include "htmlview.h"

#include <QWebChannel>

#include "previewpage.h"
namespace MarkdownEditView {
namespace Internal {

HtmlView::HtmlView(IMarkdownEditView *markdownEditView_, bool darkTheme_)
    : mediator{markdownEditView_},
      markdownEditView{markdownEditView_},
      darkTheme{darkTheme_},
      parser{maddy::Parser{maddy::ParserConfig{false, false}}} {
  auto page = new PreviewPage(this);
  setPage(page);

  auto channel = new QWebChannel(this);
  channel->registerObject(QStringLiteral("mediator"), &mediator);
  page->setWebChannel(channel);

  if (darkTheme) {
    setUrl(QUrl("qrc:/index_dark.html"));
    page->setBackgroundColor(QColor{51, 52, 44});
  } else {
    setUrl(QUrl("qrc:/index_light.html"));
  }
}

void HtmlView::handleEvent(const TextChangedEvent &event) {
  std::stringstream markdown(event.getText().toStdString());
  const std::string output = parser.Parse(markdown);
  emit mediator.textChanged(event.getText(), event.getPath());
}

void Mediator::pageLoaded() const {
  emit textChanged(markdownEditView->getText(), markdownEditView->getPath());
}

}  // namespace Internal
}  // namespace MarkdownEditView
