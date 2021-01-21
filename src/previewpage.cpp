#include "previewpage.h"

#include <QDesktopServices>
namespace MarkdownEditView {
namespace Internal {

bool PreviewPage::acceptNavigationRequest(const QUrl &url,
                                          QWebEnginePage::NavigationType type,
                                          bool isMainFrame) {
  Q_UNUSED(isMainFrame)
  Q_UNUSED(type)

  // Only allow qrc:/index.html.
  if (url.scheme() == QString("qrc")) return true;
  QDesktopServices::openUrl(url);
  return false;
}
}  // namespace Internal
}  // namespace MarkdownEditView
