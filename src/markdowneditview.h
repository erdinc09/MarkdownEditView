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

#ifndef MARKDOWNEDITVIEWPLUGIN_H
#define MARKDOWNEDITVIEWPLUGIN_H

#include <extensionsystem/iplugin.h>

#include "markdowneditview_global.h"
#include "markdowneditviewplugininternal.h"

namespace MarkdownEditView {
namespace Internal {

class MarkdownEditViewPlugin : public ExtensionSystem::IPlugin {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE
                      "MarkdownEditView.json")

public:
    MarkdownEditViewPlugin();
    ~MarkdownEditViewPlugin() override;

    bool initialize(const QStringList &arguments, QString *errorString) override;
    void extensionsInitialized() override;
    ShutdownFlag aboutToShutdown() override;

private:
    MarkdownEditViewPluginInternal *dd;
};

}  // namespace Internal
}  // namespace MarkdownEditView

#endif  // MARKDOWNEDITVIEWPLUGIN_H
