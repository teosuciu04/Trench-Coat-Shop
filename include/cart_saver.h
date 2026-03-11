#pragma once
#include<vector>
#include "TrenchCoat.h"

class CartSaver
{
public:
	virtual void save(const std::vector<TrenchCoat>& trenchCoats) = 0;
	virtual ~CartSaver() = default;
};