/**
 * @file languagedialog.hpp
 * @brief Header definitions for the language dialog class.
 * @author Alex Zirbel
 */

#ifndef LANGUAGEDIALOG_H
#define LANGUAGEDIALOG_H

#include <QDialog>
#include "userprofile.hpp"
#include "languagepair.hpp"

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

//! @todo Change to a drop-down menu
QLineEdit *recentList;
QPushButton *goButton;
QPushButton *backButton;

public:
    LanguageDialog(QWidget *parent = 0);
    ~LanguageDialog();

signals:
    void submitLanguagePair(LanguagePair *languages);
    void back();

private slots:
    void goClicked();
    void backClicked();

};

#endif // LANGUAGEDIALOG_H

