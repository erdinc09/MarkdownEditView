#include "markdowntexteditorwidget.h"

#include <texteditor/textdocument.h>

#include "eb/eventbus.h"
#include "textchangedevent.h"

namespace MarkdownEditView {
namespace Internal {

void MarkdownTextEditorWidget::openFinishedSuccessfully() {
  TextEditorWidget::openFinishedSuccessfully();

  connect(textDocument(),
          &TextEditor::TextDocument::contentsChangedWithPosition, this,
          &MarkdownTextEditorWidget::contentsChangedWithPosition);

  aeb::postEvent<>(TextChangedEvent{document()->toPlainText()});
}

void MarkdownTextEditorWidget::contentsChangedWithPosition(int, int, int) {
  aeb::postEvent<>(TextChangedEvent{document()->toPlainText()});
}

}  // namespace Internal
}  // namespace MarkdownEditView
