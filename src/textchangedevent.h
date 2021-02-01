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

#ifndef TEXTCHANGEDEVENT_H
#define TEXTCHANGEDEVENT_H
#include <QString>
namespace MarkdownEditView {
namespace Internal {
class TextChangedEvent {
 public:
  TextChangedEvent() {}  // for close
  TextChangedEvent(QString&& text_, const QString&& path_)
      : text{std::move(text_)}, path{std::move(path_)} {};
  const QString& getText() const { return text; };
  const QString& getPath() const { return path; };

 private:
  const QString text;
  const QString path;
};
}  // namespace Internal
}  // namespace MarkdownEditView

#endif  // TEXTCHANGEDEVENT_H
