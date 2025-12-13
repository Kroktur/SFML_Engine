#include "MyGameObject.h"

RandomSquare::RandomSquare(BaseComposite* parent): CollidableRectangleComposite(parent)
{
	GetRectangle()->setPosition({ 0,590 });
	GetRectangle()->setSize({ 1920,900 });
}

void RandomSquare::OnInit()
{
}

void RandomSquare::Update(float deltatime)
{
	GetRectangle()->setFillColor(sf::Color::White);
	CollidableRectangleComposite::Update(deltatime);
}

void RandomSquare::OnDestroy()
{

}

Player::Player(BaseComposite* parent): CollidableRectangleComposite(parent)
{}

void Player::OnInit()
{
	m_managerPlayer = new AnimationManager{ "SpriteSheet_Nova.png", KT::Vector2UI(528, 624), KT::Vector2UI(0, 0), KT::Vector2UI(11, 13) };
	m_animationPlayer = new LoopAnimation{ m_managerPlayer,89,94,KT::Chrono<float>::Time::CreateFromValue<KT::ratio<1>>(0.1) };
	GetRectangle()->setPosition({ 400,500 });
	GetRectangle()->setSize({ 100,100 });
	m_animationPlayer->SetTexture(GetRectangle());
}

void Player::Update(float deltatime)
{
	auto rect = GetRectangle();
	m_animationPlayer->UpdateShapeFrame(GetRectangle());


	if (moveRight)
		rect->move({ 200 * deltatime,0 });
	if (moveLeft)
		rect->move({ -200 * deltatime ,0 });
	if (jump && GetRectangle()->getPosition().y >= 500.0f)
	{
		movingUp = true;
	}
	if (GetRectangle()->getPosition().y <= 450.0f)
	{
		movingUp = false;
		movingDown = true;
	}
	if (GetRectangle()->getPosition().y >= 500.0f)
	{
		movingDown = false;
	}
	if(movingUp)
	{
		rect->move({ 0,-400 * deltatime });
	}
	if(movingDown)
	{
		rect->move({ 0,+400 * deltatime });
	}
	CollidableRectangleComposite::Update(deltatime);
}

void Player::Input(const std::optional<sf::Event>& event)
{
	moveLeft = false;
	moveRight = false;
	jump = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		moveRight = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
	{
		moveLeft = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{
		jump = true;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
	{
		if (!shooting)
		{
			shooting = true;
			Bullet* bullet = new Bullet(this);
			bullet->OnInit();
			bullet->GetRectangle()->setPosition({ GetRectangle()->getPosition().x + GetRectangle()->getSize().x, GetRectangle()->getPosition().y + GetRectangle()->getSize().y / 2 });
		}
	}
	else
	{
		shooting = false;
	}
}

Bullet::Bullet(BaseComposite* parent) : CollidableRectangleComposite(parent)
{

}

void Bullet::OnInit()
{
	GetRectangle()->setPosition({ 0,0 });
	GetRectangle()->setSize({ 5,3 });
}

void Bullet::Update(float deltatime)
{
	GetRectangle()->move({ 600 * deltatime,0 });
	CollidableRectangleComposite::Update(deltatime);
}
