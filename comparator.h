#pragma once
#include "TrenchCoat.h"
#include <vector>
#include <algorithm>

template <typename T>
class Comparator
{
public:
	virtual bool compare(const T& a, const T& b) const = 0;
	virtual ~Comparator() = default;
};

class ComparatorAscendingByPrice : public Comparator<TrenchCoat> {
public:
    bool compare(const TrenchCoat& a, const TrenchCoat& b) const override {
        return a.getPrice() < b.getPrice();
    }
};

class ComparatorDescendingByQuantity : public Comparator<TrenchCoat> {
public:
    bool compare(const TrenchCoat& a, const TrenchCoat& b) const override {
        return a.getQuantity() < b.getQuantity();
    }
};

