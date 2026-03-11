#pragma once
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QInputDialog>
#include <memory>
#include "Repository.h"
#include "file_repository.h"

class StartUpWindow : public QWidget {
    Q_OBJECT

public:
    StartUpWindow(QWidget* parent = nullptr);

signals:
    void repositoryChosen(std::shared_ptr<Repository> repo);

private slots:
    void useMemoryRepo();
    void useFileRepo();
};
