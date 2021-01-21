#ifndef HTMLVIEW_H
#define HTMLVIEW_H

#include <QList>
#include <QWebEngineView>

#include "eb/eventlistener.h"
#include "imarkdowneditview.h"
#include "textchangedevent.h"

namespace MarkdownEditView {
namespace Internal {

/*
 *between C++ and js side ...
 */
class Mediator : public QObject {
  Q_OBJECT
 public:
  Mediator(const IMarkdownEditView *markdownEditView_)
      : markdownEditView{markdownEditView_} {}

  Q_INVOKABLE void pageLoaded();  // is called from JS

 signals:
  void textChanged(const QString &text);

 private:
  const IMarkdownEditView *markdownEditView;
};

class HtmlView : public QWebEngineView,
                 public aeb::EventListener<TextChangedEvent> {
  Q_OBJECT
 public:
  HtmlView(IMarkdownEditView *markdownEditView_);

 private:
  Mediator mediator;
  IMarkdownEditView *markdownEditView;

  void handleEvent(const TextChangedEvent &event) override;
};

}  // namespace Internal
}  // namespace MarkdownEditView
#endif  // HTMLVIEW_H
