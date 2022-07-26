#include "HealthPickup.h"

#include <iostream>

using std::cout;

HealthPickup::HealthPickup(int x, int y, int worth)
	: PlacableActor(x, y)
	, m_worth(worth) {}

void HealthPickup::Draw()
{
	std::cout << "H";
}