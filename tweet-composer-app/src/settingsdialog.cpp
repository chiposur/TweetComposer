#include "settingsdialog.h"
#include "settings.h"
#include "customcontrols.h"
#include "datastore.h"
#include "settingsmanager.h"
#include "styles.h"

#include <QGroupBox>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QVBoxLayout>

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("TweetComposer Settings");

    QVBoxLayout *mainLayout = new QVBoxLayout();
    setLayout(mainLayout);

    QGroupBox *twitterApiGroupBox = new QGroupBox("Twitter API");
    mainLayout->addWidget(twitterApiGroupBox);

    QVBoxLayout *twitterApiLayout = new QVBoxLayout();
    twitterApiGroupBox->setLayout(twitterApiLayout);

    apiKeyLineEdit = new QLineEdit(Settings::apiKey);
    apiSecretLineEdit = new QLineEdit(Settings::apiSecret);
    accessTokenLineEdit = new QLineEdit(Settings::accessToken);
    accessTokenSecretLineEdit = new QLineEdit(Settings::accessTokenSecret);

    apiKeyLineEdit->setEchoMode(QLineEdit::Password);
    apiSecretLineEdit->setEchoMode(QLineEdit::Password);
    accessTokenLineEdit->setEchoMode(QLineEdit::Password);
    accessTokenSecretLineEdit->setEchoMode(QLineEdit::Password);

    twitterApiLayout->addWidget(new QLabel("API key:"));
    twitterApiLayout->addWidget(apiKeyLineEdit);
    twitterApiLayout->addWidget(new QLabel("API key secret:"));
    twitterApiLayout->addWidget(apiSecretLineEdit);
    twitterApiLayout->addWidget(new QLabel("Access token:"));
    twitterApiLayout->addWidget(accessTokenLineEdit);
    twitterApiLayout->addWidget(new QLabel("Access token secret:"));
    twitterApiLayout->addWidget(accessTokenSecretLineEdit);

    QGroupBox *storageGroupBox = new QGroupBox("Storage");
    mainLayout->addWidget(storageGroupBox);

    QVBoxLayout *storageLayout = new QVBoxLayout();
    storageGroupBox->setLayout(storageLayout);

    encryptDraftsCheck = new QCheckBox("Encrypt drafts on disk");
    encryptTemplatesCheck = new QCheckBox("Encrypt templates on disk");
    encryptDraftsCheck->setChecked(Settings::encryptDraftsOnDisk);
    encryptTemplatesCheck->setChecked(Settings::encryptTemplatesOnDisk);
    encryptDraftsCheck->setDisabled(true);
    encryptDraftsCheck->setToolTip("Feature not yet released");
    encryptTemplatesCheck->setDisabled(true);
    encryptTemplatesCheck->setToolTip("Feature not yet released");
    storageLayout->addWidget(encryptDraftsCheck);
    storageLayout->addWidget(encryptTemplatesCheck);

    persistWindowSizeCheck = new QCheckBox("Persist window state");
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
    deleteBtnsLayout->addStretch();

    mainLayout->addStretch();

    QHBoxLayout *btnsLayout = new QHBoxLayout();
    mainLayout->addLayout(btnsLayout);

    btnsLayout->addStretch();

    QPushButton *saveBtn = new QPushButton("Save");
    QPushButton *cancelBtn = new QPushButton("Cancel");
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
    Settings::apiKey = apiKeyLineEdit->text();
    Settings::apiSecret = apiSecretLineEdit->text();
    Settings::accessToken = accessTokenLineEdit->text();
    Settings::accessTokenSecret = accessTokenSecretLineEdit->text();
    Settings::encryptDraftsOnDisk = encryptDraftsCheck->isChecked();
    Settings::encryptTemplatesOnDisk = encryptTemplatesCheck->isChecked();
    Settings::persistWindowState = persistWindowSizeCheck->isChecked();
    QDialog::accept();
}
