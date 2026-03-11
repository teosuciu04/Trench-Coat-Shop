#include "ui.h"
#include <iostream>
#include <conio.h>

using namespace std;

UI::UI(Service& adminService, UserService& userService) : adminService{ adminService }, userService{userService} {}

//ADMIN OP
void UI :: addTrenchCoatUI()
{
	string size, color, photo;
	int price;
	int quantity;

	cout << "Size: "; cin >> size;
	cout << "Color: "; cin >> color;
	cout << "Price: "; cin >> price;
	cout << "Quantity: "; cin >> quantity;
	cout << "Photo: "; cin >> photo;

	if (adminService.addTrenchCoatService(size, color, price, quantity, photo))
		cout << "Trench Coat added successfully!\n";
	else
		cout << "Coat already exists\n";
}

void UI::removeTrenchCoatUI()
{
	string size, color;
	cout << "Size: "; cin >> size;
	cout << "Color: "; cin >> color;

	if (adminService.removeTrenchCoatService(size, color))
		cout << "Trench Coat removed successfully!\n";
	else
		cout << "Coat does not exists\n";
}

void UI::updateTrenchCoatUI()
{
	string size, color, photo;
	int price;
	int quantity;

	cout << "Size: "; cin >> size;
	cout << "Color: "; cin >> color;
	cout << "New Price: "; cin >> price;
	cout << "New Quantity: "; cin >> quantity;
	cout << "New Photo: "; cin >> photo;

	if (adminService.updateTrenchCoatService(size, color, price, quantity, photo))
		cout << "Trench Coat updated successfully!\n";
	else
		cout << "Coat does not exists\n";

}

void UI::listAllTrenchCoats()
{
	auto trenchCoats = adminService.getTrenchCoats();
	for (int i = 0; i < adminService.getSize(); i++)
		trenchCoats[i].display();
}



//USER OP
void UI::getTrenchCoatsBySizeUI()
{
	string size;
	cout << "Size: "; cin >> size;
	vector<TrenchCoat> filteredTrenchCoats = this->userService.getTrenchCoatsBySize(this->adminService.getTrenchCoats(), size);

	if (filteredTrenchCoats.empty()) {
		cout << "No trench coats available for this size\n";
		return;
	}

	int index = 0;
	while (true) {
		if (index == filteredTrenchCoats.size())
			index = 0;

		TrenchCoat coat = filteredTrenchCoats[index];
		coat.display();

		cout << "\nDo you want to add it in the cart? yes/no\nOption: ";
		string option;
		cin >> option;
		if (option == "yes") {
			if(this->userService.AddToCart(coat))
			// Update the quantity of the coat in the repository
			cout << "Added successfully!\n";
			cout << "You have to pay: " << this->userService.getSum() << "$\n";

			if (filteredTrenchCoats.size() == 0) {
				cout << "No more trench coats left.\n";
				break;
			}
		}
		index++;
		cout << "\nDo you want to see the next coat? next/exit\nOption: ";
		cin >> option;
		if (option == "exit")
			break;
			
	}
}

void UI::listAllTrenchCoatsInCartUI()
{
	cout << "You have to pay: " << this->userService.getSum() << "$\n";
	cout << "You have the following coats in your cart:\n";
	vector<TrenchCoat> coats = this->userService.getCart();
	for (int i = 0; i < coats.size(); i++)
		coats[i].display();

}

void UI::openCartUI()
{
	this->userService.openCart();
}


//MENUS
void UI::adminMenu()
{
	system("cls");

	while (true)
	{
		cout << "\n[ADMIN MENU]\n";
		cout << "\n1. ADD COAT\n2. REMOVE COAT\n3. UPDATE COAT\n4. LIST ALL COATS\n0. BACK\n";

		int option;
		cin >> option;
		
		switch (option)
		{
			case 1: addTrenchCoatUI(); break;
			case 2: removeTrenchCoatUI(); break;
			case 3: updateTrenchCoatUI(); break;
			case 4: listAllTrenchCoats(); break;
			case 0: return;
			default: cout << "Invalid optiton";
		}
	}
}

void UI::userMenu()
{
	system("cls");
	cout << "Choose file type to save cart (CSV/HTML): ";
	string fileType;
	cin >> fileType;

	if (fileType == "CSV") {
		userService.setCartSaver(new CartSaverCSV("cart.csv"));
	}
	else if (fileType == "HTML") {
		userService.setCartSaver(new CartSaverHTML("cart.html"));
	}
	else {
		cout << "Invalid file type. Defaulting to CSV.\n";
		userService.setCartSaver(new CartSaverCSV("cart.csv"));
	}
	while (true)
	{
		cout << "\n[USER MENU]\n";
		cout << "\n1. SEARCH TRENCH COAT\n2. LIST ALL COATS IN CART\n3. OPEN CART\n0. BACK\n";
		int option;
		cin >> option;
		switch (option)
		{
		case 1: system("cls"); getTrenchCoatsBySizeUI(); break; // Add to cart
		case 2: system("cls"); listAllTrenchCoatsInCartUI(); break; // List all coats in cart
		case 3: system("cls"); openCartUI(); break; // Open cart
		case 0: return;
		default: cout << "Invalid option";
		}
	}
}

enum Mode { ADMIN = 0, USER, EXIT };

int chooseMode() {
	int current = 0;
	const char* options[] = { "Administrator Mode", "User Mode", "Exit" };
	const int optionCount = 3;

	while (true) {
		system("cls"); // Clears screen (Windows only)
		cout << "Press ENTER to choose mode:\n\n";

		for (int i = 0; i < optionCount; ++i) {
			if (i == current)
				cout << " -> ";
			else
				cout << "   ";

			cout << options[i] << "\n";
		}

		int key = _getch();

		// Arrow keys come in pairs, first key is 224
		if (key == 224) {
			int arrow = _getch();
			if (arrow == 72) current = (current - 1 + optionCount) % optionCount; // Up
			if (arrow == 80) current = (current + 1) % optionCount; // Down
		}
		else if (key == 13) { // Enter
			return current;
		}
	}
}
void UI::start() {
	while (true) {
		int mode = chooseMode();
		switch (mode) {
		case ADMIN: adminMenu(); break;
		case USER: userMenu(); break;
		case EXIT:
			cout << "Bye bestie\n";
			return;
		}
	}
}


