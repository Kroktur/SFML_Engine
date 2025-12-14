#include "MyGameObject.h"

#include "GameScene.h"
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
}

void BackGround::Update(float deltatime)
{
	if (hasWinn)
		return;
	if (m_scored <= 0)
	{
		throw std::runtime_error("ARRETEZ DE POLLUER");
	}
	if (m_scored > 5* factor)
	{
		if (m_scored >= 60)
			hasWinn = true;
		GetRectangle()->setTexture(&TextureLoader::Load("map 6.png", {}, {}));
	}else if (m_scored > 4*factor)
	{
		GetRectangle()->setTexture(&TextureLoader::Load("map 5.png", {}, {}));

	}
	else if (m_scored > 3*factor)
	{
		GetRectangle()->setTexture(&TextureLoader::Load("map 4.png", {}, {}));

	}
	else if (m_scored > 2*factor)
	{
		GetRectangle()->setTexture(&TextureLoader::Load("map 3.png", {}, {}));


	}
	else if (m_scored > 1*factor)
	{
		GetRectangle()->setTexture(&TextureLoader::Load("map 2.png", {}, {}));


	}
	else 
	{
		GetRectangle()->setTexture(&TextureLoader::Load("map 1.png", {}, {}));

	}
}

void BackGround::AddScore()
{
	m_scored++;
}

void BackGround::RemoveScore()
{
	m_scored--;
}

bool BackGround::HasWinn()
{
	return hasWinn;
}
