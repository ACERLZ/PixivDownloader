#ifndef PREFERENCESWINDOW_H
#define PREFERENCESWINDOW_H

#include <QDialog>

namespace Ui {
class PreferencesWindow;
}

class PreferencesWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PreferencesWindow(QWidget *parent = nullptr);
    ~PreferencesWindow();
    void setText();
    void setVersion();
    void setBuildDate();
    void setUrl();

private slots:
    void on_pushButton_clicked();

    void on_buttonBox_accepted();

    void on_aboutQtBtn_clicked();

private:
    Ui::PreferencesWindow *ui;
};

#endif // PREFERENCESWINDOW_H
