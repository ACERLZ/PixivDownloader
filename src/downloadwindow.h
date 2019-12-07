#ifndef DOWNLOADWINDOW_H
#define DOWNLOADWINDOW_H

#include <QDialog>

namespace Ui {
class DownloadWindow;
}

class DownloadWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DownloadWindow(QWidget *parent = nullptr);
    ~DownloadWindow();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DownloadWindow *ui;
};

#endif // DOWNLOADWINDOW_H
