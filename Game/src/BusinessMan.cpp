#include "BusinessMan.h"
#include "GameScene.h"
#include"MyPlayer.h"
#include "cmath"
#include "BulletBusiness.h"
BusinessMan::BusinessMan(BaseComposite* parent, float capY) : CollidableRectangleComposite(parent), m_capY(capY), m_playerStateMachine(nullptr), m_manager(nullptr), m_animation(nullptr),lives(3),m_isAGoodGuy(false)
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
	float x;
	auto randNumb = m_random.getRandomNumber(0, 1);
	if (randNumb == 0)
	{
		x = 1920.0f;
	}
	else
	{
		x = -170.0f;
	}
	GetRectangle()->setSize({ 55 * 3,80*3 });
	GetRectangle()->setPosition({ x,m_capY });
	m_manager = new AnimationManager{ "Businessman_sprite_sheet.png", KT::Vector2UI(440, 480), KT::Vector2UI(0, 0), KT::Vector2UI(8, 6) };
	m_animation = new LoopAnimation{ m_manager,9,17,KT::Chrono<float>::Time::CreateFromValue<KT::ratio<1>>(0.1f) };
	m_animation->SetTexture(GetRectangle());
	m_playerStateMachine = new KT::StateMachine<BusinessMan>(std::make_unique<BusinessIdleLeft>(this, m_animation), 1);
}

float BusinessMan::GetCapY() const
{
	return m_capY;
}

float BusinessMan::GetSpeed()
{
	return 75.0f;
}

void BusinessMan::Update(float deltatime)
{

	m_playerStateMachine->ChangeState();
	m_playerStateMachine->Update(deltatime);
	if (m_hitTimer.GetElapsedTime().AsSeconds() > 0.25f)
	{
		GetRectangle()->setFillColor(sf::Color{ 255,255,255,255 });
		m_hitTimer.Pause();
		m_hitTimer.Reset();
	}
	

}

void BusinessMan::Render(float alpha)
{
	m_playerStateMachine->Render(alpha);
}

void BusinessMan::Attack()
{
	auto player = GetMyScene()->GetPlayer();
	auto PlayerPos = player->GetRectangle()->getPosition();

	auto BusinessPos = GetRectangle()->getPosition();

	bool IsRight = PlayerPos.x > BusinessPos.x;
	Bullet* bullet;
	if (IsRight)
	 bullet = new Bullet(this, { GetRectangle()->getPosition().x + 55, GetRectangle()->getPosition().y + 100 }, IsRight);
	else
		 bullet = new Bullet(this, { GetRectangle()->getPosition().x , GetRectangle()->getPosition().y + 100 }, IsRight);

	bullet->OnInit();
}

void BusinessMan::Input(const std::optional<sf::Event>& event)
{
	m_playerStateMachine->ProcessInput();
}

GameScene* BusinessMan::GetMyScene() const
{
		return dynamic_cast<GameScene*>(GetScene());
	
}

void BusinessMan::HitBusinessMan()
{
	--lives;
	if (lives <= 0)
	{
		m_isAGoodGuy = true;
		DisableCollision(0);
		static_cast<GameScene*>(GetScene())->AddScore();
	}
	 if (lives >= 0)
	{
		GetRectangle()->setFillColor(sf::Color::Green);
		m_hitTimer.Resume();
		m_hitTimer.Reset();
	}
}

bool BusinessMan::GetIsAGoodGuy() const 
{
	return m_isAGoodGuy;
}

BusinessManState::BusinessManState(BusinessMan* owner, LoopAnimation* anim) : KT::IState<BusinessMan>(owner), m_animation(anim)
{
}


BaseBusinessIdle::BaseBusinessIdle(BusinessMan* owner, LoopAnimation* anim) : BusinessManState(owner, anim)
{

}

void BaseBusinessIdle::Update(const float& dt)
{
	m_animation->UpdateShapeFrame(m_entity->GetRectangle());
	auto player = m_entity->GetMyScene()->GetPlayer();
	if (!player)
		return;
	auto pos = player->GetRectangle()->getPosition();
	if (pos.x > m_entity->GetRectangle()->getPosition().x)
	{
		SetNextState<BusinessMoveRight>(m_animation);
	}
	if (pos.x < m_entity->GetRectangle()->getPosition().x)
	{
		SetNextState<BusinessMoveLeft>(m_animation);
	}
	
}

BusinessIdleLeft::BusinessIdleLeft(BusinessMan* owner, LoopAnimation* anim) : BaseBusinessIdle(owner, anim)
{
}

void BusinessIdleLeft::OnEnter()
{
	BaseBusinessIdle::OnEnter();
}

BusinessIdleRight::BusinessIdleRight(BusinessMan* owner, LoopAnimation* anim) : BaseBusinessIdle(owner, anim)
{
}

void BusinessIdleRight::OnEnter()
{
	BaseBusinessIdle::OnEnter();
}

BaseBusinessMove::BaseBusinessMove(BusinessMan* owner, LoopAnimation* anim,float dirFactor) : BusinessManState(owner, anim),m_dirFactor(dirFactor)
{
}

void BaseBusinessMove::Update(const float& dt)
{
	BusinessManState::Update(dt);
	m_animation->UpdateShapeFrame(m_entity->GetRectangle());
	auto player = m_entity->GetMyScene()->GetPlayer();
	if (!player)
		return;
}

BusinessMoveLeft::BusinessMoveLeft(BusinessMan* owner, LoopAnimation* anim) : BaseBusinessMove(owner, anim,-1)
{
}

void BusinessMoveLeft::OnEnter()
{
	BaseBusinessMove::OnEnter();
	m_animation->SetMinMax(9, 16);
	m_animation->SetAnimationTime(KT::Chrono<float>::Time::CreateFromValue<KT::ratio<1>>(0.2f));
}

void BusinessMoveLeft::Update(const float& dt)
{
	BaseBusinessMove::Update(dt);
	auto player = m_entity->GetMyScene()->GetPlayer();
	if (!player)
		return;
	if (player->GetRectangle()->getPosition().x > m_entity->GetRectangle()->getPosition().x)
	{
		SetNextState<BusinessMoveRight>(m_animation);
	}

	if ((player->GetRectangle()->getPosition() - m_entity->GetRectangle()->getPosition()).length() < 800 && m_coolDown.GetElapsedTime().AsSeconds() > 1.0f)
	{
		// on peux tirer
		auto randNum = m_random.getRandomNumber(1, 6);
		if (randNum == 2 || randNum == 4)
		{
			SetNextState<BusinessAtackLeft>(m_animation);
		}
		m_coolDown.Reset();
	}
	auto potentialX = m_entity->GetRectangle()->getPosition().x +  -m_entity->GetSpeed() * dt;
	auto playerX = player->GetRectangle()->getPosition().x;
	float x = std::max(potentialX, playerX);
	m_entity->GetRectangle()->setPosition({ x,m_entity->GetCapY() });

	if (m_entity->GetIsAGoodGuy())
		SetNextState<RedemptionRight>(m_animation);
}

BusinessMoveRight::BusinessMoveRight(BusinessMan* owner, LoopAnimation* anim) : BaseBusinessMove(owner, anim,1)
{
}

void BusinessMoveRight::OnEnter()
{
	BaseBusinessMove::OnEnter();
	m_animation->SetMinMax(1,8);
	m_animation->SetAnimationTime(KT::Chrono<float>::Time::CreateFromValue<KT::ratio<1>>(0.2f));
}

void BusinessMoveRight::Update(const float& dt)
{
	BaseBusinessMove::Update(dt);
	auto player = m_entity->GetMyScene()->GetPlayer();
	if (!player)
		return;
	if (player->GetRectangle()->getPosition().x < m_entity->GetRectangle()->getPosition().x)
	{
		SetNextState<BusinessMoveLeft>(m_animation);
	}

	if ((player->GetRectangle()->getPosition() - m_entity->GetRectangle()->getPosition()).length() < 800 && m_coolDown.GetElapsedTime().AsSeconds() > 1.0f)
	{
		// on peux tirer
		auto randNum = m_random.getRandomNumber(1, 6);
		if (randNum == 2 || randNum == 4)
		{
			SetNextState<BusinessAtackRight>(m_animation);
		}
		m_coolDown.Reset();
	}
	auto potentialX = m_entity->GetRectangle()->getPosition().x + m_entity->GetSpeed() * dt;
	auto playerX = player->GetRectangle()->getPosition().x;
	float x = std::min(potentialX, playerX);
	m_entity->GetRectangle()->setPosition({ x,m_entity->GetCapY() });
	if (m_entity->GetIsAGoodGuy())
		SetNextState<RedemptionLeft>(m_animation);
}

BusinessBaseAttack::BusinessBaseAttack(BusinessMan* owner, LoopAnimation* anim) : BusinessManState(owner, anim), m_endAtack(false)
{
}

void BusinessBaseAttack::Update(const float& dt)
{
	BusinessManState::Update(dt);
	m_animation->UpdateShapeFrame(m_entity->GetRectangle());
	if (m_attackTimer.GetElapsedTime().AsSeconds() > 0.3f)
	{
		m_entity->Attack();
		m_endAtack = true;
	}
}

BusinessAtackLeft::BusinessAtackLeft(BusinessMan* owner, LoopAnimation* anim) : BusinessBaseAttack(owner, anim)
{
}


void BusinessAtackLeft::OnEnter()
{
	BusinessBaseAttack::OnEnter();
	m_animation->SetMinMax(17, 20);
	m_animation->SetAnimationTime(KT::Chrono<float>::Time::CreateFromValue<KT::ratio<1>>(0.1f));
}

void BusinessAtackLeft::Update(const float& dt)
{
	BusinessBaseAttack::Update(dt);
	if (m_endAtack)
		SetNextState<BusinessIdleLeft>(m_animation);
}

BusinessAtackRight::BusinessAtackRight(BusinessMan* owner, LoopAnimation* anim) : BusinessBaseAttack(owner, anim)
{
}


void BusinessAtackRight::OnEnter()
{
	BusinessBaseAttack::OnEnter();
	m_animation->SetMinMax(25, 28);
	m_animation->SetAnimationTime(KT::Chrono<float>::Time::CreateFromValue<KT::ratio<1>>(0.1f));
}

void BusinessAtackRight::Update(const float& dt)
{
	BusinessBaseAttack::Update(dt);
	if (m_endAtack)
		SetNextState<BusinessIdleRight>(m_animation);
}




BaseRedemptionState::BaseRedemptionState(BusinessMan* owner, LoopAnimation* anim, float dirFactor) : BusinessManState(owner, anim), m_difFactor(dirFactor)
{
}

void BaseRedemptionState::Update(const float& dt)
{
	BusinessManState::Update(dt);
	m_entity->GetRectangle()->move({ m_difFactor * m_entity->GetSpeed() * dt, 0 });
	m_animation->UpdateShapeFrame(m_entity->GetRectangle());
}

RedemptionLeft::RedemptionLeft(BusinessMan* owner, LoopAnimation* anim) : BaseRedemptionState(owner, anim, -1)
{
}

void RedemptionLeft::OnEnter()
{
	BaseRedemptionState::OnEnter();
	m_animation->SetMinMax(41, 47);
	m_animation->SetAnimationTime(KT::Chrono<float>::Time::CreateFromValue<KT::ratio<1>>(0.1f));
}

RedemptionRight::RedemptionRight(BusinessMan* owner, LoopAnimation* anim) : BaseRedemptionState(owner,anim,1)
{
}

void RedemptionRight::OnEnter()
{
	BaseRedemptionState::OnEnter();
	m_animation->SetMinMax(33, 40);
	m_animation->SetAnimationTime(KT::Chrono<float>::Time::CreateFromValue<KT::ratio<1>>(0.1f));
}


