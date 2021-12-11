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

#include "previewpage.h"

#include <QDebug>
#include <QDesktopServices>
namespace MarkdownEditView {
namespace Internal {

bool PreviewPage::acceptNavigationRequest(const QUrl &url,
                                          QWebEnginePage::NavigationType type,
                                          bool isMainFrame) {
  Q_UNUSED(isMainFrame)
  Q_UNUSED(type)

  qDebug() << "url.scheme():" << url.scheme();
  // Only allow qrc:/ or file:/
  if (url.scheme() == QString("qrc") || url.scheme() == QString("file")) {
    return true;
  } else {
    // open links in external browser
    QDesktopServices::openUrl(url);
    return false;
  }
}
}  // namespace Internal
}  // namespace MarkdownEditView
