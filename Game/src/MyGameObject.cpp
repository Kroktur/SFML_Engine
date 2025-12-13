#include "MyGameObject.h"


void Rect::OnInit()
{
	GetRectangle()->setSize({ 100,500 });
	GetRectangle()->setFillColor(sf::Color::Green);
	GetRectangle()->setPosition({ 1800,600 });
}

void Rect::OnDestroy()
{
}

void Rect::Render(float alpha)
{
}

void Rect::Input(const std::optional<sf::Event>& event)
{
}

void Rect::Update(float deltatime)
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
