#include "RepoChooserWindow.h"
#include "file_repository.h" // if you use file repo
#include <QDebug>

RepoChooserWindow::RepoChooserWindow(QWidget* parent)
    : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    QPushButton* memoryButton = new QPushButton("Use Memory Repository");
    QPushButton* fileButton = new QPushButton("Use File Repository");

    layout->addWidget(memoryButton);
    layout->addWidget(fileButton);

    connect(memoryButton, &QPushButton::clicked, [=]() {
        auto* repo = new Repository();
        repo->addTrenchCoat(TrenchCoat("M", "Black", 150, 10, "http://photo.com/1.jpg"));
        auto* adminService = new Service(*repo);
        auto* userService = new UserService(*repo);
        auto* mainWindow = new MainWindow(*adminService, *userService);
        mainWindow->show();
        this->close();
        });

    connect(fileButton, &QPushButton::clicked, [=]() {
        auto* repo = new FileRepository("TrenchCoats.txt");
        auto* adminService = new Service(*repo);
        auto* userService = new UserService(*repo);
        auto* mainWindow = new MainWindow(*adminService, *userService);
        mainWindow->show();
        this->close();
        });

    setLayout(layout);
    setWindowTitle("Choose Repository Type");
}
