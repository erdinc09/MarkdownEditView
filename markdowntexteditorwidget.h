#ifndef MARKDOWNTEXTEDITORWIDGET_H
#define MARKDOWNTEXTEDITORWIDGET_H

#include <texteditor/texteditor.h>

#include <QFocusEvent>

#include "di/idiclient.h"
#include "ihtmlview.h"

namespace MarkdownEditView {
namespace Internal {

class MarkdownTextEditorWidget : public TextEditor::TextEditorWidget {
  Q_OBJECT
 public:
  MarkdownTextEditorWidget(IHtmlView *htmlView_) : htmlView{htmlView_} {};

  void openFinishedSuccessfully() override;

 private slots:
  void contentsChangedWithPosition(int position, int charsRemoved,
                                   int charsAdded);

 private:
  IHtmlView *htmlView;
};

}  // namespace Internal
}  // namespace MarkdownEditView

#endif  // MARKDOWNTEXTEDITORWIDGET_H
