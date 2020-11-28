#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QCheckBox>
#include <QDialog>
#include <QObject>

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    SettingsDialog(QWidget *parent = nullptr);

    void accept();

    QCheckBox *encryptDraftsCheck;
    QCheckBox *encryptTemplatesCheck;
};

#endif // SETTINGSDIALOG_H
