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
        QWebEngineSettings *settings_ = settings();
        settings_->setAttribute(QWebEngineSettings::JavascriptCanOpenWindows,
                                false);
        settings_->setAttribute(QWebEngineSettings::LocalContentCanAccessRemoteUrls,
                                false);
        settings_->setAttribute(QWebEngineSettings::XSSAuditingEnabled, true);
        settings_->setAttribute(QWebEngineSettings::PluginsEnabled, false);
        settings_->setAttribute(QWebEngineSettings::AllowRunningInsecureContent,
                                false);
        settings_->setAttribute(
                    QWebEngineSettings::AllowGeolocationOnInsecureOrigins, false);
        settings_->setAttribute(
                    QWebEngineSettings::AllowWindowActivationFromJavaScript, false);
    }

protected:
    bool acceptNavigationRequest(const QUrl &url, NavigationType type,
                                 bool isMainFrame) override;
};
}  // namespace Internal
}  // namespace MarkdownEditView

#endif  // PREVIEWPAGE_H
