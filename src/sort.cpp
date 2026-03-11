#include "sort.h"

void sortTrenchCoats(std::vector<TrenchCoat>& coats, const Comparator<TrenchCoat>& comparator)
{
    std::sort(coats.begin(), coats.end(),
        [&comparator](const TrenchCoat& a, const TrenchCoat& b) {
            return comparator.compare(a, b);
        });
}
