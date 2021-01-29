#ifndef MARKDOWNTEXTEDITORFACTORY_H
#define MARKDOWNTEXTEDITORFACTORY_H
#include <texteditor/texteditor.h>

#include <QList>

#include "di/dependencyprovider.h"
#include "imarkdowneditview.h"

namespace MarkdownEditView {
namespace Internal {

class MarkdownTextEditorFactory : public TextEditor::TextEditorFactory,
        Provides(IMarkdownEditView) {
    Q_OBJECT
    public:
    MarkdownTextEditorFactory();
    ~MarkdownTextEditorFactory();
    virtual const QString getText() const override;
    virtual const QString getPath() const override;

    public slots:
    void currentEditorChanged(Core::IEditor *editor) const;
};
}  // namespace Internal
}  // namespace MarkdownEditView

#endif  // MARKDOWNTEXTEDITORFACTORY_H
