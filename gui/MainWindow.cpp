#include "MainWindow.h"

#include <QFileDialog>

#include "Logger.h"
#include "SearcherFactory.h"

using namespace base;

namespace gui
{
MainWindow::MainWindow()
    :mModel(createSearcher())
{
    mUi.setupUi(this);

    connectToSignals();

    mUi.listView->setModel(&mModel);

    setDirectory(QDir::homePath());
}

void MainWindow::setDirectory(const QString &path)
{
    if(mModel.setDirectory(path))
        mUi.directoryLabel->setText(path);
}

void MainWindow::setSearchStr(const QString &str)
{
    mModel.setSearchStr(str);
}

void MainWindow::search()
{
    setSearchStr(mUi.searchEdit->text());
}

void MainWindow::selectDirectory()
{
    QString path = QFileDialog::getExistingDirectory(this,
            tr("Select Directory"), QDir::homePath(),
            QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    if(!path.isNull())
        setDirectory(path);
}

void MainWindow::connectToSignals()
{
    connect( mUi.selectDirectoryButton, SIGNAL(clicked()), this,
            SLOT(selectDirectory()) );

    connect( mUi.searchButton, SIGNAL(clicked()), this,
            SLOT(search()) );

    connect( mUi.searchEdit, SIGNAL(returnPressed()), this,
            SLOT(search()) );
}

}
