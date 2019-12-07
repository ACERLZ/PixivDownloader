#include "preferenceswindow.h"
#include "ui_preferenceswindow.h"

#include "basepixivapi.h"
#include "settings.h"

#include <QDebug>
#include <QMessageBox>

PreferencesWindow::PreferencesWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreferencesWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Preferences");

    ui->password->setEchoMode(QLineEdit::Password);

    ui->proxyType->addItem("None");
    ui->proxyType->addItem("Socks5");
    ui->proxyType->addItem("Http");

    ui->proxyPassword->setEchoMode(QLineEdit::Password);

    setText();
    setVersion();
    setBuildDate();
    setUrl();

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

PreferencesWindow::~PreferencesWindow()
{
    delete ui;
}

void PreferencesWindow::setText()
{
    ui->username->setText(Settings::username);
    ui->password->setText(Settings::password);
    ui->address->setText(Settings::address);
    ui->port->setValue(Settings::port);
    ui->authentication->setChecked(Settings::authentication);
    ui->proxyUsername->setText(Settings::proxyUsername);
    ui->proxyPassword->setText(Settings::proxyPassword);
}

void PreferencesWindow::setVersion()
{
    ui->version->setText(Settings::version);
}

void PreferencesWindow::setBuildDate()
{
    ui->compileTime->setText(Settings::buildDate.toString() + " " + Settings::buildTime.toString());
}

void PreferencesWindow::setUrl()
{
    ui->sourceCodeLink->setOpenExternalLinks(true);
    ui->sourceCodeLink->setText("<a href=\"https://github.com/TheWanderingCoel/PixivDownloader\">https://github.com/TheWanderingCoel/PixivDownloader");
    ui->licenseLink->setOpenExternalLinks(true);
    ui->licenseLink->setText("<a href=\"https://www.gnu.org/licenses/gpl-3.0.txt\">GPL V3 (https://www.gnu.org/licenses/gpl-3.0.txt)");
}

void PreferencesWindow::on_pushButton_clicked()
{
    Settings::username = ui->username->text();
    Settings::password = ui->password->text();
    QMessageBox alert;
    alert.setWindowTitle("PixivDownloader");
    bool status = BasePixivAPI::auth(Settings::username, Settings::password);
    if (status) {
        alert.setText("Login successfully.");
    } else {
        alert.setText("Login failed. Please check your account or password.");
    }
    alert.addButton(tr("OK"), QMessageBox::YesRole);
    alert.exec();
}

void PreferencesWindow::on_buttonBox_accepted()
{
    Settings::proxyType = ui->proxyType->currentText();
    Settings::address = ui->address->text();
    Settings::port = ui->port->value();
    Settings::authentication = ui->authentication->isChecked();
    Settings::proxyUsername = ui->proxyUsername->text();
    Settings::proxyPassword = ui->proxyPassword->text();
}

void PreferencesWindow::on_aboutQtBtn_clicked()
{
    QApplication::aboutQt();
}
