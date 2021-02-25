#ifndef FIRSTLINECHANGEDEVENT_H
#define FIRSTLINECHANGEDEVENT_H
namespace MarkdownEditView {
namespace Internal {
class FirstLineNumberInEditorChangedEvent {
 public:
  FirstLineNumberInEditorChangedEvent(int lineNumber)
      : lineNumber_(lineNumber){};
  int lineNumber() const { return lineNumber_; }

 private:
  int lineNumber_;
};
}  // namespace Internal
}  // namespace MarkdownEditView

#endif  // FIRSTLINECHANGEDEVENT_H
