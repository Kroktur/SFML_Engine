#include "MyGameObject.h"
#include "SFML_Engine_Impl/ISFMLScene.h"

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

void BackGround::OnInit()
{
	RectangleComposite::OnInit();
	GetRectangle()-> setSize({ static_cast<float>(GetScene()->GetWindow().getSize().x), static_cast<float>(GetScene()->GetWindow().getSize().y) });
	GetRectangle()->setTexture(&TextureLoader::Load("map_que_jai_pas_perdu.png",{},{}));
}
