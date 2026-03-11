#pragma once
#include "file_repository.h"
#include <fstream>
#include <iostream>
using namespace std;

void FileRepository::readFromFile()
{
	std::ifstream file(this->fileName);
	if (!file.is_open()) {
		throw std::runtime_error("Could not open file: " + fileName);
	}
	TrenchCoat coat;
	while (file >> coat) {
		Repository::addTrenchCoat(coat);
	}
	file.close();
}

void FileRepository::writeToFile()
{
	std::ofstream file(fileName);
	if (!file.is_open()) {
		throw std::runtime_error("Could not open file: " + fileName);
	}
	for (auto& coat : this->getTrenchCoats()) {
		file << coat;
	}
	file.close();
}

void FileRepository::addTrenchCoat(const TrenchCoat& coat) {
	Repository::addTrenchCoat(coat);
	writeToFile();
}

void FileRepository::removeTrenchCoat(const string& size, const string& color)
{
	Repository::removeTrenchCoat(size, color);
	writeToFile();
}

bool FileRepository::updateTrenchCoat(const string& size, const string& color, TrenchCoat& newTrenchCoat)
{
 	if (Repository::updateTrenchCoat(size, color, newTrenchCoat))
	{
		writeToFile();
		return true;
	}
	return false;
}

vector<TrenchCoat> FileRepository::getTrenchCoats()
{
	return Repository::getTrenchCoats();
}

size_t FileRepository::getSize()
{
	return Repository::getSize();
}

size_t FileRepository::findTrenchCoatIndex(const string& size, const string& color)
{
	return Repository::findTrenchCoatIndex(size, color);
}
