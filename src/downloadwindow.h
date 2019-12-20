//
//  downloadwindow.h
//  PixivDownloader
//
//  Created by TheWanderingCoel on 2019/12/5.
//  Copyright © 2019 Coel Wu. All rights reserved.
//

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
