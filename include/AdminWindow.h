#pragma once
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QListWidget>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QComboBox>
#include <QPainter>
#include "service.h"

class AdminWindow : public QWidget {
    Q_OBJECT

private:
    Service& service;
    QVBoxLayout* layout;

    QLineEdit* sizeEdit;
    QLineEdit* colorEdit;
    QLineEdit* priceEdit;
    QLineEdit* quantityEdit;
    QLineEdit* photoEdit;

    QPushButton* addButton;
    QPushButton* updateButton;
    QPushButton* removeButton;
    QPushButton* listButton;

    QListWidget* coatList;
    QPushButton* exitButton;

    QComboBox* viewModeCombo;

public:
   explicit AdminWindow(Service& service, QWidget* parent = nullptr);

private:
    void refreshCoatList();
    void paintEvent(QPaintEvent* event) override;
};
