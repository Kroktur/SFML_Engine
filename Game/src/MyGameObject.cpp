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
	m_managerPlayer = new AnimationManager{ "SpriteSheet_Nova.png", KT::Vector2UI(528, 624), KT::Vector2UI(0, 0), KT::Vector2UI(11, 13) };
	m_animationPlayer = new LoopAnimation{ m_managerPlayer,89,94,KT::Chrono<float>::Time::CreateFromValue<KT::ratio<1>>(0.1) };
	GetRectangle()->setPosition({ 400,400 });
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
	if (jump && GetRectangle()->getPosition().y == 400.0f)
	{
		movingUp = true;
	}
	if (GetRectangle()->getPosition().y <= 350.0f)
	{
		movingUp = false;
		movingDown = true;
	}
	if (GetRectangle()->getPosition().y >= 400.0f)
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
}
