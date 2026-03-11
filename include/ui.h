#pragma once
#include "service.h"
#include "user_service.h"
#include "TrenchCoat.h"
#include "cart_saverCSV.h"
#include "cart_saverHTML.h"

class UI
{
private:
	Service& adminService;
	UserService& userService;

public:
	UI(Service& adminService, UserService& userService);
	void start();

private:
	void adminMenu();
	void userMenu();

	//ADMIN OP
	void addTrenchCoatUI();
	void removeTrenchCoatUI();
	void updateTrenchCoatUI();
	void listAllTrenchCoats();

	//USER OP
	//void addToCartUI();
	void getTrenchCoatsBySizeUI();
	void listAllTrenchCoatsInCartUI();
	void openCartUI();
	
};