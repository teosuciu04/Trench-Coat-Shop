#include "MainWindow.h"
#include "AdminWindow.h"
#include "UserWindow.h"

MainWindow::MainWindow(Service& adminService, UserService& userService, QWidget* parent)
    : QMainWindow(parent), adminService(adminService), userService(userService) {

    auto* mainWidget = new QWidget();
    auto* mainLayout = new QVBoxLayout();

    QPushButton* adminButton = new QPushButton("Admin Mode");
    QPushButton* userButton = new QPushButton("User Mode");
    QPushButton* exitButton = new QPushButton("Exit");

    mainLayout->addWidget(adminButton);
    mainLayout->addWidget(userButton);
    mainLayout->addWidget(exitButton);

    connect(adminButton, &QPushButton::clicked, [&]() {
        auto* adminWin = new AdminWindow(adminService);
        adminWin->show();
        });

    connect(userButton, &QPushButton::clicked, [&]() {
        auto* userWin = new UserWindow(userService);
        userWin->setAttribute(Qt::WA_DeleteOnClose);
        userWin->show();

        connect(userWin, &UserWindow::exitRequested, [=]() {
            userWin->close();  
            });
	});

    connect(exitButton, &QPushButton::clicked, this, &QMainWindow::close);

    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);
    setWindowTitle("Trench Coat Store");
}
