#include "htmlviewwidgetfactory.h"


#include <QColor>

#include "utils/theme/theme.h"
#include "htmlview.h"

namespace MarkdownEditView {
namespace Internal {

HtmlViewWidgetFactory::HtmlViewWidgetFactory()
    :darkTheme{::Utils::creatorTheme() && ::Utils::creatorTheme()->flag(::Utils::Theme::DarkUserInterface)}
{
    setDisplayName(tr("Markdown View"));
    setPriority(500);
    setId("Markdown View");
}

Core::NavigationView HtmlViewWidgetFactory::createWidget() {
    Core::NavigationView navigationView;
    navigationView.widget = new HtmlView(markdownEditView, darkTheme);
    return navigationView;
}

}  // namespace Internal
}  // namespace MarkdownEditView
