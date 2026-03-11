#pragma once
#include "TrenchCoat.h"
#include <iostream>
#include <string>
#include <vector>
#include "repository_exceptions.h"
using namespace std;

class Repository
{
private:
	std::vector <TrenchCoat>trenchCoats;

public:
	Repository() {}
	virtual ~Repository() {}

	//CRUD
	virtual void addTrenchCoat(const TrenchCoat& trenchCoat);
	virtual void removeTrenchCoat(const string& size, const string& color);
	virtual bool updateTrenchCoat(const string& size, const string& color, TrenchCoat& newTrenchCoat);

	virtual vector<TrenchCoat> getTrenchCoats() const { return trenchCoats; }
	virtual size_t getSize() const { return trenchCoats.size(); };
	virtual size_t findTrenchCoatIndex(const string& size, const string& color);
};