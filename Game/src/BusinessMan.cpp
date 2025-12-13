#include "BusinessMan.h"
#include "GameScene.h"
#include"MyPlayer.h"
#include "cmath"
#include "BulletBusiness.h"
BusinessMan::BusinessMan(BaseComposite* parent, float capY) : CollidableRectangleComposite(parent), m_capY(capY), m_playerStateMachine(nullptr), m_manager(nullptr), m_animation(nullptr)
{
}

void BusinessMan::OnDestroy()
{
	delete m_playerStateMachine;
	delete m_manager;
	delete m_animation;
}

void BusinessMan::OnInit()
{
	GetRectangle()->setSize({ 55 * 3,80*3 });
	GetRectangle()->setPosition({ 500,m_capY });
	m_manager = new AnimationManager{ "SpriteSheet_Nova.png", KT::Vector2UI(528, 624), KT::Vector2UI(0, 0), KT::Vector2UI(11, 13) };
	m_animation = new LoopAnimation{ m_manager,1,10,KT::Chrono<float>::Time::CreateFromValue<KT::ratio<1>>(0.1f) };
	m_animation->SetTexture(GetRectangle());
	m_playerStateMachine = new KT::StateMachine<BusinessMan>(std::make_unique<BusinessManIdleState>(this, m_animation), 1);
}

float BusinessMan::GetCapY() const
{
	return m_capY;
}

void BusinessMan::Update(float deltatime)
{

	m_playerStateMachine->ChangeState();
	m_playerStateMachine->Update(deltatime);
	if (m_coolDown.GetElapsedTime().AsSeconds() > 1.5f)
	{

		auto player = GetMyScene()->GetPlayer();
		auto PlayerPos = player->GetRectangle()->getPosition();

		auto BusinessPos = GetRectangle()->getPosition();

		bool IsRight = PlayerPos.x > BusinessPos.x;

		auto bullet = new Bullet(this, { GetRectangle()->getPosition().x , GetRectangle()->getPosition().y}, IsRight);
		bullet->OnInit();
		m_coolDown.Reset();
	}

}

void BusinessMan::Render(float alpha)
{
	m_playerStateMachine->Render(alpha);
}

void BusinessMan::Input(const std::optional<sf::Event>& event)
{
	m_playerStateMachine->ProcessInput();
}

GameScene* BusinessMan::GetMyScene() const
{
		return dynamic_cast<GameScene*>(GetScene());
	
}

BusinessManState::BusinessManState(BusinessMan* owner, LoopAnimation* anim) : KT::IState<BusinessMan>(owner), m_animation(anim)
{
}


BusinessManIdleState::BusinessManIdleState(BusinessMan* owner, LoopAnimation* anim) : BusinessManState(owner, anim)
{
}


void BusinessManIdleState::Update(const float& dt)
{
	auto player = m_entity->GetMyScene()->GetPlayer();
	player->GetRectangle()->getPosition();

	m_animation->UpdateShapeFrame(m_entity->GetRectangle());

	if (player->GetRectangle()->getPosition().x > m_entity->GetRectangle()->getPosition().x)
	{
		SetNextState<BusinessManRightState>(m_animation);
	}
	else if (player->GetRectangle()->getPosition().x < m_entity->GetRectangle()->getPosition().x)
	{
		SetNextState<BusinessManLeftState>(m_animation);
	}
}


void BusinessManIdleState::OnEnter()
{
	m_animation->SetMinMax(1, 10);
}



void BusinessManRightState::Update(const float& dt)
{
	auto player = m_entity->GetMyScene()->GetPlayer();
	player->GetRectangle()->getPosition();

	m_animation->UpdateShapeFrame(m_entity->GetRectangle());

	if (player->GetRectangle()->getPosition().x < m_entity->GetRectangle()->getPosition().x)
	{
		SetNextState<BusinessManLeftState>(m_animation);
	}
	else if (player->GetRectangle()->getPosition().x == m_entity->GetRectangle()->getPosition().x)
	{
		SetNextState<BusinessManIdleState>(m_animation);
	}
	else
	{
		auto potentialX = m_entity->GetRectangle()->getPosition().x + 100 * dt;
		auto playerX = player->GetRectangle()->getPosition().x;
		float x = std::min(potentialX, playerX);
		m_entity->GetRectangle()->setPosition({ x,m_entity->GetCapY()});
	}
}


BusinessManRightState::BusinessManRightState(BusinessMan* owner, LoopAnimation* anim) : BusinessManState(owner, anim)
{
}

void BusinessManRightState::OnEnter()
{
	m_animation->SetMinMax(12, 20);

}
BusinessManLeftState::BusinessManLeftState(BusinessMan* owner, LoopAnimation* anim) : BusinessManState(owner, anim)
{

}

void BusinessManLeftState::Update(const float& dt)
{
	auto player = m_entity->GetMyScene()->GetPlayer();
	player->GetRectangle()->getPosition();
	m_animation->UpdateShapeFrame(m_entity->GetRectangle());
	if (player->GetRectangle()->getPosition().x > m_entity->GetRectangle()->getPosition().x)
	{
		SetNextState<BusinessManRightState>(m_animation);
	}
	else if (player->GetRectangle()->getPosition().x == m_entity->GetRectangle()->getPosition().x)
	{
		SetNextState<BusinessManIdleState>(m_animation);
	}
	else
	{
		auto potentialX = m_entity->GetRectangle()->getPosition().x - 100 * dt;
		auto playerX = player->GetRectangle()->getPosition().x;
		float x = std::max(potentialX, playerX);
		m_entity->GetRectangle()->setPosition({ x,m_entity->GetCapY() });
	}
}

void BusinessManLeftState::OnEnter()
{
	m_animation->SetMinMax(23, 31);
}



