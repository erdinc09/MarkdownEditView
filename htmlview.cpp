#include "htmlview.h"

#include <QDebug>
#include <QFile>
#include <QTimer>
#include <QWebChannel>
#include <QtDebug>
#include <utility>

#include "imarkdowneditview.h"
#include "previewpage.h"
namespace MarkdownEditView {
namespace Internal {

QList<HtmlView *> HtmlView::openedViews;

HtmlView::HtmlView(IMarkdownEditView *markdownEditView_)
    : markdownEditView{markdownEditView_} {
  auto *page = new PreviewPage(this);
  setPage(page);

  auto *channel = new QWebChannel(this);
  channel->registerObject(QStringLiteral("mediator"), &mediator);
  page->setWebChannel(channel);
  setUrl(QUrl("qrc:/index.html"));
  openedViews.append(this);

  connect(&mediator, &Mediator::loadMarkDown, this, &HtmlView::loadMarkdown);
}

void HtmlView::handleEvent(const TextChangedEvent &event) {
  qDebug() << "handleEvent(const TextChangedEvent &event)";
}

void HtmlView::loadMarkdown() {
  setMarkDownTextToRender(markdownEditView->getText());
}

HtmlView::~HtmlView() {
  qDebug() << "View Removed = " << openedViews.removeOne(this);
}

void HtmlView::setMarkDownTextToRender(const QString &text) {
  emit mediator.textChanged(text);
}

void HtmlView::setAllViews(const QString &text) {
  std::for_each(openedViews.begin(), openedViews.end(),
                [&text](auto t) { t->setMarkDownTextToRender(text); });
}

void Mediator::loadFinished() { emit loadMarkDown(); }

}  // namespace Internal
}  // namespace MarkdownEditView
