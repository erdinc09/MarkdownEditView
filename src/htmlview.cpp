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

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QWebChannel>

#include "eb/eventbus.h"
#include "firstlinenumberinpreviewchangedevent.h"
#include "markdowneditviewconstants.h"
#include "previewpage.h"

namespace MarkdownEditView {
namespace Internal {

HtmlView::HtmlView(IMarkdownEditView *markdownEditView_, bool darkTheme_)
    : mediator{markdownEditView_},
      markdownEditView{markdownEditView_},
      darkTheme{darkTheme_},
      channel{std::make_shared<QWebChannel>(this)},
      page{std::make_shared<PreviewPage>(this)} {
  setPage(page.get());
  channel->registerObject(QStringLiteral("mediator"), &mediator);
  page->setWebChannel(channel.get());

  if (darkTheme) {
    // page->setUrl(QUrl("qrc:/markdowneditview/index_dark.html"));
    page->setUrl(QUrl(QDir::cleanPath("file:" + QDir::home().absolutePath() +
                                      QDir::separator() +
                                      Constants::MARKDOWNEDITVIEW_HOME_FOLDER +
                                      QDir::separator() + "index_dark.html")));
    page->setBackgroundColor(QColor{51, 52, 44});
  } else {
    // page->setUrl(QUrl("qrc:/index_light.html"));
    page->setUrl(QUrl(QDir::cleanPath("file:" + QDir::home().absolutePath() +
                                      QDir::separator() +
                                      Constants::MARKDOWNEDITVIEW_HOME_FOLDER +
                                      QDir::separator() + "index_light.html")));
  }
}

void HtmlView::handleEvent(const TextChangedEvent &event) {
  qDebug() << "handleEvent(const TextChangedEvent &event)" << event.getText();
  emit mediator.textChanged(event.getText(), event.getPath());
  if (!event.getText().isEmpty()) {
    emit mediator.firstLineNumberInEditorChanged(
        markdownEditView->getFirstLineNumberInEditor());
  }
}

void HtmlView::handleEvent(const FirstLineNumberInEditorChangedEvent &event) {
  emit mediator.firstLineNumberInEditorChanged(event.lineNumber());
  qDebug() << "line  in editor:" << event.lineNumber();
}

void Mediator::pageLoaded() const {
  qDebug() << "pageLoaded() ";
  emit textChanged(markdownEditView->getText(), markdownEditView->getPath());
  emit firstLineNumberInEditorChanged(
      markdownEditView->getFirstLineNumberInEditor());
}

void Mediator::firstLineNumberInPreviewChanged(int lineNumber) const {
  aeb::postEvent(FirstLineNumberInPreviewChangedEvent(lineNumber));
}

}  // namespace Internal
}  // namespace MarkdownEditView
