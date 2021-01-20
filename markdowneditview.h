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
