#ifndef MARKDOWNTEXTEDITORFACTORY_H
#define MARKDOWNTEXTEDITORFACTORY_H
#include <texteditor/texteditor.h>

#include <QList>

#include "di/dependencyprovider.h"
#include "ihtmlview.h"
#include "imarkdowneditview.h"
#include "markdowntexteditorwidget.h"

namespace MarkdownEditView {
namespace Internal {

class MarkdownTextEditorFactory : public TextEditor::TextEditorFactory,
                                  Provides(IMarkdownEditView) {
  Q_OBJECT
 public:
  MarkdownTextEditorFactory();
  virtual const QString getText() override;

 private:
  Injects(IHtmlView, htmlView);
};
}  // namespace Internal
}  // namespace MarkdownEditView

#endif  // MARKDOWNTEXTEDITORFACTORY_H
