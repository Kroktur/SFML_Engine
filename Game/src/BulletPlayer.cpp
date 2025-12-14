#include "BulletPlayer.h"

BulletPlayer::BulletPlayer(BaseComposite* parent, KT::Vector2F pos, bool isGoingRight) : CollidableRectangleComposite(parent), m_startPos(pos), IsGoingRight(isGoingRight)
{	
}

void BulletPlayer::OnInit()
{
	GetRectangle()->setSize({ 10*3,5*3 });
	GetRectangle()->setFillColor(sf::Color::White);
	GetRectangle()->setTexture(&TextureLoader::Load("Graine.png", {}, {}));
	if (IsGoingRight)
	{
		GetRectangle()->setPosition({ m_startPos.x + 70,m_startPos.y });
	}
	else 
	{
		GetRectangle()->setPosition({ m_startPos.x + 10,m_startPos.y });
	}
	m_bulletStateMachine = new KT::StateMachine<BulletPlayer>(std::make_unique<MoveBulletState>(this, nullptr), 1);
}

void BulletPlayer::Update(float deltatime)
{
	m_bulletStateMachine->ChangeState();
	m_bulletStateMachine->Update(deltatime);
}

void BulletPlayer::Stop()
{
	isGoingToDie = true;
	DisableCollision(0);

}

void BulletPlayer::OnDestroy()
{
	delete m_bulletStateMachine;
}

bool BulletPlayer::GetIsGoingRight() const { return IsGoingRight; }

bool BulletPlayer::GetIsGoingToDie() const { return isGoingToDie; }

void MoveBulletState::Update(const float& dt)
{

	if (m_entity->GetIsGoingRight())
	{
		m_entity->GetRectangle()->move({ 600.0f * dt, 0 });
	}
	else
	{
		m_entity->GetRectangle()->move({ -600.0f * dt, 0 });
	}
	if(m_entity->GetIsGoingToDie())
	{
		SetNextState<DyingBulletState>(m_animation);
	}
}

void DyingBulletState::Update(const float& dt) 
{
	if (m_livingTime.GetElapsedTime().AsSeconds() > 1)
		m_entity->EnableDeath();
}

void DyingBulletState::OnEnter()
{
	BulletState::OnEnter();
}
