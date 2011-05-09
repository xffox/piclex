#include "MainWindow.h"

#include <QFileDialog>
#include <QDesktopServices>
#include <QUrl>

#include "Logger.h"
#include "SearcherFactory.h"
#include "SearchViewDelegate.h"
#include "GuiDefines.h"

using namespace base;

namespace gui
{
MainWindow::MainWindow()
    :mModel(createSearcher())
{
    mUi.setupUi(this);

    connectToSignals();

    mUi.listView->setModel(&mModel);

    SearchViewDelegate *delegate = new SearchViewDelegate(IMAGE_PREVIEW_SIZE, this);
    mUi.listView->setItemDelegate(delegate);

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

void MainWindow::openItem(const QModelIndex &index)
{
    QString filename = index.model()->data(index, Qt::DisplayRole).toString();
    if(!filename.isEmpty())
    {
        bool res = QDesktopServices::openUrl(QUrl(filename,
                    QUrl::TolerantMode));
        base::Log().debug("Open file '%s' %s", qPrintable(filename),
                res?"":"failed");
    }
}

void MainWindow::selectDirectory()
{
    QString path = QFileDialog::getExistingDirectory(this,
            tr("Select Directory"), QDir::homePath(),
            QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    if(!path.isNull())
    {
        setDirectory(path);
    }
}

void MainWindow::connectToSignals()
{
    connect( mUi.selectDirectoryButton, SIGNAL(clicked()), this,
            SLOT(selectDirectory()) );

    connect( mUi.searchButton, SIGNAL(clicked()), this,
            SLOT(search()) );

    connect( mUi.searchEdit, SIGNAL(returnPressed()), this,
            SLOT(search()) );

    connect( mUi.listView, SIGNAL(activated(const QModelIndex&)), this,
            SLOT(openItem(const QModelIndex&)) );
}

}
