#include <QApplication>

#include "MainWindow.h"

#include "Logger.h"

using namespace gui;

int main(int argc, char *argv[])
{
    base::Log().setLogWriter( new base::TimestampedLogWriter(
                new base::FileLogWriter("piclex.log")) );

    base::Log().info("piclex");

    QApplication app(argc, argv);

    MainWindow mw;
    mw.show();

    int res = app.exec();

    base::Log().info("piclex exit");

    return res;
}
