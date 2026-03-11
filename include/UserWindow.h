#pragma once

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QDesktopServices>
#include <QUrl>
#include "user_service.h"

class UserWindow : public QWidget {
    Q_OBJECT

public:
    UserWindow(UserService& service, QWidget* parent = nullptr);

signals:
    void exitRequested();

private slots:
    void filterCoatsBySize();
    void showNextCoat();
    void addCurrentCoatToCart();
    void viewCart();
    void openCart();
    void exitApp();

private:
    UserService& service;

    QPushButton* filterButton;
    QPushButton* nextButton;
    QPushButton* addButton;
    QPushButton* cartButton;
    QPushButton* openCartButton;
    QPushButton* exitButton;
    QLabel* coatDisplay;

    std::vector<TrenchCoat> filteredCoats;
    int currentIndex = 0;
};
