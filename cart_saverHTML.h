#pragma once
#include "cart_saver.h"
#include <fstream>

class CartSaverHTML : public CartSaver {
private:
    std::string filename;

public:
    CartSaverHTML(std::string filename) : filename{ std::move(filename) } {}

    void save(const std::vector<TrenchCoat>& cart) override {
        std::ofstream file(filename);
        file << "<!DOCTYPE html><html><body>\n";
        file << "<table border='1'>\n";
        file << "<tr><th>Size</th><th>Color</th><th>Price</th><th>Quantity</th><th>Photo</th></tr>\n";
        for (const auto& coat : cart) {
            file << "<tr><td>" << coat.getSize() << "</td>"
                << "<td>" << coat.getColor() << "</td>"
                << "<td>" << coat.getPrice() << "</td>"
                << "<td>" << coat.getQuantity() << "</td>"
                << "<td><a href='" << coat.getPhotograph() << "'>Link</a></td></tr>\n";
        }
        file << "</table>\n</body></html>\n";
        file.close();
    }

	std::string getFilename() const {
		return filename;
	}
};
