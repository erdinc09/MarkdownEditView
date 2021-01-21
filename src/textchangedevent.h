#ifndef TEXTCHANGEDEVENT_H
#define TEXTCHANGEDEVENT_H
#include <QString>
namespace MarkdownEditView {
namespace Internal {
class TextChangedEvent {
 public:
  TextChangedEvent(const QString& text_) : text{text_} {};
  TextChangedEvent(QString&& text_) : text{std::move(text_)} {};
  const QString& getText() const { return text; };

 private:
  QString text;
};
}  // namespace Internal
}  // namespace MarkdownEditView

#endif  // TEXTCHANGEDEVENT_H
