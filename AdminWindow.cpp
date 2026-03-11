#include "AdminWindow.h"
#include <QMessageBox>
#include <QPainter>

AdminWindow::AdminWindow(Service& service, QWidget* parent)
    : QWidget(parent), service(service) {

    // Inputs
    sizeEdit = new QLineEdit();
    colorEdit = new QLineEdit();
    priceEdit = new QLineEdit();
    quantityEdit = new QLineEdit();
    photoEdit = new QLineEdit();

    QFormLayout* formLayout = new QFormLayout();
    formLayout->addRow("Size:", sizeEdit);
    formLayout->addRow("Color:", colorEdit);
    formLayout->addRow("Price:", priceEdit);
    formLayout->addRow("Quantity:", quantityEdit);
    formLayout->addRow("Photo URL:", photoEdit);

    // Buttons
    addButton = new QPushButton("Add Coat");
    updateButton = new QPushButton("Update Coat");
    removeButton = new QPushButton("Remove Coat");
    listButton = new QPushButton("List All Coats");
    exitButton = new QPushButton("Exit");


    // List
    coatList = new QListWidget();

    // ComboBox for view mode
    viewModeCombo = new QComboBox();
    viewModeCombo->addItem("Short");
    viewModeCombo->addItem("Detailed");

    // Layout
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(addButton);
    mainLayout->addWidget(updateButton);
    mainLayout->addWidget(removeButton);
    mainLayout->addWidget(listButton);
    mainLayout->addWidget(viewModeCombo);
    mainLayout->addWidget(coatList);
    mainLayout->addWidget(exitButton);


    setLayout(mainLayout);
    setWindowTitle("Admin Panel");

    // Connections
    connect(addButton, &QPushButton::clicked, [this]() {
        std::string size = sizeEdit->text().toStdString();
        std::string color = colorEdit->text().toStdString();
        int price = priceEdit->text().toInt();
        int quantity = quantityEdit->text().toInt();
        std::string photo = photoEdit->text().toStdString();

        if (this->service.addTrenchCoatService(size, color, price, quantity, photo))
            QMessageBox::information(this, "Success", "Coat added!");
        else
            QMessageBox::warning(this, "Error", "Coat already exists!");

        refreshCoatList();
        });

    connect(updateButton, &QPushButton::clicked, [this]() {
        std::string size = sizeEdit->text().toStdString();
        std::string color = colorEdit->text().toStdString();
        int price = priceEdit->text().toInt();
        int quantity = quantityEdit->text().toInt();
        std::string photo = photoEdit->text().toStdString();

        if (this->service.updateTrenchCoatService(size, color, price, quantity, photo))
            QMessageBox::information(this, "Success", "Coat updated!");
        else
            QMessageBox::warning(this, "Error", "Coat not found!");

        refreshCoatList();
        });

    connect(removeButton, &QPushButton::clicked, [this]() {
        std::string size = sizeEdit->text().toStdString();
        std::string color = colorEdit->text().toStdString();

        if (this->service.removeTrenchCoatService(size, color))
            QMessageBox::information(this, "Success", "Coat removed!");
        else
            QMessageBox::warning(this, "Error", "Coat not found!");

        refreshCoatList();
        });

    connect(listButton, &QPushButton::clicked, this, &AdminWindow::refreshCoatList);
    connect(exitButton, &QPushButton::clicked, this, &QWidget::close);
    connect(viewModeCombo, &QComboBox::currentTextChanged, this, [this]() {
        refreshCoatList();
        });
    refreshCoatList();
}

void AdminWindow::refreshCoatList() {
    coatList->clear();
    auto coats = service.getTrenchCoats();
    QString mode = viewModeCombo->currentText();

    for (const auto& coat : coats) {
        QString item;

        if (mode == "Short") {
            item = QString::fromStdString(coat.getSize() + " - " + coat.getColor());
        }
        else {  // Detailed
            item = "Size: " + QString::fromStdString(coat.getSize()) +
                ", Color: " + QString::fromStdString(coat.getColor()) +
                ", Price: " + QString::number(coat.getPrice()) + "$" +
                ", Quantity: " + QString::number(coat.getQuantity()) +
                ", Photo: " + QString::fromStdString(coat.getPhotograph());
        }

        coatList->addItem(item);
    }
}

void AdminWindow::paintEvent(QPaintEvent* event) {
    QPainter painter(this);

    QLinearGradient gradient(0, 0, 0, height());
    gradient.setColorAt(0, QColor(255, 165, 0));  
    gradient.setColorAt(1, QColor(0, 0, 255));  

    painter.fillRect(rect(), gradient);
    QWidget::paintEvent(event);  
}

