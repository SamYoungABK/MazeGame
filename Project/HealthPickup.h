#pragma once
#include "PlacableActor.h"
class HealthPickup : public PlacableActor
{
public:
	HealthPickup(int x, int y, int worth);

	int GetWorth() const { return m_worth; }

	virtual ActorType GetType() override { return ActorType::Health; }
	virtual void Draw() override;
private:
	int m_worth;
};

