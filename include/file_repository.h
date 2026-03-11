#pragma once
#include "repository.h"

class FileRepository : public Repository {
	std::string fileName;
	void readFromFile();
	void writeToFile();

public:
	FileRepository(std::string fileName) : fileName(fileName) {
		readFromFile();
	}
	void addTrenchCoat(const TrenchCoat& coat);
	void removeTrenchCoat(const string& size, const string& color);
	bool updateTrenchCoat(const string& size, const string& color, TrenchCoat& newTrenchCoat);
	vector<TrenchCoat> getTrenchCoats();
	size_t getSize();
	size_t findTrenchCoatIndex(const string& size, const string& color);


};
