#include "Wall.h"

Wall::Wall(BaseComposite* parent, const KT::Vector2F& position, const KT::Vector2F& size) : CollidableRectangleLeaf(parent), m_position(position), m_size(size)
{

}

void Wall::OnInit()
{
	GetRectangle()->setPosition({ m_position.x,m_position.y});
	GetRectangle()->setSize({ m_size.x,m_size.y });
	//DisableMainRender();
}
