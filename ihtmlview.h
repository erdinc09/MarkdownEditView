#ifndef IHTMLVIEW_H
#define IHTMLVIEW_H
#include <QString>

class IHtmlView {
 public:
  IHtmlView(){};
  virtual void setMarkDownTextToRender(const QString& text) = 0;
};

#endif  // IHTMLVIEW_H
