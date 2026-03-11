#pragma once
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include "service.h"
#include "user_service.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    Service& adminService;
    UserService& userService;

    QWidget* mainWidget;
    QVBoxLayout* mainLayout;

    QPushButton* adminButton;
    QPushButton* userButton;
    QPushButton* exitButton;

public:
    MainWindow(Service& adminService, UserService& userService, QWidget* parent = nullptr);
};
