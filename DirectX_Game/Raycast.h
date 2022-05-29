#pragma once
#include "CollisionHandler.h"
#include "Entity.h"
class Line
{
public:
	Vector2 start;
	Vector2 end;
	Line(Vector2 start, Vector2 end)
	{
		this->start = start;
		this->end = end;
	}
	Line()
	{

	}
};
class RaycastUtility 
{
public:
	static Entity* Raycast(Vector2 origin, Vector2 direction, float maxDistance, int ignoreLayerMask = 0); 

private:
	static bool LineIntersectRectangle(Line ray, Vector2 rectPos, float rectWidth, float rectHeight);
	static bool Intersect(Line line1, Line line2);
};