#include "markdowntexteditorfactory.h"

#include <coreplugin/editormanager/editormanager.h>
#include <texteditor/textdocument.h>
#include <texteditor/texteditor.h>

#include <typeinfo>

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
  connect(editorManager, &EditorManager::currentEditorChanged, this,
          &::MarkdownEditView::Internal::MarkdownTextEditorFactory::
              currentEditorChanged);
}

void MarkdownTextEditorFactory::currentEditorChanged(Core::IEditor* editor) {
  QWidget* currentWidget;
  if (editor != nullptr &&
      typeid(currentWidget = editor->widget(), *currentWidget) ==
          typeid(MarkdownTextEditorWidget)) {
    aeb::postEvent(
        TextChangedEvent{static_cast<MarkdownTextEditorWidget*>(currentWidget)
                             ->document()
                             ->toPlainText()});
  } else {
    aeb::postEvent(TextChangedEvent{QString{}});
  }
}

const QString MarkdownTextEditorFactory::getText() const {
  TextEditor::TextEditorWidget* currentTexteditor =
      MarkdownTextEditorWidget::currentTextEditorWidget();
  if (currentTexteditor != nullptr &&
      typeid(*currentTexteditor) == typeid(MarkdownTextEditorWidget)) {
    return static_cast<MarkdownTextEditorWidget*>(currentTexteditor)
        ->document()
        ->toPlainText();
  } else {
    return QString();
  }
}

MarkdownTextEditorFactory::~MarkdownTextEditorFactory() {
  EditorManager* editorManager = EditorManager::instance();
  disconnect(editorManager, &::Core::EditorManager::currentEditorChanged, this,
             &::MarkdownEditView::Internal::MarkdownTextEditorFactory::
                 currentEditorChanged);
}

}  // namespace Internal
}  // namespace MarkdownEditView
