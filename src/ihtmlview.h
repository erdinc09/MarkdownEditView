#ifndef IHTMLVIEW_H
#define IHTMLVIEW_H
#include <QString>

class QT_DEPRECATED IHtmlView {
 public:
  IHtmlView(){};
  QT_DEPRECATED virtual void setMarkDownTextToRender(const QString& text) = 0;
};

#endif  // IHTMLVIEW_H
