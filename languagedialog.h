#ifndef LANGUAGEDIALOG_H
#define LANGUAGEDIALOG_H

#include <QDialog>
#include "userprofile.h"

class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;

class LanguageDialog : public QDialog
{
    Q_OBJECT

QLabel *languagePromptText;
QLabel *fromLangText;
QLabel *toLangText;
QLabel *recentLangText;
QLineEdit *lang1Select;
QLineEdit *lang2Select;
QPushButton *goButton;

public:
    LanguageDialog(QWidget *parent = 0);
    ~LanguageDialog();

};

#endif // LANGUAGEDIALOG_H
