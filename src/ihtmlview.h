/*
 * Copyright (c) 2020-2021 Ahmet Erdinç Yılmaz -- <ahmeterdinc09@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 */

#ifndef IHTMLVIEW_H
#define IHTMLVIEW_H
#include <QString>

class QT_DEPRECATED IHtmlView {
 public:
  IHtmlView(){};
  QT_DEPRECATED virtual void setMarkDownTextToRender(const QString& text) = 0;
};

#endif  // IHTMLVIEW_H
