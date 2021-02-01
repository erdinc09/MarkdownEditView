/*
 * Copyright (c) 2020-2021 Ahmet Erdinç Yılmaz -- <ahmeterdinc09@gmail.com>
 *
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

#include "markdowneditview.h"

#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/coreconstants.h>
#include <coreplugin/icontext.h>
#include <coreplugin/icore.h>

#include <QAction>
#include <QMainWindow>
#include <QMenu>
#include <QMessageBox>

#include "markdowneditviewconstants.h"

namespace MarkdownEditView {
namespace Internal {

MarkdownEditViewPlugin::MarkdownEditViewPlugin() {
  // Create your members
}

MarkdownEditViewPlugin::~MarkdownEditViewPlugin() {
  // Unregister objects from the plugin manager's object pool
  // Delete members

  delete dd;
  dd = nullptr;
}

bool MarkdownEditViewPlugin::initialize(const QStringList &arguments,
                                        QString *errorString) {
  // Register objects in the plugin manager's object pool
  // Load settings
  // Add actions to menus
  // Connect to other plugins' signals
  // In the initialize function, a plugin can be sure that the plugins it
  // depends on have initialized their members.

  Q_UNUSED(arguments)
  Q_UNUSED(errorString)

  dd = new MarkdownEditViewPluginInternal;
  adif::initilizeAndShutDown();
  return true;
}

void MarkdownEditViewPlugin::extensionsInitialized() {
  // Retrieve objects from the plugin manager's object pool
  // In the extensionsInitialized function, a plugin can be sure that all
  // plugins that depend on it are completely initialized.
}

ExtensionSystem::IPlugin::ShutdownFlag
MarkdownEditViewPlugin::aboutToShutdown() {
  // Save settings
  // Disconnect from signals that are not needed during shutdown
  // Hide UI (if you add UI that is not in the main window directly)
  return SynchronousShutdown;
}

}  // namespace Internal
}  // namespace MarkdownEditView
