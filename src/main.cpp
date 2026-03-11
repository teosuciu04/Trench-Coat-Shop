#include <QApplication>
#include "RepoChooserWindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    RepoChooserWindow* chooser = new RepoChooserWindow();
    chooser->show();

    return app.exec();
}
