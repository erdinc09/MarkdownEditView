/*
 * Copyright (c) 2020-2021 Ahmet Erdinç Yılmaz -- <ahmeterdinc09@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 */

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
