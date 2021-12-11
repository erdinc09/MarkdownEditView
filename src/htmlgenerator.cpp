#include "htmlgenerator.h"

#include <QDebug>
#include <QFile>
#include <QRegularExpression>
#include <QString>

int main() {
  QFile templateHtmlFile(INDEX_TEMPLATE_HTML);
  if (!templateHtmlFile.exists()) {
    qCritical() << "File Not Found: " << INDEX_TEMPLATE_HTML;
    exit(-1);
  }

  QString htmlTemplate = "<!-- THIS FILE IS GENERATED, DO NOT EDIT! -->\n";
  if (templateHtmlFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
    htmlTemplate = htmlTemplate + QString::fromUtf8(templateHtmlFile.readAll());
    templateHtmlFile.close();
  } else {
    qCritical() << "Cannot Open File " << INDEX_TEMPLATE_HTML;
    exit(-1);
  }

  qInfo() << "Generating html files";

  QString darkHtml = htmlTemplate;
  darkHtml.replace("{markdown_theme}", "node-dark");
  darkHtml.replace("{scroll_bar_theme}", "dark_scroll_bar");
  darkHtml.replace("{highlight_theme}", "dark");

  QString lightHtml = htmlTemplate;
  lightHtml.replace("{markdown_theme}", "github");
  lightHtml.replace("{scroll_bar_theme}", "light_scroll_bar");
  lightHtml.replace("{highlight_theme}", "github");

  QFile darkHtmlFile(INDEX_DARK_HTML);
  if (darkHtmlFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
    QTextStream stream(&darkHtmlFile);
    stream << darkHtml;
    darkHtmlFile.close();
  }

  QFile lightHtmlFile(INDEX_LIGHT_HTML);
  if (lightHtmlFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
    QTextStream stream(&lightHtmlFile);
    stream << lightHtml;
    lightHtmlFile.close();
  }

  qInfo() << "All html files are generated.";
}
