#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "mp3manager.h"
#include "mp3filemanager.h"
#include "taglib/taglib/tag.h"
#include "bass/bass.h"
#include <string>
#include "mp3player.h"
#include <thread>
#include <QTimer>
#include <cstdlib>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(slotTimerAlarm()));
    timer->start(250);
    ui->positionSlider->setMaximum(100);
    ui->positionSlider->setMinimum(0);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_saveButton_clicked()
{
    fManager.saveAll(manager);
}

void MainWindow::on_loadButton_clicked()
{
    ui->songList->clear();
    fManager.loadFilepaths(manager);
    fManager.loadSongs(manager);
    updateList(*(manager.getDatabase()));
}

void MainWindow::on_addPathButton_clicked()
{
    string path =  ui->pathLine->text().toStdString();
    vector<string>* filepathes = manager.getFilepathContainer();
    bool g=true;
    for(int i = 0;i<filepathes->size();i++){
        if(path == (*(filepathes))[i]){
            g = false;
        }
    };
    if(g){
        manager.addDirectory(path);}
    manager.rescanDirectories();
    updateList(*(manager.getDatabase()));
}
void MainWindow::on_songList_doubleClicked(const QModelIndex &index){
    player.playSong(currentSongs[index.row()]);
}
void MainWindow::updateList(vector<song> songs){
    ui->songList->clear();
    currentSongs = songs;
    for (int i = 0;i<currentSongs.size();i++){
        ui->songList->addItem(QString::fromStdString(currentSongs[i].getName()));
    }
}

void MainWindow::on_searchButton_clicked()
{

    string year = ui->yearLine->text().toStdString();
    string name = ui->nameLine->text().toStdString();
    string album = ui->albumLine->text().toStdString();
    string artist = ui->artistLine->text().toStdString();
    string genre = ui->genreLine->text().toStdString();
    vector<song> temp = manager.search(name,"",year,genre, artist ,album);
    updateList(temp);
}

void MainWindow::on_playButton_clicked()
{
    player.playPause();
}
void MainWindow::slotTimerAlarm(){
    int current = player.getCurrentTime();
    int total = player.getTotalTime();
    string currentString = to_string(div(current,60).quot)+":"+to_string(div(div(current,60).rem,10).quot)+to_string(div(div(current,60).rem,10).rem);
    string totalString = to_string(div(total,60).quot)+":"+to_string(div(div(total,60).rem,10).quot)+to_string(div(div(total,60).rem,10).rem);
    if(player.isActive()){
        ui->timeLabel->setText(QString::fromStdString(currentString+"/"+totalString));
        int temp = ((double)current/(double)total)*100;
        ui->positionSlider->setValue(temp);
    }
}

void MainWindow::on_positionSlider_sliderPressed()
{
}

void MainWindow::on_positionSlider_sliderReleased()
{
    player.setPosition(ui->positionSlider->value());
}

void MainWindow::on_positionSlider_valueChanged(int value)
{
}
void MainWindow::on_positionSlider_sliderMoved(int position)
{
    player.setPosition(ui->positionSlider->value());
}

void MainWindow::on_volumeSlider_valueChanged(int value)
{
    player.setVolume(value);
}
