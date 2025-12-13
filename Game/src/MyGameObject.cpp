#include "MyGameObject.h"

MyGameObject::MyGameObject(BaseComposite* parent) : CollidableRectangleComposite(parent)
{
}

void MyGameObject::OnInit()
{
	GetRectangle()->setSize({ 100,500 });
	GetRectangle()->setFillColor(sf::Color::Green);
	GetRectangle()->setPosition({ 1500,200 });
}

void MyGameObject::Update(float deltatime)
{
}

void MyGameObject::OnDestroy()
{
}
