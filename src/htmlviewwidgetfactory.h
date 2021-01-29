#ifndef HTMLVIEWWIDGETFACTORY_H
#define HTMLVIEWWIDGETFACTORY_H

#include <coreplugin/inavigationwidgetfactory.h>
#include <QUrl>
#include "di/dependencyprovider.h"
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
    const bool darkTheme;
};
}  // namespace Internal
}  // namespace MarkdownEditView
#endif  // HTMLVIEWWIDGETFACTORY_H
