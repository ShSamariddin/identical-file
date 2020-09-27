#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QCommonStyle>
#include <QDesktopWidget>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QCryptographicHash>
#include <QMessageBox>
#include <QFileIconProvider>
#include <QDirIterator>
#include <QFileInfo>
#include <QDesktopServices>

#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
main_window::main_window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, size(), qApp->desktop()->availableGeometry()));

    ui->treeWidget->header()->setSectionResizeMode(0, QHeaderView::Stretch);

    ui->treeWidget->header()->setSectionResizeMode(2, QHeaderView::ResizeToContents);

    QCommonStyle style;
    ui->actionScan_Directory->setIcon(style.standardIcon(QCommonStyle::SP_DialogOpenButton));
    ui->actionExit->setIcon(style.standardIcon(QCommonStyle::SP_DialogCloseButton));
    ui->actionAbout->setIcon(style.standardIcon(QCommonStyle::SP_DialogHelpButton));
    ui->actionFrom_smaller_to_bigge->setIcon(style.standardIcon(QCommonStyle::SP_ArrowDown));
    ui->action_rom_bigger_to_smaller->setIcon(style.standardIcon(QCommonStyle::SP_ArrowUp));
    ui->treeWidget->setStyleSheet("background-color: rgb(100,100,100);");


    connect(ui->treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(open_file(QTreeWidgetItem*, int))); // open file on double click
    connect(ui->actionFrom_smaller_to_bigge, &QAction::triggered, this, &main_window::sort_s_to_b);
    connect(ui->action_rom_bigger_to_smaller, &QAction::triggered, this, &main_window::sort_b_to_s);
    connect(ui->actionScan_Directory, &QAction::triggered, this, &main_window::select_directory);//chko mekna
    connect(ui->actionExit, &QAction::triggered, this, &QWidget::close);
    connect(ui->actionAbout, &QAction::triggered, this, &main_window::show_about_dialog);

//    scan_directory(QDir::homePath());
}

main_window::~main_window()
{}

void main_window::select_directory()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Select Directory for Scanning",
                                                    QString(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks); // i chko mkna druni kavsda chiyay
    clear_all();
    scan_directory(dir);
    write_on_treeWidget();
}

void main_window::clear_all()
{
    for(auto it:resualt){
        resualt[it.first].clear();
    }
    list_resualt.clear();
    ui->treeWidget->clear();
}

void main_window::sort_s_to_b(){
    sort(list_resualt.begin(), list_resualt.end());
    write_on_treeWidget();
}
void main_window::sort_b_to_s(){
    sort(list_resualt.begin(), list_resualt.end());
    reverse(list_resualt.begin(), list_resualt.end());
    write_on_treeWidget();
}
void main_window::write_on_treeWidget(){
    ui->treeWidget->clear();
    for(auto it:list_resualt){
            QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeWidget);
            bool e_time = false;
            int color1 = rand() % 200 + 55;
            int color2 = rand() % 200 + 55;
            int color3 = rand() % 200 + 55;
            QFileInfo inf_it =  QFileInfo(resualt[it.second].front());
            if(!inf_it.isDir()){
                for(auto new_it:resualt[it.second]){
                    if(!e_time){
                        QFileInfo inf_it =  QFileInfo(new_it);
                        item->setText(0, inf_it.fileName());
                        item->setTextColor(0, QColor::fromRgb(color1, color2, color3));
                        item->setTextColor(1, QColor::fromRgb(color1, color2, color3));
                        item->setTextColor(2, QColor::fromRgb(color1, color2, color3));
                        item->setTextColor(3, QColor::fromRgb(color1, color2, color3));
                        item->setText(1, QString::number(resualt[it.second].size()));
                        item->setText(2, QString::number(inf_it.size()));
                        item->setText(3, QString::number(inf_it.size() * resualt[it.second].size()));
                        item->setIcon(0, QFileIconProvider().icon(new_it));
                        e_time = true;
                    }
                    QTreeWidgetItem* child = new QTreeWidgetItem();
                    child->setText(0, new_it);
                    child->setTextColor(0, QColor::fromRgb(color1, color2, color3));
                    item->addChild(child);

                }
            }
            ui->treeWidget->addTopLevelItem(item);
    }

}

void main_window::scan_directory(QString const& dir)
{
    ui->treeWidget->clear();
    ui->treeWidget->setBackgroundRole(QPalette::Dark);
    setWindowTitle(QString("Directory Content - %1").arg(dir));
    QDir d(dir);
    QFileInfoList list = d.entryInfoList();
    QDirIterator it(dir, QDir::NoDotAndDotDot | QDir::Hidden | QDir::NoSymLinks | QDir::AllEntries, QDirIterator::Subdirectories);
    std::map<long long, std::vector<QString>> list_name;
    while(it.hasNext())
    {
        auto name = it.next();
        //QFile file(name);
        //std::cout << name.size()<<'\n';
        list_name[it.fileInfo().size()].push_back(name);

    }
    for(auto iter:list_name){
        if(iter.second.size() > 1){
            for(auto name:iter.second){
                QCryptographicHash crypto(QCryptographicHash::Sha256);
                QFile file(name);
                file.open(QFile::ReadOnly);

                while(!file.atEnd()) {
                  crypto.addData(file.read(8192));
                }
                QByteArray hash = crypto.result();
                QString string_hash = hash.toHex().data();
                resualt[string_hash].push_back(name);
            }
        }
    }
    for(auto it:resualt){

        if(it.second.size() > 1){
            auto name = it.second.front();
            QFileInfo inf_it =  QFileInfo(name);
            list_resualt.push_back({inf_it.size(), it.first});
        }
    }
}

void main_window::show_about_dialog()
{
    QMessageBox::aboutQt(this);
}
void main_window::open_file(QTreeWidgetItem *item, int){
    if(item->childCount() == 0) {
        QDesktopServices::openUrl(QUrl("file:" + item->text(0))); //open file in standart programm
    }
}
