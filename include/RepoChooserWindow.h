#pragma once
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "MainWindow.h"

class RepoChooserWindow : public QWidget {
    Q_OBJECT

public:
    RepoChooserWindow(QWidget* parent = nullptr);
};
