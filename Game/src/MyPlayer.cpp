#include "MyPlayer.h"

MyPlayer::MyPlayer(BaseComposite* parent, float capY) : CollidableRectangleComposite(parent), m_capY(capY), m_manager(nullptr), m_animation(nullptr)
{}

void MyPlayer::OnDestroy()
{
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
}

float MyPlayer::GetCapY() const
{
	return m_capY;
}

void MyPlayer::Update(float deltatime)
{
	m_animation->UpdateShapeFrame(GetRectangle());
}

void MyPlayer::Render(float alpha)
{

}

void MyPlayer::Input(const std::optional<sf::Event>& event)
{
}

