#include "MyPlayer.h"

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

void MyPlayer::Update(float deltatime)
{
	m_playerStateMachine->ChangeState();
	m_playerStateMachine->Update(deltatime);
}

void MyPlayer::Render(float alpha)
{
	m_playerStateMachine->Render(alpha);
}

void MyPlayer::Input(const std::optional<sf::Event>& event)
{
	m_playerStateMachine->ProcessInput();
}

PlayerState::PlayerState(MyPlayer* owner, LoopAnimation* anim): KT::IState<MyPlayer>(owner),m_animation(anim)
{}

IdlePlayerState::IdlePlayerState(MyPlayer* owner, LoopAnimation* anim): PlayerState(owner, anim)
{}

void IdlePlayerState::ProcessInput()
{
		
}

void IdlePlayerState::Update(const float& dt)
{
	m_animation->UpdateShapeFrame(m_entity->GetRectangle());
}

void IdlePlayerState::Render(const float& alpha)
{
		
}

void IdlePlayerState::OnEnter()
{
	m_animation->SetMinMax(1, 10);
}

void IdlePlayerState::OnExit()
{
		
}
