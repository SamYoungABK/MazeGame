#pragma once
#include <string>
#include <vector>
#include <set>

using std::vector;
using std::set; using std::pair;

class PlacableActor;
class Player;

struct CollisionPair :
	std::pair< PlacableActor*, PlacableActor*>
{
	CollisionPair(PlacableActor* actor1, PlacableActor* actor2) :
		std::pair<PlacableActor*, PlacableActor*>(actor1, actor2) {};

	bool operator==(CollisionPair rhs)
	{
		return (first == rhs.first && second == rhs.second) ||
			(first == rhs.second && second == rhs.first);
	}
};

class Level
{
	char* m_pLevelData;
	int m_height;
	int m_width;

	std::vector<PlacableActor*> m_pActors;

public:
	Level();
	~Level();

	bool Load(std::string levelName, int* playerX, int* playerY);
	void Draw();
	vector<CollisionPair> UpdateActors(int x, int y, Player* player);

	bool IsSpace(int x, int y);
	bool IsWall(int x, int y);

	int GetHeight() { return m_height; }
	int GetWidth() { return m_width;  }

	static constexpr char WAL = (char)219;

private:
	bool ConvertLevel(int* playerX, int* playerY);
	int GetIndexFromCoordinates(int x, int y);

};