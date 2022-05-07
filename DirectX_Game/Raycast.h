#pragma once
#include "CollisionHandler.h"

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
class RaycastUtility //TODO: Change name
{
public:
	bool Raycast(Vector2 origin, Vector2 direction, float maxDistance); //TODO: Add layermask

private:
	bool LineIntersectRectangle(Line ray, Vector2 rectPos, float rectWidth, float rectHeight);
	bool LineIntersectLine(Line line1, Line line2);
	bool OnSegment(Vector2 p, Vector2 q, Vector2 r);
	int GetOrientation(Vector2 p, Vector2 q, Vector2 r);
};