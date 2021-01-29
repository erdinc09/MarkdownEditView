#ifndef IMARKDOWNEDITVIEW_H
#define IMARKDOWNEDITVIEW_H
#include <QString>
namespace MarkdownEditView {
namespace Internal {

class IMarkdownEditView {
public:
    IMarkdownEditView(){};
    virtual const QString getText() const = 0;
    virtual const QString getPath() const = 0;
};
}  // namespace Internal
}  // namespace MarkdownEditView

#endif  // IMARKDOWNEDITVIEW_H
