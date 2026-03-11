#include "StartUpWindow.h"

StartUpWindow::StartUpWindow(QWidget* parent) : QWidget(parent) {
    auto* layout = new QVBoxLayout(this);
    auto* memoryButton = new QPushButton("Use Memory Repository");
    auto* fileButton = new QPushButton("Use File Repository");

    layout->addWidget(memoryButton);
    layout->addWidget(fileButton);

    connect(memoryButton, &QPushButton::clicked, this, &StartUpWindow::useMemoryRepo);
    connect(fileButton, &QPushButton::clicked, this, &StartUpWindow::useFileRepo);
}

void StartUpWindow::useMemoryRepo() {
    emit repositoryChosen(std::make_shared<Repository>());
}

void StartUpWindow::useFileRepo() {
    QString fileName = QInputDialog::getText(this, "File Repository", "Enter file name:", QLineEdit::Normal, "TrenchCoats.txt");
   // emit repositoryChosen(std::make_unique<FileRepository>(fileName.toStdString()));
    if (!fileName.isEmpty()) {
        emit repositoryChosen(std::make_shared<FileRepository>(fileName.toStdString()));
    }
}
