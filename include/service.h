#pragma once
#include "Repository.h"
#include "file_repository.h"
#include <iostream>
#include <string>
using namespace std;

class Service
{
private:
	Repository& repository;

public:
	Service(Repository& repository) : repository{ repository } {}
	~Service() {}

	//CRUD
	bool addTrenchCoatService(const string& size, const string& color, int price, int quantity, const string& photograph);
	bool removeTrenchCoatService(const string& size, const string& color);
	bool updateTrenchCoatService(const string& size, const string& color, int price, int quantity, const string& photograph);
	
	//Other
	vector<TrenchCoat> getTrenchCoats() const { return repository.getTrenchCoats(); }
	size_t getSize() const { return repository.getSize(); }

	//Populate repo
	void populateRepo();

};