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
