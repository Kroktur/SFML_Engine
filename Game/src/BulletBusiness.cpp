#include "BulletBusiness.h"
#include "BusinessMan.h"


Bullet::Bullet(BaseComposite* parent,KT::Vector2F pos,bool right) : CollidableRectangleComposite(parent), m_startPos(pos), m_isRight(right)
{

}

void Bullet::OnInit()
{
	GetRectangle()->setSize({ 10,5 });
	GetRectangle()->setFillColor(sf::Color::Yellow);
	GetRectangle()->setPosition({ m_startPos.x,m_startPos.y });
	if (m_isRight)
	{
		GetRectangle()->setPosition({ m_startPos.x + 50,m_startPos.y + 50 });
	}
	else
	{
		GetRectangle()->setPosition({ m_startPos.x +30,m_startPos.y +50 });
	}
	m_bulletStateMachine = new KT::StateMachine<Bullet>(std::make_unique<BulletMoveState>(this, nullptr), 1);
}




void Bullet::Update(float deltatime)
{
	m_bulletStateMachine->ChangeState();
	m_bulletStateMachine->Update(deltatime);

	//// check if BusinessMan is facing right or left and move accordingly
	//if (m_isRight)
	//{
	//	GetRectangle()->move({ 500 * deltatime ,0 });
	//}
	//else
	//{
	//	GetRectangle()->move({ -500 * deltatime ,0 });
	//}
}

void Bullet::Stop()
{
	m_isGoingToDie = true;
}

void Bullet::OnDestroy()
{
	delete m_bulletStateMachine;
}

bool Bullet::GetIsGoingRight() const
{
	return m_isRight;
}

bool Bullet::GetIsGoingToDie() const
{
	return m_isGoingToDie;
}

void BulletMoveState::Update(const float& dt)
{
	if (m_entity->GetIsGoingRight()) {

		m_entity->GetRectangle()->move({ 600.0f * dt, 0.0f });

	}
	else {
		m_entity->GetRectangle()->move({ -600.0f * dt, 0.0f });
	}
	if (m_entity->GetIsGoingToDie()) {
		SetNextState<BulletDyingState>(m_animation);
	}

}

void BulletDyingState::Update(const float& dt)
{
	if(m_lifeTime.GetElapsedTime().AsSeconds() > 1)
	{
		m_entity->EnableDeath();
	}
}
