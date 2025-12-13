#include "MyPlayer.h"
#include "BulletPlayer.h"
MyPlayer::MyPlayer(BaseComposite* parent, float capY) : CollidableRectangleComposite(parent), m_capY(capY), m_playerStateMachine(nullptr), m_manager(nullptr), m_animation(nullptr)
{}

void MyPlayer::OnDestroy()
{
	delete m_playerStateMachine;
	delete m_manager;
	delete m_animation;
}

void MyPlayer::OnInit()
{
	GetRectangle()->setSize({ 100,100 });
	GetRectangle()->setPosition({0,m_capY});
	m_manager = new AnimationManager{ "SpriteSheet_Nova.png", KT::Vector2UI(528, 624), KT::Vector2UI(0, 0), KT::Vector2UI(11, 13) };
	m_animation = new LoopAnimation{ m_manager,1,10,KT::Chrono<float>::Time::CreateFromValue<KT::ratio<1>>(0.1f) };
	m_animation->SetTexture(GetRectangle());
	m_playerStateMachine = new KT::StateMachine<MyPlayer>(std::make_unique<IdlePlayerState>(this, m_animation), 1);
}

float MyPlayer::GetCapY() const
{
	return m_capY;
}

float MyPlayer::GetSpeed() const
{
	return 300.0f;
}

float MyPlayer::GetJumpHeight() const
{
	return m_capY - 50.0f;
}

void MyPlayer::Update(float deltatime)
{
	m_playerStateMachine->ChangeState();
	m_playerStateMachine->Update(deltatime);
}

void MyPlayer::SetDirShoot(bool shootRight)
{
	isShootingRight = shootRight;
}

void MyPlayer::Render(float alpha)
{
	m_playerStateMachine->Render(alpha);
}

void MyPlayer::Input(const std::optional<sf::Event>& event)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
		Attack();
	m_playerStateMachine->ProcessInput();
}

void MyPlayer::Attack()
{
	if(m_attackCooldown.GetElapsedTime().AsSeconds() < 0.2f)
		return;
	auto bullet = new BulletPlayer(this, {GetRectangle()->getPosition().x,GetRectangle()->getPosition().y}, isShootingRight);
	bullet->OnInit();
	m_attackCooldown.Reset();
}

PlayerState::PlayerState(MyPlayer* owner, LoopAnimation* anim): KT::IState<MyPlayer>(owner),m_animation(anim)
{}

IdlePlayerState::IdlePlayerState(MyPlayer* owner, LoopAnimation* anim): PlayerState(owner, anim)
{}

void IdlePlayerState::ProcessInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
	{
		SetNextState<LeftPlayerState>(m_animation);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		SetNextState<RightPlayerState>(m_animation);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{
		SetNextState<JumpPlayerState>(m_animation);
	}

}

void IdlePlayerState::Update(const float& dt)
{
	
	m_animation->UpdateShapeFrame(m_entity->GetRectangle());
}

void IdlePlayerState::OnEnter()
{
	m_animation->SetMinMax(89, 94);
}

void LeftPlayerState::ProcessInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		SetNextState<RightPlayerState>(m_animation);
	}
	 if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
	{
		SetNextState<IdlePlayerState>(m_animation);
	}
	 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	 {
		 SetNextState<JumpLeftPlayerState>(m_animation);
	 }
}

void LeftPlayerState::Update(const float& dt)
{
	m_entity->GetRectangle()->move({ -m_entity->GetSpeed() *dt, 0 });
	m_animation->UpdateShapeFrame(m_entity->GetRectangle());
}

void LeftPlayerState:: OnEnter() 
{
	m_animation->SetMinMax(23, 31);
	m_entity->SetDirShoot(false);
}

void RightPlayerState::ProcessInput() 
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
	{
		SetNextState<LeftPlayerState>(m_animation);
	}
	 if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		SetNextState<IdlePlayerState>(m_animation);
	}
	 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	 {
		 SetNextState<JumpRightPlayerState>(m_animation);
	 }
}

void RightPlayerState::Update(const float& dt) 
{
	m_entity->GetRectangle()->move({ m_entity->GetSpeed() * dt, 0 });
	m_animation->UpdateShapeFrame(m_entity->GetRectangle());
}

void RightPlayerState::OnEnter() 
{
	m_entity->SetDirShoot(true);
	m_animation->SetMinMax(12, 19);
}

JumpPlayerState::JumpPlayerState(MyPlayer* owner, LoopAnimation* anim) : PlayerState(owner, anim)
{
}

void JumpPlayerState::ProcessInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
	{
		SetNextState<JumpLeftPlayerState>(m_animation);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		SetNextState<JumpRightPlayerState>(m_animation);
	}
	

}

void JumpPlayerState::Update(const float& dt)
{
	float y = std::max(m_entity->GetRectangle()->getPosition().y - m_entity->GetSpeed() * dt, m_entity->GetJumpHeight());
	m_entity->GetRectangle()->setPosition({ m_entity->GetRectangle()->getPosition().x, y });

	

	m_animation->UpdateShapeFrame(m_entity->GetRectangle());
	if (y == m_entity->GetJumpHeight())
	{
		SetNextState<DawnPlayerState>(m_animation);
	}
}

void JumpPlayerState::OnEnter()
{
	m_animation->SetMinMax(1, 10);
}

void JumpLeftPlayerState::ProcessInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		SetNextState<JumpRightPlayerState>(m_animation);
	}
     if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
	{
		SetNextState<JumpPlayerState>(m_animation);
	}
	 if (m_entity->GetRectangle()->getPosition().y == m_entity->GetJumpHeight())
	 {
		 SetNextState<DawnLeftPlayerState>(m_animation);
	 }
}

void JumpLeftPlayerState::Update(const float& dt)
{
	float y = std::max(m_entity->GetRectangle()->getPosition().y - m_entity->GetSpeed() * dt, m_entity->GetJumpHeight());
	m_entity->GetRectangle()->setPosition({ m_entity->GetRectangle()->getPosition().x, y });



	m_entity->GetRectangle()->move({ -m_entity->GetSpeed() * dt, 0 });
	m_animation->UpdateShapeFrame(m_entity->GetRectangle());
	
}

void JumpLeftPlayerState::OnEnter()
{
	m_entity->SetDirShoot(false);
	m_animation->SetMinMax(23, 31);
}

void JumpRightPlayerState::ProcessInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
	{
		SetNextState<JumpLeftPlayerState>(m_animation);
	}
	 if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		SetNextState<JumpPlayerState>(m_animation);
	}

	 if (m_entity->GetRectangle()->getPosition().y == m_entity->GetJumpHeight())
	 {
		 SetNextState<DawnRightPlayerState>(m_animation);
	 }

}

void JumpRightPlayerState::Update(const float& dt)
{
	
	float y =  std::max(m_entity->GetRectangle()->getPosition().y - m_entity->GetSpeed() * dt, m_entity->GetJumpHeight());
	m_entity->GetRectangle()->setPosition({ m_entity->GetRectangle()->getPosition().x, y });


	m_entity->GetRectangle()->move({ m_entity->GetSpeed() * dt, 0 });
	m_animation->UpdateShapeFrame(m_entity->GetRectangle());

}

void JumpRightPlayerState::OnEnter()
{
	m_entity->SetDirShoot(true);
	m_animation->SetMinMax(12, 19);
}


// here 
DawnPlayerState::DawnPlayerState(MyPlayer* owner, LoopAnimation* anim) : PlayerState(owner, anim)
{
}

void DawnPlayerState::ProcessInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
	{
		SetNextState<DawnLeftPlayerState>(m_animation);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		SetNextState<DawnRightPlayerState>(m_animation);
	}
	if (m_entity->GetRectangle()->getPosition().y == m_entity->GetCapY())
	{
		SetNextState<IdlePlayerState>(m_animation);
	}

}

void DawnPlayerState::Update(const float& dt)
{
	float y = std::min(m_entity->GetRectangle()->getPosition().y + m_entity->GetSpeed() * dt, m_entity->GetCapY());
	m_entity->GetRectangle()->setPosition({ m_entity->GetRectangle()->getPosition().x, y });

	m_animation->UpdateShapeFrame(m_entity->GetRectangle());
}

void DawnPlayerState::OnEnter()
{
	m_animation->SetMinMax(1, 10);
}

void DawnLeftPlayerState::ProcessInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		SetNextState<DawnRightPlayerState>(m_animation);
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
	{
		SetNextState<DawnPlayerState>(m_animation);
	}
	if (m_entity->GetRectangle()->getPosition().y == m_entity->GetCapY())
	{
		SetNextState<LeftPlayerState>(m_animation);
	}
}

void DawnLeftPlayerState::Update(const float& dt)
{
	float y = std::min(m_entity->GetRectangle()->getPosition().y + m_entity->GetSpeed() * dt, m_entity->GetCapY());
	m_entity->GetRectangle()->setPosition({ m_entity->GetRectangle()->getPosition().x, y });


	m_entity->GetRectangle()->move({ -m_entity->GetSpeed() * dt, 0 });
	m_animation->UpdateShapeFrame(m_entity->GetRectangle());
}

void DawnLeftPlayerState::OnEnter()
{
	m_entity->SetDirShoot(false);
	m_animation->SetMinMax(23, 31);
}

void DawnRightPlayerState::ProcessInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
	{
		SetNextState<DawnLeftPlayerState>(m_animation);
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		SetNextState<DawnPlayerState>(m_animation);
	}
	if (m_entity->GetRectangle()->getPosition().y == m_entity->GetCapY())
	{
		SetNextState<RightPlayerState>(m_animation);
	}
}

void DawnRightPlayerState::Update(const float& dt)
{

	float y = std::min(m_entity->GetRectangle()->getPosition().y + m_entity->GetSpeed() * dt, m_entity->GetCapY());
	m_entity->GetRectangle()->setPosition({ m_entity->GetRectangle()->getPosition().x, y });

	m_entity->GetRectangle()->move({ m_entity->GetSpeed() * dt, 0 });
	m_animation->UpdateShapeFrame(m_entity->GetRectangle());
	
}

void DawnRightPlayerState::OnEnter()
{
	m_entity->SetDirShoot(true);
	m_animation->SetMinMax(12, 19);
}