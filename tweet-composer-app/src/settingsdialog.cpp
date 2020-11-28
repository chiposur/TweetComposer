#include "settingsdialog.h"
#include "settings.h"
#include "customcontrols.h"

#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("TweetComposer Settings");

    QVBoxLayout *mainLayout = new QVBoxLayout();
    setLayout(mainLayout);

    QGroupBox *storageGroupBox = new QGroupBox("Storage");
    mainLayout->addWidget(storageGroupBox);

    QVBoxLayout *storageLayout = new QVBoxLayout();
    storageGroupBox->setLayout(storageLayout);

    encryptDraftsCheck = new QCheckBox("Encrypt drafts on disk");
    encryptTemplatesCheck = new QCheckBox("Encrypt templates on disk");
    encryptDraftsCheck->setChecked(Settings::encryptDraftsOnDisk);
    encryptTemplatesCheck->setChecked(Settings::encryptTemplatesOnDisk);
    storageLayout->addWidget(encryptDraftsCheck);
    storageLayout->addWidget(encryptTemplatesCheck);

    mainLayout->addStretch();

    QHBoxLayout *btnsLayout = new QHBoxLayout();
    mainLayout->addLayout(btnsLayout);

    btnsLayout->addStretch();

    StandardButton *saveBtn = new StandardButton("Save");
    DeleteButton *cancelBtn = new DeleteButton("Cancel");
    btnsLayout->addWidget(saveBtn);
    btnsLayout->addWidget(cancelBtn);
    connect(saveBtn, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancelBtn, SIGNAL(clicked()), this, SLOT(reject()));
}

void SettingsDialog::accept()
{
    Settings::encryptDraftsOnDisk = encryptDraftsCheck->isChecked();
    Settings::encryptTemplatesOnDisk = encryptTemplatesCheck->isChecked();
    QDialog::accept();
}
