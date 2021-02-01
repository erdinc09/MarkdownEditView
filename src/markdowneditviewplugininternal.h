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

#ifndef MARKDOWNEDITVIEWPLUGININTERNAL_H
#define MARKDOWNEDITVIEWPLUGININTERNAL_H

#include "htmlviewwidgetfactory.h"
#include "markdowntexteditorfactory.h"
namespace MarkdownEditView {
namespace Internal {

class MarkdownEditViewPluginInternal {
 public:
  MarkdownEditViewPluginInternal();

 private:
  const MarkdownTextEditorFactory editorFactory;
  const HtmlViewWidgetFactory viewWidgetFactory;
};
}  // namespace Internal
}  // namespace MarkdownEditView
#endif  // MARKDOWNEDITVIEWPLUGININTERNAL_H
