#pragma once

#include "Repository.h"
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

/// <summary>
/// Function that adds a trench coat to the repository.
/// </summary>
/// <param name="trenchCoat"></param>
/// <returns> true if it was added, false if it already exists</returns>
void Repository::addTrenchCoat(const TrenchCoat& trenchCoat)
{
	// Check if the trench coat already exists in the repository
	this->trenchCoats.push_back(trenchCoat);
}   

/// <summary>
/// Function that removes a trench coat from the repository.
/// </summary>
/// <param name="size"></param>
/// <param name="color"></param>
/// <returns>true if it was removed false if the coat doesn't exist</returns>
void Repository::removeTrenchCoat(const string& size, const string& color)
{
    auto it = find_if(trenchCoats.begin(), trenchCoats.end(), [&](TrenchCoat c) {return c.getSize() == size && c.getColor() == color; });
	if (it != trenchCoats.end()) {
		trenchCoats.erase(it);
	}
	else {
		//cout << "Trench coat not found!" << endl;
		throw RepositoryException("Trench coat not found!");
	}
}
/// <summary>
/// Function that updates a trench coat in the repository.
/// </summary>
/// <param name="size"></param>
/// <param name="color"></param>
/// <param name="newTrenchCoat"></param>
/// <returns>true if it was updated false otherwise</returns>
bool Repository::updateTrenchCoat(const string& size, const string& color, TrenchCoat& newTrenchCoat)
{
    int index = findTrenchCoatIndex(size, color);
    if (index == -1)
		return false;
	
	int price = newTrenchCoat.getPrice();
	int quantity = newTrenchCoat.getQuantity();
	string photograph = newTrenchCoat.getPhotograph();
	this->trenchCoats[index].setPrice(price);
	this->trenchCoats[index].setQuantity(quantity);
	this->trenchCoats[index].setPhotograph(photograph);
    return true;
}

size_t Repository::findTrenchCoatIndex(const string& size, const string& color)
{
   /* for (int i = 0; i < trenchCoats.capacity(); ++i) {
        TrenchCoat coat = trenchCoats[i];
        if (coat.getSize() == size && coat.getColor() == color)
            return i;
    }
    return -1;*/
	auto it = find_if(trenchCoats.begin(), trenchCoats.end(), [&](TrenchCoat c) {return c.getSize() == size && c.getColor() == color; });
	if (it != trenchCoats.end()) {
		return distance(trenchCoats.begin(), it);
	}
	else {
		return -1;
	}
}

//int Repository::findTrenchCoat(const string& size, const string& color)

