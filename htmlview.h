#ifndef HTMLVIEW_H
#define HTMLVIEW_H

#include <QList>
#include <QWebEngineView>

#include "imarkdowneditview.h"

//@Beta
#include "eb/eventlistener.h"
#include "textchangedevent.h"

namespace MarkdownEditView {
namespace Internal {

/*
 *between C++ and js side ...
 */
class Mediator : public QObject {
  Q_OBJECT
 signals:
  void textChanged(const QString &text);
  void loadMarkDown();
 public slots:
  void loadFinished();  // is called from JS
};

class HtmlView : public QWebEngineView,
                 public aeb::EventListener<TextChangedEvent> {
  Q_OBJECT
 public:
  HtmlView(IMarkdownEditView *markdownEditView_);
  ~HtmlView();
  static void setAllViews(const QString &text);
 public slots:
  void loadMarkdown();

 private:
  Mediator mediator;
  IMarkdownEditView *markdownEditView;

  void handleEvent(const TextChangedEvent &event) override;

  void setMarkDownTextToRender(const QString &text);
  static QList<HtmlView *> openedViews;
};

}  // namespace Internal
}  // namespace MarkdownEditView
#endif  // HTMLVIEW_H
