#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QCheckBox>
#include <QDialog>
#include <QObject>

#include "customcontrols.h"

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    SettingsDialog(QWidget *parent = nullptr);

    void accept();

private slots:
    void onDeleteAllDraftsBtnClicked();
    void onDeleteAllTemplatesBtnClicked();

private:
    QCheckBox *encryptDraftsCheck;
    QCheckBox *encryptTemplatesCheck;

    DeleteButton *deleteAllDraftsBtn;
    DeleteButton *deleteAllTemplatesBtn;
};

#endif // SETTINGSDIALOG_H
