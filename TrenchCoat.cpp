#include "TrenchCoat.h"
#include <iostream>
#include "Utils.h"

using namespace std;

TrenchCoat::TrenchCoat() {
	this->price = 0;
	this->quantity = 0;
	
}

TrenchCoat::TrenchCoat(string size, string color, int price, int quantity,string  photograph)
	: size(size), color(color), price(price), quantity(quantity), photograph(photograph) {
}

TrenchCoat::TrenchCoat(const TrenchCoat& trenchCoat)
{
	this->size = trenchCoat.size;
	this->color = trenchCoat.color;
	this->price = trenchCoat.price;
	this->quantity = trenchCoat.quantity;
	this->photograph = trenchCoat.photograph;
}

TrenchCoat::~TrenchCoat()
{
}

void TrenchCoat::display() const {
	std::cout << "Trench Coat - Size: " << size << ", Colour: " << color
		<< ", Price: $" << price << ", Quantity: " << quantity
		<< ", Photo: " << photograph << std::endl;
}

bool TrenchCoat::operator==(const TrenchCoat& other) const
{
	return this->size == other.size && this->color == other.color;
}

istream& operator>>(istream& in, TrenchCoat& coat)
{
	string line;
	getline(in, line);
	vector<string> result = split(line, ',');
	if (line.empty()) {
		return in;
	}
	if (result.size() == 5) {
		coat.size = result[0];
		coat.color = result[1];
		coat.price = stoi(result[2]);
		coat.quantity = stoi(result[3]);
		coat.photograph = result[4];
	}
	else {
		throw std::runtime_error("Invalid input format");

	}
	return in;
}
ostream& operator<<(ostream& out, const TrenchCoat& coat)
{
	out << coat.size << "," << coat.color << "," << coat.price << "," << coat.quantity << "," << coat.photograph<<"\n";
	return out;
}
	


