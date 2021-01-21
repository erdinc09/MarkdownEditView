#include "htmlviewwidgetfactory.h"

#include <QDebug>

#include "htmlview.h"

namespace MarkdownEditView {
namespace Internal {

HtmlViewWidgetFactory::HtmlViewWidgetFactory() {
  setDisplayName(tr("Markdown View"));
  setPriority(500);
  setId("Markdown View");
}

Core::NavigationView HtmlViewWidgetFactory::createWidget() {
  Core::NavigationView navigationView;
  navigationView.widget = new HtmlView(markdownEditView);
  return navigationView;
}

}  // namespace Internal
}  // namespace MarkdownEditView
