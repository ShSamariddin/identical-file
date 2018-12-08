#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include <QCommonStyle>
#include <QDesktopWidget>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QCryptographicHash>
#include <QTreeWidgetItem>
#include <QMessageBox>
#include <QFileIconProvider>
#include <QDirIterator>
#include <QFileInfo>

namespace Ui {
class MainWindow;
}

class main_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit main_window(QWidget *parent = 0);
    ~main_window();
private:
    std::map<QString, std::vector<QString>> resualt;
    std::vector<std::pair<long long, QString>> list_resualt;
private slots:
    void select_directory();
    void clear_all();
    void scan_directory(QString const& dir);
    void show_about_dialog();
    void open_file(QTreeWidgetItem *item, int column);
    void write_on_treeWidget();
    void sort_s_to_b();
    void sort_b_to_s();

private:
    std::unique_ptr<Ui::MainWindow> ui;
};

#endif // MAINWINDOW_H
