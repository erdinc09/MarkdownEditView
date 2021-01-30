#ifndef MARKDOWNTEXTEDITORWIDGET_H
#define MARKDOWNTEXTEDITORWIDGET_H

#include <texteditor/texteditor.h>

namespace MarkdownEditView {
namespace Internal {

class MarkdownTextEditorWidget : public TextEditor::TextEditorWidget {
    Q_OBJECT
public:
    void openFinishedSuccessfully() override;
private slots:
    void contentsChangedWithPosition(int position, int charsRemoved,
                                     int charsAdded);
};

}  // namespace Internal
}  // namespace MarkdownEditView

#endif  // MARKDOWNTEXTEDITORWIDGET_H
