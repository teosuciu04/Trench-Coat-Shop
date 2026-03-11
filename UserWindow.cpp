#include "UserWindow.h"
#include <QInputDialog>
#include <QMessageBox>

UserWindow::UserWindow(UserService& service, QWidget* parent)
    : QWidget(parent), service(service)
{
    auto* layout = new QVBoxLayout(this);


    // Ask user for cart format (HTML or CSV)
    QStringList formats = { "HTML", "CSV" };
    QString selected = QInputDialog::getItem(this, "Cart Format", "Choose cart format:", formats, 0, false);

    if (selected == "HTML") {
        service.setCartSaver(new CartSaverHTML("cart.html"));
    }
    else {
        service.setCartSaver(new CartSaverCSV("cart.csv"));
    }
 
    filterButton = new QPushButton("Filter by Size");
    nextButton = new QPushButton("Next Coat");
    addButton = new QPushButton("Add to Cart");
    cartButton = new QPushButton("View Cart");
    openCartButton = new QPushButton("Open Cart File");
    exitButton = new QPushButton("Exit");
    coatDisplay = new QLabel("No coat loaded.");
    coatDisplay->setWordWrap(true);

    layout->addWidget(filterButton);
    layout->addWidget(coatDisplay);
    layout->addWidget(nextButton);
    layout->addWidget(addButton);
    layout->addWidget(cartButton);
    layout->addWidget(openCartButton);
    layout->addWidget(exitButton);

    connect(filterButton, &QPushButton::clicked, this, &UserWindow::filterCoatsBySize);
    connect(nextButton, &QPushButton::clicked, this, &UserWindow::showNextCoat);
    connect(addButton, &QPushButton::clicked, this, &UserWindow::addCurrentCoatToCart);
    connect(cartButton, &QPushButton::clicked, this, &UserWindow::viewCart);
    connect(openCartButton, &QPushButton::clicked, this, &UserWindow::openCart);
    connect(exitButton, &QPushButton::clicked, this, &UserWindow::exitApp);
}

void UserWindow::filterCoatsBySize() {
    QString size = QInputDialog::getText(this, "Filter Coats", "Enter Size:");
    if (size.isEmpty())
        return;

    filteredCoats = service.getTrenchCoatsBySize(service.getTrenchCoatsUser(), size.toStdString());
    currentIndex = 0;

    if (filteredCoats.empty()) {
        coatDisplay->setText("No trench coats available for this size.");
    }
    else {
        showNextCoat();
    }
}

void UserWindow::showNextCoat() {
    if (filteredCoats.empty()) {
        coatDisplay->setText("No filtered coats. Please filter first.");
        return;
    }

    if (currentIndex >= filteredCoats.size())
        currentIndex = 0;

    const auto& coat = filteredCoats[currentIndex];
    QString displayText = QString::fromStdString(
        coat.getSize() + ", " + coat.getColor() + ", " +
        std::to_string(coat.getPrice()) + "$, " +
        std::to_string(coat.getQuantity()) + " pcs\n" +
        coat.getPhotograph()
    );

    coatDisplay->setText(displayText);
    QDesktopServices::openUrl(QUrl(QString::fromStdString(coat.getPhotograph())));
    currentIndex++;
}

void UserWindow::addCurrentCoatToCart() {
    if (filteredCoats.empty()) {
        QMessageBox::warning(this, "Warning", "No coat selected.");
        return;
    }

    const auto& coat = filteredCoats[(currentIndex - 1 + filteredCoats.size()) % filteredCoats.size()];
    TrenchCoat coatCopy = filteredCoats[(currentIndex - 1 + filteredCoats.size()) % filteredCoats.size()];

    if (service.AddToCart(coatCopy)) {
        double total = service.getSum();
        QMessageBox::information(this, "Added", QString("Added to cart.\nTotal: %1$").arg(total));
    }
    else {
        QMessageBox::warning(this, "Error", "Failed to add to cart.");
    }
}

void UserWindow::viewCart() {
    const auto& cart = service.getCart();
    if (cart.empty()) {
        QMessageBox::information(this, "Cart", "Your cart is empty.");
        return;
    }

    QString items;
    for (const auto& coat : cart) {
        items += QString::fromStdString(
            coat.getSize() + ", " + coat.getColor() + ", " +
            std::to_string(coat.getPrice()) + "$, " +
            std::to_string(coat.getQuantity()) + " pcs\n"
        );
    }

    double total = service.getSum();
    QMessageBox::information(this, "Cart", items + QString("\nTotal: %1$").arg(total));
}

void UserWindow::openCart() {
    service.openCart();
    QMessageBox::information(this, "Cart File", "Cart opened in default app.");
}

void UserWindow::exitApp() {
    emit exitRequested();
    close();
}
