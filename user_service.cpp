#include "user_service.h"

void UserService::openCart() const
{
	if (!cartSaver) {
		cout << "No cart saver is set.\n";
		return;
	}

	// Downcast to get the filename (if needed)
	std::string command;

	if (auto csvSaver = dynamic_cast<CartSaverCSV*>(cartSaver)) {
		command = "start " + csvSaver->getFilename(); // Windows
	}
	else if (auto htmlSaver = dynamic_cast<CartSaverHTML*>(cartSaver)) {
		command = "start " + htmlSaver->getFilename(); // Windows
	}
	else {
		cout << "Unknown file type.\n";
		return;
	}

	system(command.c_str()); // Launches the file with the default application
}

/// <summary>
/// Function that adds a trench coat to the cart.
/// </summary>
/// <param name="trenchCoat"></param>
/// <returns> true of false</returns>
bool UserService::AddToCart(TrenchCoat& trenchCoat)
{
	// Check if the trench coat already exists in the cart
	for (const auto& coat : this->cart) {
		if (coat == trenchCoat) {
			return false; // Coat already in cart
		}
	}
	this->cart.push_back(trenchCoat);
	this->sum += trenchCoat.getPrice();
	saveCart();	
	return true;
}

/// <summary>
/// Function that filters the trench coats by size.
/// </summary>
/// /// <param name="trenchCoats"></param>
/// /// <param name="size"></param>
/// <returns> a vector of trench coats</returns>
vector<TrenchCoat> UserService::getTrenchCoatsBySize(vector<TrenchCoat> trenchCoats, const string& size)
{
	if (size.empty())
		return trenchCoats;

	vector<TrenchCoat> filteredTrenchCoats;
	for (int i = 0; i < trenchCoats.capacity(); ++i) {
		TrenchCoat coat = trenchCoats[i];
		if (coat.getSize() == size)
			filteredTrenchCoats.push_back(coat);
	}

	return filteredTrenchCoats;	
}
