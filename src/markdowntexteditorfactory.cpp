#include "markdowntexteditorfactory.h"

#include <coreplugin/editormanager/editormanager.h>
#include <texteditor/textdocument.h>
#include <texteditor/texteditor.h>

#include "eb/eventbus.h"
#include "markdowneditviewconstants.h"
#include "markdowntexteditorwidget.h"
#include "textchangedevent.h"

using EditorManager = Core::EditorManager;

namespace MarkdownEditView {
namespace Internal {

MarkdownTextEditorFactory::MarkdownTextEditorFactory() {
    setId(Constants::MARKDOWN_EDITOR_ID);
    setDisplayName("Markdown Edit & View");
    addMimeType("text/plain");
    addMimeType("text/markdown");

    setDocumentCreator([]() {
        return new TextEditor::TextDocument(Constants::MARKDOWN_EDITOR_ID);
    });
    setEditorCreator([]() { return new TextEditor::BaseTextEditor; });

    setEditorWidgetCreator([=]() { return new MarkdownTextEditorWidget{}; });

    EditorManager* editorManager = EditorManager::instance();
    connect(editorManager, &EditorManager::currentEditorChanged,
            this, &::MarkdownEditView::Internal::MarkdownTextEditorFactory::currentEditorChanged);
}

void MarkdownTextEditorFactory::currentEditorChanged(Core::IEditor* editor) const{
    MarkdownTextEditorWidget* currentWidget;
    if (editor != nullptr && (currentWidget = dynamic_cast<MarkdownTextEditorWidget*>(editor->widget()))) {
        aeb::postEvent(TextChangedEvent{currentWidget->document()->toPlainText(),
                                        QString{currentWidget->textDocument()->filePath().absolutePath().toString()}});
    } else {
        aeb::postEvent(TextChangedEvent{});
    }
}

const QString MarkdownTextEditorFactory::getText() const {
    MarkdownTextEditorWidget* currentTexteditor = dynamic_cast<MarkdownTextEditorWidget*>(MarkdownTextEditorWidget::currentTextEditorWidget());
    return  currentTexteditor!=nullptr ? currentTexteditor->document()->toPlainText() : QString{};
}

const QString MarkdownTextEditorFactory::getPath() const {
    MarkdownTextEditorWidget* currentTexteditor = dynamic_cast<MarkdownTextEditorWidget*>(MarkdownTextEditorWidget::currentTextEditorWidget());
    return currentTexteditor!=nullptr ? QString{currentTexteditor->textDocument()->filePath().absolutePath().toString()} : QString{};
}


MarkdownTextEditorFactory::~MarkdownTextEditorFactory() {
    EditorManager* editorManager = EditorManager::instance();
    disconnect(editorManager, &::Core::EditorManager::currentEditorChanged, this,
               &::MarkdownEditView::Internal::MarkdownTextEditorFactory::
               currentEditorChanged);
}

}  // namespace Internal
}  // namespace MarkdownEditView
