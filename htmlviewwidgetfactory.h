#ifndef HTMLVIEWWIDGETFACTORY_H
#define HTMLVIEWWIDGETFACTORY_H

#include <coreplugin/inavigationwidgetfactory.h>
#include <ihtmlview.h>

#include "di/dependencyprovider.h"
#include "imarkdowneditview.h"

namespace MarkdownEditView {
namespace Internal {

class HtmlViewWidgetFactory : public Core::INavigationWidgetFactory,
                              Provides(IHtmlView)

{
  Q_OBJECT
 public:
  HtmlViewWidgetFactory();

  void setMarkDownTextToRender(const QString &text) override;

  Core::NavigationView createWidget() override;

 signals:
  void textChanged(const QString &text);

 private:
  Injects(IMarkdownEditView, markdownEditView);
};
}  // namespace Internal
}  // namespace MarkdownEditView
#endif  // HTMLVIEWWIDGETFACTORY_H
