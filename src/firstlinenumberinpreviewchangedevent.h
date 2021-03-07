#ifndef FIRSTLINENUMBERINPREVIEWCHANGEDEVENT_H
#define FIRSTLINENUMBERINPREVIEWCHANGEDEVENT_H

namespace MarkdownEditView {
namespace Internal {
class FirstLineNumberInPreviewChangedEvent
{
 public:
  FirstLineNumberInPreviewChangedEvent(int lineNumber)
      : lineNumber_(lineNumber){};
  int lineNumber() const { return lineNumber_; }

 private:
  int lineNumber_;
};
}  // namespace Internal
}  // namespace MarkdownEditView

#endif // FIRSTLINENUMBERINPREVIEWCHANGEDEVENT_H
