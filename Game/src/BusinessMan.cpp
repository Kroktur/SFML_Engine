#include "BusinessMan.h"



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
	GetRectangle()->setSize({ 100,100 });
	GetRectangle()->setPosition({ 0,m_capY });
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
}

void BusinessMan::Render(float alpha)
{
	m_playerStateMachine->Render(alpha);
}

void BusinessMan::Input(const std::optional<sf::Event>& event)
{
	m_playerStateMachine->ProcessInput();
}

BusinessManState::BusinessManState(BusinessMan* owner, LoopAnimation* anim) : KT::IState<BusinessMan>(owner), m_animation(anim)
{
}


BusinessManIdleState::BusinessManIdleState(BusinessMan* owner, LoopAnimation* anim) : BusinessManState(owner, anim)
{
}


void BusinessManIdleState::Update(const float& dt)
{
	m_animation->UpdateShapeFrame(m_entity->GetRectangle());
}


void BusinessManIdleState::OnEnter()
{
	m_animation->SetMinMax(1, 10);
}
