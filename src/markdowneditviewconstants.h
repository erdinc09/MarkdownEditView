#ifndef MARKDOWNEDITVIEWCONSTANTS_H
#define MARKDOWNEDITVIEWCONSTANTS_H
#include <QString>
namespace MarkdownEditView {
namespace Constants {

inline QString const MARKDOWNEDITVIEW_HOME_FOLDER = ".markdowneditview";
inline QString const MARKDOWNEDITVIEW_QRC_PREFIX = ":/markdowneditview";

constexpr char ACTION_ID[] = "MarkdownEditView.Action";
constexpr char MENU_ID[] = "MarkdownEditView.Menu";
constexpr char MARKDOWN_EDITOR_ID[] = "MarkdownEditView.MarkdownEditor";
constexpr char MARKDOWN_MIME_TYPE[] = "text/markdown";
}  // namespace Constants

}  // namespace MarkdownEditView

#endif // MARKDOWNEDITVIEWCONSTANTS_H
