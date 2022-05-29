#include "Raycast.h"
Entity* RaycastUtility::Raycast(Vector2 origin, Vector2 direction, float maxDistance, int ignoreLayerMask)
{
	Line ray = Line(origin, origin + direction * maxDistance);

	for (Collider* collider : CollisionHandler::GetAllCollidersInLevel())
	{
		if (collider->layer.CollisionMask & ignoreLayerMask) continue;

		if (LineIntersectRectangle(ray, collider->bottomLeftPos, collider->width, collider->height))
		{
			return static_cast<Entity*>(collider->GetOwner());
		}
	}
	return nullptr;
}

bool RaycastUtility::LineIntersectRectangle(Line ray, Vector2 bottomLeftPos, float rectWidth, float rectHeight)
{
	Line linesInRect[4];
	linesInRect[0] = Line(bottomLeftPos, bottomLeftPos + Vector2(0, rectHeight));
	linesInRect[1] = Line(bottomLeftPos, bottomLeftPos + Vector2(rectWidth,0));
	linesInRect[2] = Line(bottomLeftPos + Vector2(rectWidth, rectHeight), bottomLeftPos + Vector2(rectWidth, 0));
	linesInRect[3] = Line(bottomLeftPos + Vector2(rectWidth, rectHeight), bottomLeftPos + Vector2(0, rectHeight));
	for (int i = 0; i < 4; i++)
	{
		if(Intersect(linesInRect[i],ray))
		{
			return true;
		}
	}
	return false;
}

bool RaycastUtility::Intersect(Line line1, Line line2) {
	float x1 = line1.start.x, x2 = line1.end.x, x3 = line2.start.x, x4 = line2.end.x;
	float y1 = line1.start.y, y2 = line1.end.y, y3 = line2.start.y, y4 = line2.end.y;

	float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

	return d != 0;

}

