#pragma once
#include "Repository.h"
#include "cart_saver.h"
#include "cart_saverCSV.h"
#include "cart_saverHTML.h"

class UserService {	
private:
	Repository& repository;
	vector<TrenchCoat> cart;
	int sum = 0;

	CartSaver* cartSaver = nullptr;

public:
	UserService(Repository& repository) : repository{ repository } {}

	void setCartSaver(CartSaver* cartSaver) {
		this->cartSaver = cartSaver;
	}
	void saveCart() {
		if (cartSaver) {
			cartSaver->save(cart);
		}
		else {
			cout << "No cart saver set.\n";
		}
	}
	void openCart() const;
	~UserService() {}

	bool AddToCart(TrenchCoat& trenchCoat);
	vector<TrenchCoat> getTrenchCoatsBySize(vector<TrenchCoat> trenchCoats, const string& size);
	vector<TrenchCoat> getCart() const { return cart; }
	int getSum() { return sum; }
	int setSum(int newsum) { return sum = newsum; }

	vector<TrenchCoat> getTrenchCoatsUser() { return repository.getTrenchCoats(); }


};
