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
	m_animation->UpdateShapeFrame(m_entity->GetRectangle());
	if (m_livingTime.GetElapsedTime().AsSeconds() > 0.9f)
		m_entity->EnableDeath();
}

void DyingBulletState::OnEnter()
{
	BulletState::OnEnter();
	m_manager = new AnimationManager{ "graine_explosion_sprite_sheet.png", KT::Vector2UI(60, 20), KT::Vector2UI(0, 0), KT::Vector2UI(3, 1) };
	m_animation = new LoopAnimation{ m_manager,1,3,KT::Chrono<float>::Time::CreateFromValue<KT::ratio<1>>(0.3f) };
	m_animation->SetTexture(m_entity->GetRectangle());
	m_entity->GetRectangle()->setSize({ 20 * 3,20 *3});
}

void DyingBulletState::OnExit()
{
	BulletState::OnExit();
	delete m_manager;
	delete m_animation;
}
