#include "BulletBusiness.h"
#include "BusinessMan.h"


Bullet::Bullet(BaseComposite* parent,KT::Vector2F pos,bool right) : CollidableRectangleComposite(parent), m_startPos(pos), m_isRight(right)
{

}

void Bullet::OnInit()
{
	GetRectangle()->setSize({ 20,10 });
	GetRectangle()->setFillColor(sf::Color::Yellow);
	GetRectangle()->setPosition({ m_startPos.x,m_startPos.y });
	GetRectangle()->setTexture(&TextureLoader::Load("cigare.png", {}, {}));
	if (m_isRight)
	{
		GetRectangle()->setPosition({ m_startPos.x + 50,m_startPos.y });
	}
	else
	{
		GetRectangle()->setPosition({ m_startPos.x +30,m_startPos.y });
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
	DisableCollision(0);

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

		m_entity->GetRectangle()->move({ 300.0f * dt, 0.0f });

	}
	else {
		m_entity->GetRectangle()->move({ -300.0f * dt, 0.0f });
	}
	if (m_entity->GetIsGoingToDie()) {
		SetNextState<BulletDyingState>(m_animation);
	}

}

void BulletDyingState::Update(const float& dt)
{
	m_animation2->UpdateShapeFrame(m_entity->GetRectangle());
	if (m_lifeTime.GetElapsedTime().AsSeconds() > 0.9f)
		m_entity->EnableDeath();
}

void BulletDyingState::OnEnter()
{
	BusinessBulletState::OnEnter();
	m_manager = new AnimationManager{ "cigare_explosion_sprite_sheet.png", KT::Vector2UI(60, 20), KT::Vector2UI(0, 0), KT::Vector2UI(3, 1) };
	m_animation2 = new LoopAnimation{ m_manager,1,3,KT::Chrono<float>::Time::CreateFromValue<KT::ratio<1>>(0.3f) };
	m_animation2->SetTexture(m_entity->GetRectangle());
	m_entity->GetRectangle()->setSize({ 20 * 3,20 * 3 });
}

void BulletDyingState::OnExit()
{
	BusinessBulletState::OnExit();
	delete m_manager;
	delete m_animation2;
}
