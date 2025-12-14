#include "MyPlayer.h"
#include "BulletPlayer.h"
#include "GameScene.h"
#include "SoundEffect.h"
#include "Core/Input.h"

MyPlayer::MyPlayer(BaseComposite* parent, float capY) : CollidableRectangleComposite(parent), m_capY(capY), m_playerStateMachine(nullptr), m_manager(nullptr), m_animation(nullptr),m_isInvlunerable(false),m_shield(false)
{}

void MyPlayer::OnDestroy()
{
	delete m_playerStateMachine;
	delete m_manager;
	delete m_animation;
}

void MyPlayer::OnInit()
{
	GetRectangle()->setSize({ 47 * 3,70 * 3});
	GetRectangle()->setPosition({889.5f,m_capY});
	m_manager = new AnimationManager{ "graineman_sprite_sheet_70x47.png", KT::Vector2UI(376, 560), KT::Vector2UI(0, 0), KT::Vector2UI(8, 8) };
	m_animation = new LoopAnimation{ m_manager,33,35,KT::Chrono<float>::Time::CreateFromValue<KT::ratio<1>>(0.3f) };
	m_animation->SetTexture(GetRectangle());
	m_playerStateMachine = new KT::StateMachine<MyPlayer>(std::make_unique<RightIdle>(this, m_animation), 1);
}

float MyPlayer::GetCapY() const
{
	return m_capY;
}

float MyPlayer::GetSpeed() const
{
	return 300.f;
}

float MyPlayer::GetJumpHeight() const
{
	return m_capY - 200.0f;
}

void MyPlayer::Update(float deltatime)
{
	m_playerStateMachine->ChangeState();
	m_playerStateMachine->Update(deltatime);
	if (m_isInvlunerable)
	{
		if ( m_invulnerabilityTimer.GetElapsedTime().AsSeconds() > 1.5f)
		{
			GetRectangle()->setFillColor(sf::Color{ 255,255,255,255 });
			m_isInvlunerable = false;
			redtimer.Reset();
			redtimer.Pause();
		}
	
		if (isRed && redtimer.GetElapsedTime().AsSeconds() > 0.25f)
		{
			GetRectangle()->setFillColor(sf::Color{ 255,255,255,255 });
			redtimer.Reset();
			isRed = !isRed;
		}
		if (!isRed && redtimer.GetElapsedTime().AsSeconds() > 0.25f)
		{
			GetRectangle()->setFillColor(sf::Color::Red);
			redtimer.Reset();
			isRed = !isRed;
			
		}
	
	}
}



void MyPlayer::Render(float alpha)
{
	m_playerStateMachine->Render(alpha);
}

void MyPlayer::Input(const std::optional<sf::Event>& event)
{
	
	m_playerStateMachine->ProcessInput();
}

void MyPlayer::Attack(bool isShootingRight)
{
	auto bullet = new BulletPlayer(this, {GetRectangle()->getPosition().x,GetRectangle()->getPosition().y + 105}, isShootingRight);
	bullet->OnInit();
	auto sound = new Sound(this, SoundBufferLoader::Load("Sound_lance_graine.wav"));
	sound->OnInit();
	m_attackCooldown.Reset();

}

void MyPlayer::HitPlayer()
{
	if (m_shield)
		return;
	if (!m_isInvlunerable)
	{
		// hit
		auto sound = new Sound(this, SoundBufferLoader::Load("Sound_explosion_graine.wav"));
		sound->OnInit();
		static_cast<GameScene*>(GetScene())->RemoveScore();
		// TODO game rules for hit
		isRed = true;
		GetRectangle()->setFillColor(sf::Color::Red);
		m_isInvlunerable = true;
		m_invulnerabilityTimer.Reset();
		redtimer.Resume();
		redtimer.Reset();
	}
}

void MyPlayer::EnableShield()
{
	m_shield = true;
}

void MyPlayer::DisableShield()
{
	m_shield = false;
}


PlayerState::PlayerState(MyPlayer* owner, LoopAnimation* anim): KT::IState<MyPlayer>(owner),m_animation(anim)
{}

IdleBaseState::IdleBaseState(MyPlayer* owner, LoopAnimation* anim): PlayerState(owner,anim)
{}

void IdleBaseState::Update(const float& dt)
{
	PlayerState::Update(dt);
	m_animation->UpdateShapeFrame(m_entity->GetRectangle());
}

void IdleBaseState::ProcessInput()
{
	PlayerState::ProcessInput();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		SetNextState<MovingRight>(m_animation);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
	{
		SetNextState<MovingLeft>(m_animation);

	}
		
}

LeftIdle::LeftIdle(MyPlayer* owner, LoopAnimation* anim): IdleBaseState(owner,anim)
{}

void LeftIdle::ProcessInput()
{
	IdleBaseState::ProcessInput();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{
		SetNextState<JumpIdleLeftState>(m_animation);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
	{
		SetNextState<AttackLeftState>(m_animation);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		SetNextState<ShieldLeft>(m_animation);
	}
}

void LeftIdle::OnEnter()
{
	m_animation->SetMinMax(41, 43);
	m_animation->SetAnimationTime(KT::Chrono<float>::Time::CreateFromValue<KT::ratio<1>>(0.1f));
}

RightIdle::RightIdle(MyPlayer* owner, LoopAnimation* anim): IdleBaseState(owner, anim)
{}

void RightIdle::ProcessInput()
{
	IdleBaseState::ProcessInput();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{
		SetNextState<JumpIdleRightState>(m_animation);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
	{
		SetNextState<AttackRightState>(m_animation);

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		SetNextState<ShieldRight>(m_animation);
	}
}

void RightIdle::OnEnter()
{
	m_animation->SetMinMax(33, 35);
	m_animation->SetAnimationTime(KT::Chrono<float>::Time::CreateFromValue<KT::ratio<1>>(0.1f));
}

MovingBase::MovingBase(MyPlayer* owner, LoopAnimation* anim, float dirFactor): PlayerState(owner,anim),m_dirFactor(dirFactor)
{
		
}

void MovingBase::Update(const float& dt)
{
	PlayerState::Update(dt);
	m_entity->GetRectangle()->move({ m_dirFactor * m_entity->GetSpeed() * dt, 0 });
	m_animation->UpdateShapeFrame(m_entity->GetRectangle());
}

MovingLeft::MovingLeft(MyPlayer* owner, LoopAnimation* anim): MovingBase(owner, anim,-1)
{
		
}

void MovingLeft::OnEnter()
{
	m_animation->SetMinMax(57, 64);
	m_animation->SetAnimationTime(KT::Chrono<float>::Time::CreateFromValue<KT::ratio<1>>(0.1f));
}

void MovingLeft::ProcessInput()
{
	MovingBase::ProcessInput();
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
	{
		SetNextState<LeftIdle>(m_animation);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		SetNextState<MovingRight>(m_animation);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{
		SetNextState<JumpLeft>(m_animation);
	}
}

MovingRight::MovingRight(MyPlayer* owner, LoopAnimation* anim): MovingBase(owner, anim, 1)
{

}

void MovingRight::OnEnter()
{
	m_animation->SetMinMax(49, 56);
	m_animation->SetAnimationTime(KT::Chrono<float>::Time::CreateFromValue<KT::ratio<1>>(0.1f));
}

void MovingRight::ProcessInput()
{
	MovingBase::ProcessInput();
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		SetNextState<RightIdle>(m_animation);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
	{
		SetNextState<MovingLeft>(m_animation);

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{
		SetNextState<JumpRight>(m_animation);

	}
}

JumpIdleBase::JumpIdleBase(MyPlayer* owner, LoopAnimation* anim): PlayerState(owner, anim)
{

}

void JumpIdleBase::Update(const float& dt)
{
	PlayerState::Update(dt);
	float y = std::max(m_entity->GetRectangle()->getPosition().y - m_entity->GetSpeed() * dt, m_entity->GetJumpHeight());
	m_entity->GetRectangle()->setPosition({ m_entity->GetRectangle()->getPosition().x, y });
	m_animation->UpdateShapeFrame(m_entity->GetRectangle());
}

void JumpIdleBase::ProcessInput()
{
	PlayerState::ProcessInput();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		SetNextState<JumpRight>(m_animation);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
	{
		SetNextState<JumpLeft>(m_animation);

	}
}

JumpIdleLeftState::JumpIdleLeftState(MyPlayer* owner, LoopAnimation* anim): JumpIdleBase(owner,anim)
{}

void JumpIdleLeftState::ProcessInput()
{
	JumpIdleBase::ProcessInput();
	if (m_entity->GetRectangle()->getPosition().y == m_entity->GetJumpHeight())
	{
		SetNextState<DownIdleLeftState>(m_animation);
	}
}

void JumpIdleLeftState::OnEnter()
{
	m_animation->SetMinMax(26, 29);
	m_animation->SetAnimationTime(KT::Chrono<float>::Time::CreateFromValue<KT::ratio<1>>(0.17f));
}

JumpIdleRightState::JumpIdleRightState(MyPlayer* owner, LoopAnimation* anim): JumpIdleBase(owner, anim)
{}

void JumpIdleRightState::ProcessInput()
{
	JumpIdleBase::ProcessInput();
	if (m_entity->GetRectangle()->getPosition().y == m_entity->GetJumpHeight())
	{
		SetNextState<DownIdleRightState>(m_animation);
	}
}

void JumpIdleRightState::OnEnter()
{
	m_animation->SetMinMax(18, 21);
	m_animation->SetAnimationTime(KT::Chrono<float>::Time::CreateFromValue<KT::ratio<1>>(0.17f));
}

BaseJumpMoving::BaseJumpMoving(MyPlayer* owner, LoopAnimation* anim, float dirFactor): PlayerState(owner, anim), m_dirFactor(dirFactor)
{

}

void BaseJumpMoving::Update(const float& dt)
{
	PlayerState::Update(dt);
	float y = std::max(m_entity->GetRectangle()->getPosition().y - m_entity->GetSpeed() * dt, m_entity->GetJumpHeight());
	m_entity->GetRectangle()->setPosition({ m_entity->GetRectangle()->getPosition().x, y });
	m_entity->GetRectangle()->move({ m_dirFactor * m_entity->GetSpeed() * dt, 0 });
	m_animation->UpdateShapeFrame(m_entity->GetRectangle());
}

JumpLeft::JumpLeft(MyPlayer* owner, LoopAnimation* anim): BaseJumpMoving(owner,anim,-1)
{}

void JumpLeft::ProcessInput()
{
	BaseJumpMoving::ProcessInput();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		SetNextState<JumpRight>(m_animation);
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
	{
		SetNextState<JumpIdleLeftState>(m_animation);
	}
	if (m_entity->GetRectangle()->getPosition().y == m_entity->GetJumpHeight())
	{
		SetNextState<DownLeft>(m_animation);
	}
}

void JumpLeft::OnEnter()
{
	m_animation->SetMinMax(26, 29);		
	m_animation->SetAnimationTime(KT::Chrono<float>::Time::CreateFromValue<KT::ratio<1>>(0.17f));
}

JumpRight::JumpRight(MyPlayer* owner, LoopAnimation* anim): BaseJumpMoving(owner, anim, 1)
{}

void JumpRight::ProcessInput()
{
	BaseJumpMoving::ProcessInput();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
	{
		SetNextState<JumpLeft>(m_animation);
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		SetNextState<JumpIdleRightState>(m_animation);
	}
	if (m_entity->GetRectangle()->getPosition().y == m_entity->GetJumpHeight())
	{
		SetNextState<DownRight>(m_animation);
	}
}

void JumpRight::OnEnter()
{
	m_animation->SetMinMax(18, 21);
	m_animation->SetAnimationTime(KT::Chrono<float>::Time::CreateFromValue<KT::ratio<1>>(0.17f));
}

DownIdleBase::DownIdleBase(MyPlayer* owner, LoopAnimation* anim): PlayerState(owner, anim)
{

}

void DownIdleBase::Update(const float& dt)
{
	PlayerState::Update(dt);
	float y = std::min(m_entity->GetRectangle()->getPosition().y + m_entity->GetSpeed() * dt, m_entity->GetCapY());
	m_entity->GetRectangle()->setPosition({ m_entity->GetRectangle()->getPosition().x, y });
	m_animation->UpdateShapeFrame(m_entity->GetRectangle());
}

void DownIdleBase::ProcessInput()
{
	PlayerState::ProcessInput();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		SetNextState<DownRight>(m_animation);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
	{
		SetNextState<DownLeft>(m_animation);
	}
}

DownIdleLeftState::DownIdleLeftState(MyPlayer* owner, LoopAnimation* anim): DownIdleBase(owner, anim)
{}

void DownIdleLeftState::ProcessInput()
{
	DownIdleBase::ProcessInput();
	if (m_entity->GetRectangle()->getPosition().y == m_entity->GetCapY())
	{
		SetNextState<LeftIdle>(m_animation);
	}
}

void DownIdleLeftState::OnEnter()
{
	//m_animation->SetMinMax(28, 29);
	m_animation->SetAnimationTime(KT::Chrono<float>::Time::CreateFromValue<KT::ratio<1>>(0.4f));

}

DownIdleRightState::DownIdleRightState(MyPlayer* owner, LoopAnimation* anim): DownIdleBase(owner, anim)
{}

void DownIdleRightState::ProcessInput()
{
	DownIdleBase::ProcessInput();
	if (m_entity->GetRectangle()->getPosition().y == m_entity->GetCapY())
	{
		SetNextState<RightIdle>(m_animation);
	}
}

void DownIdleRightState::OnEnter()
{
	//m_animation->SetMinMax(20, 21);
	m_animation->SetAnimationTime(KT::Chrono<float>::Time::CreateFromValue<KT::ratio<1>>(0.4f));
}

BaseDownMoving::BaseDownMoving(MyPlayer* owner, LoopAnimation* anim, float dirFactor): PlayerState(owner, anim), m_dirFactor(dirFactor)
{

}

void BaseDownMoving::Update(const float& dt)
{
	PlayerState::Update(dt);
	float y = std::min(m_entity->GetRectangle()->getPosition().y + m_entity->GetSpeed() * dt, m_entity->GetCapY());
	m_entity->GetRectangle()->setPosition({ m_entity->GetRectangle()->getPosition().x, y });
	m_entity->GetRectangle()->move({ m_dirFactor * m_entity->GetSpeed() * dt, 0 });
	m_animation->UpdateShapeFrame(m_entity->GetRectangle());
}

DownLeft::DownLeft(MyPlayer* owner, LoopAnimation* anim): BaseDownMoving(owner, anim, -1)
{}

void DownLeft::ProcessInput()
{
	BaseDownMoving::ProcessInput();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		SetNextState<DownRight>(m_animation);
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
	{
		SetNextState<DownIdleLeftState>(m_animation);
	}
	if (m_entity->GetRectangle()->getPosition().y == m_entity->GetCapY())
	{
		SetNextState<MovingLeft>(m_animation);
	}
}

void DownLeft::OnEnter()
{
	//m_animation->SetMinMax(28, 29);
	m_animation->SetAnimationTime(KT::Chrono<float>::Time::CreateFromValue<KT::ratio<1>>(0.4f));
}

DownRight::DownRight(MyPlayer* owner, LoopAnimation* anim): BaseDownMoving(owner, anim, 1)
{}

void DownRight::ProcessInput()
{
	BaseDownMoving::ProcessInput();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
	{
		SetNextState<DownLeft>(m_animation);
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		SetNextState<DownIdleRightState>(m_animation);
	}
	if (m_entity->GetRectangle()->getPosition().y == m_entity->GetCapY())
	{
		SetNextState<MovingRight>(m_animation);
	}
}

void DownRight::OnEnter()
{
	//m_animation->SetMinMax(20, 21);
	m_animation->SetAnimationTime(KT::Chrono<float>::Time::CreateFromValue<KT::ratio<1>>(0.4f));
}

AttackState::AttackState(MyPlayer* owner, LoopAnimation* anim, bool isRight) : PlayerState(owner, anim), m_isRight(isRight),endAtack(false)
{
}

void AttackState::Update(const float& dt)
{
	PlayerState::Update(dt);
	m_animation->UpdateShapeFrame(m_entity->GetRectangle());

	if (m_attackTimer.GetElapsedTime().AsSeconds() > 0.15f)
	{
		m_entity->Attack(m_isRight);
		endAtack = true;
	}

}

AttackRightState::AttackRightState(MyPlayer* owner, LoopAnimation* anim) : AttackState(owner, anim, true)
{
}

void AttackRightState::OnEnter()
{
	m_animation->SetMinMax(1, 2);
	m_animation->SetAnimationTime(KT::Chrono<float>::Time::CreateFromValue<KT::ratio<1>>(0.6f));
		
}

void AttackRightState::ProcessInput()
{
	if (endAtack)
	{
		SetNextState<RightIdle>(m_animation);
	}
}

AttackLeftState::AttackLeftState(MyPlayer* owner, LoopAnimation* anim) : AttackState(owner, anim, false)
{
}

void AttackLeftState::OnEnter()
{
	m_animation->SetMinMax(9, 10);
	m_animation->SetAnimationTime(KT::Chrono<float>::Time::CreateFromValue<KT::ratio<1>>(0.6f));
}

void AttackLeftState::ProcessInput()
{
	AttackState::ProcessInput();
	if (endAtack)
	{
		SetNextState<LeftIdle>(m_animation);
	}
}

ShieldLeft::ShieldLeft(MyPlayer* owner, LoopAnimation* anim) : PlayerState(owner, anim)
{
}

void ShieldLeft::OnEnter()
{
	PlayerState::OnEnter();
	m_entity->EnableShield();
}

void ShieldLeft::OnExit()
{
	PlayerState::OnExit();
	m_entity->DisableShield();
}

void ShieldLeft::ProcessInput()
{
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		SetNextState<LeftIdle>(m_animation);
	}
}

ShieldRight::ShieldRight(MyPlayer* owner, LoopAnimation* anim) : PlayerState(owner, anim)
{
}

void ShieldRight::OnEnter()
{
	PlayerState::OnEnter();
	m_entity->EnableShield();
}

void ShieldRight::OnExit()
{
	PlayerState::OnExit();
	m_entity->DisableShield();
}

void ShieldRight::ProcessInput()
{
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		SetNextState<RightIdle>(m_animation);
	}
}


//IdlePlayerState::IdlePlayerState(MyPlayer* owner, LoopAnimation* anim): PlayerState(owner, anim)
//{}
//
//void IdlePlayerState::ProcessInput()
//{
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
//	{
//		SetNextState<LeftPlayerState>(m_animation);
//	}
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
//	{
//		SetNextState<RightPlayerState>(m_animation);
//	}
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
//	{
//		SetNextState<JumpPlayerState>(m_animation);
//	}
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
//		m_entity->Attack();
//}
//
//void IdlePlayerState::Update(const float& dt)
//{
//	
//	m_animation->UpdateShapeFrame(m_entity->GetRectangle());
//}
//
//void IdlePlayerState::OnEnter()
//{
//	m_animation->SetMinMax(89, 94);
//}
//
//void LeftPlayerState::ProcessInput() {
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
//	{
//		SetNextState<RightPlayerState>(m_animation);
//	}
//	 if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
//	{
//		SetNextState<IdlePlayerState>(m_animation);
//	}
//	 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
//	 {
//		 SetNextState<JumpLeftPlayerState>(m_animation);
//	 }
//}
//
//void LeftPlayerState::Update(const float& dt)
//{
//	m_entity->GetRectangle()->move({ -m_entity->GetSpeed() *dt, 0 });
//	m_animation->UpdateShapeFrame(m_entity->GetRectangle());
//}
//
//void LeftPlayerState:: OnEnter() 
//{
//	m_animation->SetMinMax(23, 31);
//	m_entity->SetDirShoot(false);
//}
//
//void RightPlayerState::ProcessInput() 
//{
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
//	{
//		SetNextState<LeftPlayerState>(m_animation);
//	}
//	 if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
//	{
//		SetNextState<IdlePlayerState>(m_animation);
//	}
//	 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
//	 {
//		 SetNextState<JumpRightPlayerState>(m_animation);
//	 }
//}
//
//void RightPlayerState::Update(const float& dt) 
//{
//	m_entity->GetRectangle()->move({ m_entity->GetSpeed() * dt, 0 });
//	m_animation->UpdateShapeFrame(m_entity->GetRectangle());
//}
//
//void RightPlayerState::OnEnter() 
//{
//	m_entity->SetDirShoot(true);
//	m_animation->SetMinMax(12, 19);
//}
//
//JumpPlayerState::JumpPlayerState(MyPlayer* owner, LoopAnimation* anim) : PlayerState(owner, anim)
//{
//}
//
//void JumpPlayerState::ProcessInput()
//{
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
//	{
//		SetNextState<JumpLeftPlayerState>(m_animation);
//	}
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
//	{
//		SetNextState<JumpRightPlayerState>(m_animation);
//	}
//	
//
//}
//
//void JumpPlayerState::Update(const float& dt)
//{
//	float y = std::max(m_entity->GetRectangle()->getPosition().y - m_entity->GetSpeed() * dt, m_entity->GetJumpHeight());
//	m_entity->GetRectangle()->setPosition({ m_entity->GetRectangle()->getPosition().x, y });
//
//	
//
//	m_animation->UpdateShapeFrame(m_entity->GetRectangle());
//	if (y == m_entity->GetJumpHeight())
//	{
//		SetNextState<DawnPlayerState>(m_animation);
//	}
//}
//
//void JumpPlayerState::OnEnter()
//{
//	m_animation->SetMinMax(1, 10);
//}
//
//void JumpLeftPlayerState::ProcessInput() {
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
//	{
//		SetNextState<JumpRightPlayerState>(m_animation);
//	}
//     if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
//	{
//		SetNextState<JumpPlayerState>(m_animation);
//	}
//	 if (m_entity->GetRectangle()->getPosition().y == m_entity->GetJumpHeight())
//	 {
//		 SetNextState<DawnLeftPlayerState>(m_animation);
//	 }
//}
//
//void JumpLeftPlayerState::Update(const float& dt)
//{
//	float y = std::max(m_entity->GetRectangle()->getPosition().y - m_entity->GetSpeed() * dt, m_entity->GetJumpHeight());
//	m_entity->GetRectangle()->setPosition({ m_entity->GetRectangle()->getPosition().x, y });
//
//
//
//	m_entity->GetRectangle()->move({ -m_entity->GetSpeed() * dt, 0 });
//	m_animation->UpdateShapeFrame(m_entity->GetRectangle());
//	
//}
//
//void JumpLeftPlayerState::OnEnter()
//{
//	m_entity->SetDirShoot(false);
//	m_animation->SetMinMax(23, 31);
//}
//
//void JumpRightPlayerState::ProcessInput()
//{
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
//	{
//		SetNextState<JumpLeftPlayerState>(m_animation);
//	}
//	 if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
//	{
//		SetNextState<JumpPlayerState>(m_animation);
//	}
//
//	 if (m_entity->GetRectangle()->getPosition().y == m_entity->GetJumpHeight())
//	 {
//		 SetNextState<DawnRightPlayerState>(m_animation);
//	 }
//
//}
//
//void JumpRightPlayerState::Update(const float& dt)
//{
//	
//	float y =  std::max(m_entity->GetRectangle()->getPosition().y - m_entity->GetSpeed() * dt, m_entity->GetJumpHeight());
//	m_entity->GetRectangle()->setPosition({ m_entity->GetRectangle()->getPosition().x, y });
//
//
//	m_entity->GetRectangle()->move({ m_entity->GetSpeed() * dt, 0 });
//	m_animation->UpdateShapeFrame(m_entity->GetRectangle());
//
//}
//
//void JumpRightPlayerState::OnEnter()
//{
//	m_entity->SetDirShoot(true);
//	m_animation->SetMinMax(12, 19);
//}
//
//
//// here 
//DawnPlayerState::DawnPlayerState(MyPlayer* owner, LoopAnimation* anim) : PlayerState(owner, anim)
//{
//}
//
//void DawnPlayerState::ProcessInput()
//{
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
//	{
//		SetNextState<DawnLeftPlayerState>(m_animation);
//	}
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
//	{
//		SetNextState<DawnRightPlayerState>(m_animation);
//	}
//	if (m_entity->GetRectangle()->getPosition().y == m_entity->GetCapY())
//	{
//		SetNextState<IdlePlayerState>(m_animation);
//	}
//
//}
//
//void DawnPlayerState::Update(const float& dt)
//{
//	float y = std::min(m_entity->GetRectangle()->getPosition().y + m_entity->GetSpeed() * dt, m_entity->GetCapY());
//	m_entity->GetRectangle()->setPosition({ m_entity->GetRectangle()->getPosition().x, y });
//
//	m_animation->UpdateShapeFrame(m_entity->GetRectangle());
//}
//
//void DawnPlayerState::OnEnter()
//{
//	m_animation->SetMinMax(1, 10);
//}
//
//void DawnLeftPlayerState::ProcessInput() {
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
//	{
//		SetNextState<DawnRightPlayerState>(m_animation);
//	}
//	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
//	{
//		SetNextState<DawnPlayerState>(m_animation);
//	}
//	if (m_entity->GetRectangle()->getPosition().y == m_entity->GetCapY())
//	{
//		SetNextState<LeftPlayerState>(m_animation);
//	}
//}
//
//void DawnLeftPlayerState::Update(const float& dt)
//{
//	float y = std::min(m_entity->GetRectangle()->getPosition().y + m_entity->GetSpeed() * dt, m_entity->GetCapY());
//	m_entity->GetRectangle()->setPosition({ m_entity->GetRectangle()->getPosition().x, y });
//
//
//	m_entity->GetRectangle()->move({ -m_entity->GetSpeed() * dt, 0 });
//	m_animation->UpdateShapeFrame(m_entity->GetRectangle());
//}
//
//void DawnLeftPlayerState::OnEnter()
//{
//	m_entity->SetDirShoot(false);
//	m_animation->SetMinMax(23, 31);
//}
//
//void DawnRightPlayerState::ProcessInput()
//{
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
//	{
//		SetNextState<DawnLeftPlayerState>(m_animation);
//	}
//	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
//	{
//		SetNextState<DawnPlayerState>(m_animation);
//	}
//	if (m_entity->GetRectangle()->getPosition().y == m_entity->GetCapY())
//	{
//		SetNextState<RightPlayerState>(m_animation);
//	}
//}
//
//void DawnRightPlayerState::Update(const float& dt)
//{
//
//	float y = std::min(m_entity->GetRectangle()->getPosition().y + m_entity->GetSpeed() * dt, m_entity->GetCapY());
//	m_entity->GetRectangle()->setPosition({ m_entity->GetRectangle()->getPosition().x, y });
//
//	m_entity->GetRectangle()->move({ m_entity->GetSpeed() * dt, 0 });
//	m_animation->UpdateShapeFrame(m_entity->GetRectangle());
//	
//}
//
//void DawnRightPlayerState::OnEnter()
//{
//	m_entity->SetDirShoot(true);
//	m_animation->SetMinMax(12, 19);
//}