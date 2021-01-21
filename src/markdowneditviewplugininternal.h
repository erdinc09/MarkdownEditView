#ifndef MARKDOWNEDITVIEWPLUGININTERNAL_H
#define MARKDOWNEDITVIEWPLUGININTERNAL_H

#include "htmlviewwidgetfactory.h"
#include "markdowntexteditorfactory.h"
namespace MarkdownEditView {
namespace Internal {

class MarkdownEditViewPluginInternal {
 public:
  MarkdownEditViewPluginInternal();

 private:
  MarkdownTextEditorFactory editorFactory;
  HtmlViewWidgetFactory viewWidgetFactory;
};
}  // namespace Internal
}  // namespace MarkdownEditView
#endif  // MARKDOWNEDITVIEWPLUGININTERNAL_H
