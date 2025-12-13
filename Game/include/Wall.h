#pragma once
#include "ObjectToUse.h"
#include "Core/StateMachine.h"
#include "SFML_Engine_Impl/Animation.h"

class Wall : public CollidableRectangleLeaf
{
public:
	Wall(BaseComposite* parent, const KT::Vector2F& position, const KT::Vector2F& size);
	void OnInit() override;
private:
	KT::Vector2F m_position;
	KT::Vector2F m_size;
};

class WallToBlock : public Wall
{
public:
	WallToBlock(BaseComposite* parent, const KT::Vector2F& position, const KT::Vector2F& size);
};

class WallToDestroy : public Wall
{
public:
	WallToDestroy(BaseComposite* parent, const KT::Vector2F& position, const KT::Vector2F& size);
};
