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

#ifndef PREVIEWPAGE_H
#define PREVIEWPAGE_H

#include <QWebEnginePage>
#include <QWebEngineSettings>
namespace MarkdownEditView {
namespace Internal {

class PreviewPage : public QWebEnginePage {
  Q_OBJECT
 public:
  explicit PreviewPage(QObject *parent = nullptr) : QWebEnginePage(parent) {
    //    QWebEngineSettings *settings_ = settings();
    //    settings_->setAttribute(QWebEngineSettings::JavascriptCanOpenWindows,
    //                            false);
    //    settings_->setAttribute(QWebEngineSettings::LocalContentCanAccessRemoteUrls,
    //                            false);
    //    settings_->setAttribute(QWebEngineSettings::XSSAuditingEnabled, true);
    //    settings_->setAttribute(QWebEngineSettings::PluginsEnabled, false);
    //    settings_->setAttribute(QWebEngineSettings::AllowRunningInsecureContent,
    //                            true);
    //    settings_->setAttribute(
    //        QWebEngineSettings::AllowGeolocationOnInsecureOrigins, false);
    //    settings_->setAttribute(
    //        QWebEngineSettings::AllowWindowActivationFromJavaScript, false);
    //    settings_->setAttribute(QWebEngineSettings::LocalContentCanAccessFileUrls,
    //                            true);
    //    settings_->setAttribute(QWebEngineSettings::AutoLoadImages, true);
    //    settings_->setAttribute(QWebEngineSettings::JavascriptEnabled, true);
    //    settings_->setAttribute(QWebEngineSettings::LocalStorageEnabled,
    //    true);
  }

 protected:
  bool acceptNavigationRequest(const QUrl &url, NavigationType type,
                               bool isMainFrame) override;
};
}  // namespace Internal
}  // namespace MarkdownEditView

#endif  // PREVIEWPAGE_H
