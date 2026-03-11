#pragma once
#include <string.h>
#include <stdexcept>
using namespace std;

class Validator {
public:
	static void validateTrenchCoat(const string& size, const string& color, const int price, const int quantity, const string& photo);
};

