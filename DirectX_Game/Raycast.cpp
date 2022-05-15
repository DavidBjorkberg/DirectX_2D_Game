#include "Raycast.h"
bool RaycastUtility::Raycast(Vector2 origin, Vector2 direction, float maxDistance, int ignoreLayerMask)
{
	Line ray = Line(origin, origin + direction * maxDistance);

	for (Collider* collider : CollisionHandler::GetAllCollidersInLevel())
	{
		if (collider->layer.CollisionMask & ignoreLayerMask) continue;

		if (LineIntersectRectangle(ray, collider->bottomLeftPos, collider->width, collider->height))
		{
			return true;
		}
	}
	return false;
}

bool RaycastUtility::LineIntersectRectangle(Line ray, Vector2 rectPos, float rectWidth, float rectHeight)
{
	Line linesInRect[4];
	linesInRect[0] = Line(rectPos + (Vector2(-rectWidth, -rectHeight) / 2), rectPos + (Vector2(-rectWidth, rectHeight) / 2));
	linesInRect[1] = Line(rectPos + (Vector2(-rectWidth, -rectHeight) / 2), rectPos + (Vector2(rectWidth, -rectHeight) / 2));
	linesInRect[2] = Line(rectPos + (Vector2(-rectWidth, rectHeight) / 2), rectPos + (Vector2(rectWidth, rectHeight) / 2));
	linesInRect[3] = Line(rectPos + (Vector2(rectWidth, -rectHeight) / 2), rectPos + (Vector2(rectWidth, rectHeight) / 2));
	for (int i = 0; i < 4; i++)
	{
		if (LineIntersectLine(linesInRect[i], ray))
		{
			return true;
		}
	}
	return false;
}

bool RaycastUtility::LineIntersectLine(Line line1, Line line2)
{
	int o1 = GetOrientation(line1.start, line1.end, line2.start);
	int o2 = GetOrientation(line1.start, line1.end, line2.end);
	int o3 = GetOrientation(line2.start, line2.end, line1.start);
	int o4 = GetOrientation(line2.start, line2.end, line1.end);

	if (o1 != o2 && o3 != o4)
	{
		return true;
	}
	//Special cases
	if (o1 == 0 && OnSegment(line1.start, line2.start, line1.end))
	{
		return true;
	}
	if (o2 == 0 && OnSegment(line1.start, line2.end, line1.end))
	{
		return true;
	}
	if (o3 == 0 && OnSegment(line2.start, line1.start, line2.end))
	{
		return true;
	}
	if (o4 == 0 && OnSegment(line2.start, line1.end, line2.end))
	{
		return true;
	}
	return false;
}

bool RaycastUtility::OnSegment(Vector2 p, Vector2 q, Vector2 r)
{
	if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
		q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
	{
		return true;
	}

	return false;
}

//Returns orientation of the three points: 0 -> Collinear, 1 -> clockwise, 2 -> counterclockwise
int RaycastUtility::GetOrientation(Vector2 p, Vector2 q, Vector2 r)
{
	int val = (q.y - p.y) * (r.x - q.x) -
		(q.x - p.x) * (r.y - q.y);

	if (val == 0)
	{
		return 0;  // collinear
	}

	return val > 0 ? 1 : 2; // clock or counterclockwise

}
