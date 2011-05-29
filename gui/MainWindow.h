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
    bool setSearchStr(const QString &str);

    void selectDirectory();

    void search();

    void openItem(const QModelIndex &index);

    void disableQueryHighlight();

private:
    void connectToSignals();

    void highlightQuery(bool highlighted);

private:
    Ui::MainWindow mUi;

    SearchModel mModel;

    QString mSearchEditStyleSheet;
};

}

#endif//MAIN_WINDOW_H
