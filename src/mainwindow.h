#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QStandardItemModel *model;
    void add2Table(QString authorName, int authorId, QString artworkTitle, int artworkId);
    void change2Table();
    void startDownload();
    void downloadBookmarks();
    void downloadArtworkId();
    void downloadAuthorId();

private slots:
    void on_preferencesBtn_clicked();

    void on_addTaskBtn_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
