#include "MyGameObject.h"

Enemy::Enemy(BaseComposite* parent): CollidableRectangleComposite(parent)
{}

void Enemy::OnInit()
{
	movingRight = false;
	m_manager = new AnimationManager{ "SpriteSheet_Nova.png", KT::Vector2UI(528, 624), KT::Vector2UI(0, 0), KT::Vector2UI(11, 13) };
	m_animation = new LoopAnimation{ m_manager,23,31,KT::Chrono<float>::Time::CreateFromValue<KT::ratio<1>>(0.1) };
	m_animation->SetTexture(GetRectangle());
	GetRectangle()->setSize({ 100,100 });
	// place the enemy at the far right
	GetRectangle()->setPosition({ 1809, 500 });
	

}

void Enemy::Update(float deltatime)
{
	
	m_animation->UpdateShapeFrame(GetRectangle());
	auto rect = GetRectangle();
	
	
	if (movingRight)
	{
		rect->move({ 150 * deltatime,0 });
		SetAnimationForDirection(movingRight);

		
	}
	else
		rect->move({ -150 * deltatime,0 });
	    SetAnimationForDirection(movingRight);
	

	


	CollidableRectangleComposite::Update(deltatime);
}

void Enemy::Input(const std::optional<sf::Event>& event)
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

void Enemy::OnDestroy()
{
	delete m_manager;
	delete m_animation;
}

void Enemy::MoveRight()
{
	movingRight = true;
	SetAnimationForDirection(true);
}

void Enemy::SetAnimationForDirection(bool right)
{
	if (right)
	{
		m_animation->SetMinMax(12, 19);
	}
	else
	{
		m_animation->SetMinMax(23, 31);
	}
}
