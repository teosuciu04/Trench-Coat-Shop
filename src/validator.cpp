#include "validator.h"
#include "validator_exceptions.h"

void Validator::validateTrenchCoat(const string& size, const string& color, const int price, const int quantity, const string& photo)
{
    string errors;
	string sizes[] = { "XS", "S", "M", "L", "XL" };
	bool found = false;

    for (const auto& s : sizes) {
        if (size == s) {
            found = true;
            break;
        }
    }

    if (size.empty() || !found)
        errors += "Invalid size";

    if (color.empty())
        errors += "Invalid color";

    if (price <= 0)
        errors += "Invalid price";

    if (quantity <= 0)
        errors += "Invalid quantity";

    if (photo.empty())
        errors += "Invalid photo";

	if (!errors.empty())
		throw ValidationException(errors);
}



