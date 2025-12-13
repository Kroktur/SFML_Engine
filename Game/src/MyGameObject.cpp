#include "MyGameObject.h"

MyGameObject::MyGameObject(BaseComposite* parent) : CollidableRectangleComposite(parent)
{
}

void MyGameObject::OnInit()
{
	GetRectangle()->setSize({ 100,500 });
	GetRectangle()->setFillColor(sf::Color::Red);
	GetRectangle()->setPosition({ 1500,200 });
}

void MyGameObject::Update(float deltatime)
{
	if(movedBack)
		GetRectangle()->move({ +100 * deltatime, 0 });
	else
		GetRectangle()->move({ -200 * deltatime, 0 });
}

void MyGameObject::OnDestroy()
{
}

void MyGameObject::MoveBack()
{
	--vie;
	if (vie == 0)
	{
		movedBack = true;
		GetRectangle()->setFillColor(sf::Color::Green);
	}
}
