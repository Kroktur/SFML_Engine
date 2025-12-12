#include "MyGameObject.h"

RandomSquare::RandomSquare(BaseComposite* parent): CollidableRectangleComposite(parent)
{}

void RandomSquare::OnInit()
{
	m_manager = new AnimationManager{ "SpriteSheet_Nova.png", KT::Vector2UI(528, 624), KT::Vector2UI(0, 0), KT::Vector2UI(11, 13) };
	m_animation = new LoopAnimation{ m_manager,1,10,KT::Chrono<float>::Time::CreateFromValue<KT::ratio<1>>(0.1) };
	m_animation->SetTexture(GetRectangle());
	GetRectangle()->setSize({ 100,100 });
	GetRectangle()->move({ 100,4 });
	GetRectangle()->rotate(sf::degrees(23));
}

void RandomSquare::Update(float deltatime)
{
	m_animation->UpdateShapeFrame(GetRectangle());
	GetRectangle()->setFillColor(sf::Color::White);
	CollidableRectangleComposite::Update(deltatime);
}

void RandomSquare::OnDestroy()
{
	delete m_manager;
	delete m_animation;
}

Player::Player(BaseComposite* parent): CollidableRectangleComposite(parent)
{}

void Player::OnInit()
{
	GetRectangle()->setSize({ 100,100 });
	GetRectangle()->move({ 400,4 });
	GetRectangle()->rotate(sf::degrees(23));
}

void Player::Update(float deltatime)
{
	auto rect = GetRectangle();


	if (ZQSD[0])
		rect->move({ 0,-100 * deltatime });
	if (ZQSD[1])
		rect->move({ -100 * deltatime ,0 });
	if (ZQSD[2])
		rect->move({ 0,100 * deltatime });
	if (ZQSD[3])
		rect->move({ 100 * deltatime,0 });


	CollidableRectangleComposite::Update(deltatime);
}

void Player::Input(const std::optional<sf::Event>& event)
{
	ZQSD[0] = false;
	ZQSD[1] = false;
	ZQSD[2] = false;
	ZQSD[3] = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
	{
		ZQSD[0] = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
	{
		ZQSD[1] = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		ZQSD[2] = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		ZQSD[3] = true;
	}
}
