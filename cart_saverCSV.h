#pragma once
#include <fstream>
#include "cart_saver.h"

class CartSaverCSV : public CartSaver
{
private:
	std::string filename;

public:
	CartSaverCSV(const std::string& filename) : filename(filename) {}

    void save(const std::vector<TrenchCoat>& cart) override {
        std::ofstream file(filename);
        for (const auto& coat : cart) {
            file << coat.getSize() << "," << coat.getColor() << ","
                << coat.getPrice() << "," << coat.getQuantity() << ","
                << coat.getPhotograph() << "\n";
        }
        file.close();
    }

	std::string getFilename() const {
		return filename;
	}
};