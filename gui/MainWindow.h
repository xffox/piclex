#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>

#include "ui_main.h"

#include "SearchModel.h"

namespace gui
{
class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

public slots:
    void setDirectory(const QString &path);
    void setSearchStr(const QString &str);

    void selectDirectory();

    void search();

private:
    void connectToSignals();

private:
    Ui::MainWindow mUi;

    SearchModel mModel;
};

}

#endif//MAIN_WINDOW_H
