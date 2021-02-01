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
