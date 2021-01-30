#include "htmlview.h"

#include <QWebChannel>
#include "previewpage.h"
namespace MarkdownEditView {
namespace Internal {

HtmlView::HtmlView(IMarkdownEditView *markdownEditView_, bool darkTheme_)
    : mediator{markdownEditView_},
      markdownEditView{markdownEditView_},
      darkTheme{darkTheme_}{

    auto page = new PreviewPage(this);
    setPage(page);

    auto channel = new QWebChannel(this);
    channel->registerObject(QStringLiteral("mediator"), &mediator);
    page->setWebChannel(channel);

    if(darkTheme){
        setUrl(QUrl("qrc:/index_dark.html"));
        page->setBackgroundColor(QColor{51,52,44});
    }else{
        setUrl(QUrl("qrc:/index_light.html"));
    }
}

void HtmlView::handleEvent(const TextChangedEvent &event) {
    emit mediator.textChanged(event.getText(),event.getPath());
}

void Mediator::pageLoaded() const {
    emit textChanged(markdownEditView->getText(),markdownEditView->getPath());
}

}  // namespace Internal
}  // namespace MarkdownEditView
