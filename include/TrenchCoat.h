#pragma once
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
using namespace std;

class TrenchCoat
{
private:
	string size;
	string color;
	int price;
	int quantity;
	string photograph;

public:
	//constructor, copy, destructor
	TrenchCoat();
	TrenchCoat(string size, string color, int price, int quantity, string photograph);
	TrenchCoat(const TrenchCoat& trenchCoat);
	~TrenchCoat();

	void display() const;

	//getters
	string getSize() const { return size; }
	string getColor() const { return color; }
	int getPrice() const { return price; }
	int getQuantity() const { return quantity; }
	string getPhotograph() const { return photograph; }

	//operators
	bool operator==(const TrenchCoat& other) const;

	//setters
	void setSize(const string& size) { this->size = size; }
	void setColor(const string& color) { this->color = color; }
	void setPrice(int price) { this->price = price; }
	void setQuantity(int quantity) { this->quantity = quantity; }
	void setPhotograph(const string& photograph) { this->photograph = photograph; }

	friend istream& operator>>(istream& in, TrenchCoat& coat);
	friend ostream& operator<<(ostream& in, const TrenchCoat& coat);

};