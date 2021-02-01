#ifndef LANGUAGEHIGHLIGHTERBASE_H
#define LANGUAGEHIGHLIGHTERBASE_H

namespace MarkdownEditView {
namespace Internal {
class LanguageHighlighterBase {
 public:
  LanguageHighlighterBase();
  virtual void initCppData() = 0;
};
}  // namespace Internal
}  // namespace MarkdownEditView

#endif  // LANGUAGEHIGHLIGHTERBASE_H
