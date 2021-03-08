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

#ifndef MARKDOWNTEXTEDITORFACTORY_H
#define MARKDOWNTEXTEDITORFACTORY_H
#include <texteditor/texteditor.h>

#include <QList>

#include "di/dependencyprovider.h"
#include "imarkdowneditview.h"

namespace MarkdownEditView {
namespace Internal {

class MarkdownTextEditorFactory : public TextEditor::TextEditorFactory,
                                  Provides(IMarkdownEditView) {
  Q_OBJECT
 public:
  MarkdownTextEditorFactory();
  ~MarkdownTextEditorFactory();
  virtual const QString getText() const override;
  virtual const QString getPath() const override;
  virtual int getFirstLineNumberInEditor() const override;

 public slots:
  void currentEditorChanged(Core::IEditor *editor) const;
};
}  // namespace Internal
}  // namespace MarkdownEditView

#endif  // MARKDOWNTEXTEDITORFACTORY_H
