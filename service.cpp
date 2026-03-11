#pragma once
#include "repository.h"
#include "service.h"
#include "validator.h"
#include <iostream>

using namespace std;

/// <summary>
/// Function that adds a trench coat to the repository.
/// </summary>
/// <param name="trenchCoat"></param>
/// <returns> true if it was added, false if it already exists</returns>
bool Service::addTrenchCoatService(const string& size, const string& color, int price, int quantity, const string& photograph)
{
	Validator::validateTrenchCoat(size, color, price, quantity, photograph);
	// Check if the coat already exists
	int index = this->repository.findTrenchCoatIndex(size, color);
	if (index != -1) {
		return false;
	}
	TrenchCoat trenchCoat{ size,color,price,quantity,photograph };
	this->repository.addTrenchCoat(trenchCoat);
	return true;
}

/// <summary>
/// Function that removes a trench coat from the repository.
/// </summary>
/// <param name="size"></param>
/// <param name="color"></param>
/// <returns>true if it was removed false if the coat doesn't exist</returns>
bool Service::removeTrenchCoatService(const string& size, const string& color)
{
    try {
		this->repository.removeTrenchCoat(size, color);
	}
    catch (const RepositoryException& e) {
        cout << "Trench coat not found!" << endl;
        return false;
    }
	return true;
}

/// <summary>
/// Function that updates a trench coat in the repository.
/// </summary>
/// <param name="size"></param>
/// <param name="color"></param>
/// <param name="newTrenchCoat"></param>
/// <returns>true if it was updated false otherwise</returns>
bool Service::updateTrenchCoatService(const string& size, const string& color, int price, int quantity, const string& photograph)
{
    Validator::validateTrenchCoat(size, color, price, quantity, photograph);
    TrenchCoat newtrenchCoat{ size,color,price,quantity,photograph };
    return this->repository.updateTrenchCoat(size, color, newtrenchCoat);
}

void Service::populateRepo()
{
    this->addTrenchCoatService("M", "Red", 150, 10, "https://example.com/redcoat.jpg");
    this->addTrenchCoatService("L", "Blue", 200, 5, "https://example.com/bluecoat.jpg");
    this->addTrenchCoatService("S", "Black", 180, 8, "https://example.com/blackcoat.jpg");
    this->addTrenchCoatService("XL", "White", 220, 4, "https://example.com/whitecoat.jpg");
    this->addTrenchCoatService("XS", "Green", 170, 6, "https://example.com/greencoat.jpg");
    this->addTrenchCoatService("M", "Gray", 160, 7, "https://example.com/graycoat.jpg");
    this->addTrenchCoatService("L", "Yellow", 190, 3, "https://example.com/yellowcoat.jpg");
    this->addTrenchCoatService("S", "Pink", 175, 9, "https://example.com/pinkcoat.jpg");
    this->addTrenchCoatService("XL", "Brown", 210, 2, "https://example.com/browncoat.jpg");
    this->addTrenchCoatService("S", "Purple", 165, 5, "https://example.com/purplecoat.jpg");
}
