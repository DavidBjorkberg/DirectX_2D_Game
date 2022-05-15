#pragma once


class Physics
{
public:

	struct Layer
	{
		unsigned int CollisionMask;
		unsigned int CategoryMask;
	};
	inline static Layer GroundLayer;
	inline static Layer PropLayer;
	inline static Layer PlayerLayer;

	static void InitializeLayers()
	{
		GroundLayer.CollisionMask	= 0b00000001;
		GroundLayer.CategoryMask	= 0;

		PropLayer.CollisionMask		= 0b00000010;
		PropLayer.CategoryMask		= 0b00000011;

		PlayerLayer.CollisionMask	= 0b00000100;
		PlayerLayer.CategoryMask	= 0b00000111;
	}
};