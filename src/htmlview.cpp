#include "htmlview.h"

#include <QWebChannel>

#include "previewpage.h"
namespace MarkdownEditView {
namespace Internal {

HtmlView::HtmlView(IMarkdownEditView *markdownEditView_)
    : mediator{markdownEditView_}, markdownEditView{markdownEditView_} {
  auto *page = new PreviewPage(this);
  setPage(page);

  auto *channel = new QWebChannel(this);
  channel->registerObject(QStringLiteral("mediator"), &mediator);
  page->setWebChannel(channel);
  setUrl(QUrl("qrc:/index.html"));
}

void HtmlView::handleEvent(const TextChangedEvent &event) {
  emit mediator.textChanged(event.getText());
}

void Mediator::pageLoaded() { emit textChanged(markdownEditView->getText()); }

}  // namespace Internal
}  // namespace MarkdownEditView
