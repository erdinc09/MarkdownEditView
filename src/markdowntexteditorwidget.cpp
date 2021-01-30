#include "markdowntexteditorwidget.h"

#include <texteditor/textdocument.h>

#include <QDebug>

#include "eb/eventbus.h"
#include "textchangedevent.h"
namespace MarkdownEditView {
namespace Internal {

void MarkdownTextEditorWidget::openFinishedSuccessfully() {
    TextEditorWidget::openFinishedSuccessfully();

    connect(textDocument(),
            &TextEditor::TextDocument::contentsChangedWithPosition, this,
            &MarkdownTextEditorWidget::contentsChangedWithPosition);

    aeb::postEvent<>(TextChangedEvent{document()->toPlainText(),QString{textDocument()->filePath().absolutePath().toString()}});
}

void MarkdownTextEditorWidget::contentsChangedWithPosition(int, int, int) {
    aeb::postEvent<>(TextChangedEvent{document()->toPlainText(),QString{textDocument()->filePath().absolutePath().toString()}});
}

}  // namespace Internal
}  // namespace MarkdownEditView
