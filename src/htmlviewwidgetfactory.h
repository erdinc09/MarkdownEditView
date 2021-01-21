#ifndef HTMLVIEWWIDGETFACTORY_H
#define HTMLVIEWWIDGETFACTORY_H

#include <coreplugin/inavigationwidgetfactory.h>

#include "di/dependencyprovider.h"
#include "ihtmlview.h"
#include "imarkdowneditview.h"

namespace MarkdownEditView {
namespace Internal {

class HtmlViewWidgetFactory : public Core::INavigationWidgetFactory

{
  Q_OBJECT
 public:
  HtmlViewWidgetFactory();

  Core::NavigationView createWidget() override;

 signals:
  void textChanged(const QString &text);

 private:
  Injects(IMarkdownEditView, markdownEditView);
};
}  // namespace Internal
}  // namespace MarkdownEditView
#endif  // HTMLVIEWWIDGETFACTORY_H
