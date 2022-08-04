#pragma once
#include "Point.h"

enum class ActorColor
{
	Regular = 7,
	Blue = 9,
	Green = 10,
	Red = 12,
	SolidGreen = 34,
	SolidRed = 68,
	SolidBlue = 153
};

enum class ActorType
{
	Door,
	Enemy,
	Goal,
	Key,
	Money,
	Player,
	Health
};

class PlacableActor
{
	bool m_skipNextPosUpdate = false;

public:
	PlacableActor(int x, int y, ActorColor color = ActorColor::Regular);
	virtual ~PlacableActor();

	int GetXPosition();
	int GetYPosition();
	int* GetXPositionPointer();
	int* GetYPositionPointer();
	void SetPosition(int x, int y);
	void SkipNextPositionUpdate() { m_skipNextPosUpdate = true; };

	bool IsOverlapping(int x, int y) { return (GetXPosition() == x && GetYPosition() == y); }
	bool IsOverlapping(PlacableActor* actor) { return (GetXPosition() == actor->GetXPosition() && GetYPosition() == actor->GetYPosition()); }

	ActorColor GetColor() { return m_color; }

	void Remove() { m_IsActive = false; }
	bool IsActive() { return m_IsActive; }
	void Place(int x, int y);

	virtual ActorType GetType() = 0;
	virtual void Draw() = 0;
	virtual void Update()
	{

	}
	virtual void HandleCollision(PlacableActor* collidedActor) {};

protected:
	Point* m_pPosition;

	bool m_IsActive;
	ActorColor m_color;
};