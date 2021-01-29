#ifndef TEXTCHANGEDEVENT_H
#define TEXTCHANGEDEVENT_H
#include <QString>
namespace MarkdownEditView {
namespace Internal {
class TextChangedEvent {
public:
    TextChangedEvent(){}//for close
    TextChangedEvent(QString&& text_,const QString&& path_) : text{std::move(text_)},path{std::move(path_)} {};
    const QString& getText() const { return text; };
    const QString& getPath() const { return path; };

private:
    const QString text;
    const QString path;
};
}  // namespace Internal
}  // namespace MarkdownEditView

#endif  // TEXTCHANGEDEVENT_H
