#include "settingsdialog.h"
#include "settings.h"
#include "customcontrols.h"
#include "datastore.h"
#include "settingsmanager.h"

#include <QGroupBox>
#include <QHBoxLayout>
#include <QMessageBox>
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

    encryptDraftsCheck = new CheckBox("Encrypt drafts on disk");
    encryptTemplatesCheck = new CheckBox("Encrypt templates on disk");
    encryptDraftsCheck->setChecked(Settings::encryptDraftsOnDisk);
    encryptTemplatesCheck->setChecked(Settings::encryptTemplatesOnDisk);
    encryptDraftsCheck->setDisabled(true);
    encryptDraftsCheck->setToolTip("Feature not yet released");
    encryptTemplatesCheck->setDisabled(true);
    encryptTemplatesCheck->setToolTip("Feature not yet released");
    storageLayout->addWidget(encryptDraftsCheck);
    storageLayout->addWidget(encryptTemplatesCheck);

    persistWindowSizeCheck = new CheckBox("Persist window state");
    persistWindowSizeCheck->setChecked(Settings::persistWindowState);
    storageLayout->addWidget(persistWindowSizeCheck);

    QHBoxLayout *deleteBtnsLayout = new QHBoxLayout();
    storageLayout->addLayout(deleteBtnsLayout);

    deleteAllDraftsBtn = new DeleteButton("Delete all Drafts");
    deleteAllTemplatesBtn = new DeleteButton("Delete all Templates");
    connect(deleteAllDraftsBtn, SIGNAL(clicked()), this, SLOT(onDeleteAllDraftsBtnClicked()));
    connect(deleteAllTemplatesBtn, SIGNAL(clicked()), this, SLOT(onDeleteAllTemplatesBtnClicked()));
    deleteBtnsLayout->addWidget(deleteAllDraftsBtn);
    deleteBtnsLayout->addWidget(deleteAllTemplatesBtn);

    mainLayout->addStretch();

    QHBoxLayout *btnsLayout = new QHBoxLayout();
    mainLayout->addLayout(btnsLayout);

    btnsLayout->addStretch();

    Button *saveBtn = new Button("Save");
    DeleteButton *cancelBtn = new DeleteButton("Cancel");
    btnsLayout->addWidget(saveBtn);
    btnsLayout->addWidget(cancelBtn);
    connect(saveBtn, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancelBtn, SIGNAL(clicked()), this, SLOT(reject()));
}

void SettingsDialog::onDeleteAllDraftsBtnClicked()
{
    QMessageBox::StandardButton result =
        QMessageBox::question(
            this,
            "Delete all drafts?",
            "Are you sure you want to delete all drafts? This can't be undone.");

    if (result == QMessageBox::Yes)
    {
        DataStore::getInstance()->deleteAllTweetDrafts();
        SettingsManager::getInstance()->saveTweetDrafts();
    }
}

void SettingsDialog::onDeleteAllTemplatesBtnClicked()
{
    QMessageBox::StandardButton result =
        QMessageBox::question(
            this,
            "Delete all templates?",
            "Are you sure you want to delete all templates? This can't be undone.");

    if (result == QMessageBox::Yes)
    {
        DataStore::getInstance()->deleteAllTweetTemplates();
        SettingsManager::getInstance()->saveTweetTemplates();
    }
}

void SettingsDialog::accept()
{
    Settings::encryptDraftsOnDisk = encryptDraftsCheck->isChecked();
    Settings::encryptTemplatesOnDisk = encryptTemplatesCheck->isChecked();
    Settings::persistWindowState = persistWindowSizeCheck->isChecked();
    QDialog::accept();
}
