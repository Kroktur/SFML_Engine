
#include "SFML_Engine_Impl/GameObject/BaseIGameObject.h"
#include "SFML_Engine_Impl/ISFMLScene.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFMl/Audio/Music.hpp>
#include <SFMl/Audio/Sound.hpp>
#include <SFMl/Audio/SoundBuffer.hpp>
LivingGameObject::LivingGameObject(ISFMLScene* scene):IGameObject(scene)
{
	m_component = AddComponent<LivingComponent<IGameObject>>();
}

bool LivingGameObject::NeedToBeDestroy() const
{
	return m_component->IsLiving();
}

void LivingGameObject::EnableDeath()
{
	m_component->EnableDeath();
}

MusicLGO::MusicLGO(ISFMLScene* scene) : LivingGameObject(scene),m_music(std::make_unique<sf::Music>())
{
}

sf::Music* MusicLGO::GetMusic() const
{
	return m_music.get();
}

SoundLGO::SoundLGO(ISFMLScene* scene, const sf::SoundBuffer& buffer) : LivingGameObject(scene), m_sound(std::make_unique<sf::Sound>(buffer))
{
}

sf::Sound* SoundLGO::GetSound() const
{
	return m_sound.get();
}

BaseRendererLGO::BaseRendererLGO(ISFMLScene* scene):LivingGameObject(scene)
{
	m_component = AddComponent<GraphicComponent<IGameObject>>();
}

void BaseRendererLGO::AddDrawable(sf::Drawable* drawable, bool active)
{
	m_component->AddObject(drawable, active);
}

void BaseRendererLGO::EnableMainRender()
{
	m_component->EnableRender(0);
}

void BaseRendererLGO::EnableBoxRender() const
{
	m_component->EnableRender(1);
}

void BaseRendererLGO::DisableMainRender() const
{
	m_component->DisableRender(0);
}

void BaseRendererLGO::DisableBoxRender() const
{
	m_component->DisableRender(1);
}

bool BaseRendererLGO::IsMainActiveRender() const
{
	return m_component->IsRenderable(0);
}

bool BaseRendererLGO::IsBoxActiveRender() const
{
	return m_component->IsRenderable(1);
}

void BaseRendererLGO::PrivRender(float alpha)
{
	auto render = GetComponent<GraphicComponent<IGameObject>>();
	auto& window = m_scene->GetWindow();
	render->Render(&window);
}

RectangleRLGO::RectangleRLGO(ISFMLScene* scene):BaseRendererLGO(scene), m_rect(std::make_unique<sf::RectangleShape>()),m_array(std::make_unique<sf::VertexArray>(sf::PrimitiveType::LineStrip, line_size))
{
	AddDrawable(m_rect.get());
	AddDrawable(m_array.get(),false);
	for (int i = 0; i < line_size; ++i)
		(*m_array)[i].color = sf::Color::Red;
}

sf::RectangleShape* RectangleRLGO::GetRectangle() const
{
	return m_rect.get();
}

KT::AABB2DF RectangleRLGO::LocalBox() const
{
	return m_box;
}

void RectangleRLGO::SetBoxColor(sf::Color color) const
{
	for (int i = 0; i < line_size; ++i)
		(*m_array)[i].color = color;
}

void RectangleRLGO::PrivUpdate(float deltatime)
{

	if (IsBoxActiveRender())
	{
		auto localBounds = m_rect->getLocalBounds();
		m_box.Amin = { localBounds.position.x,localBounds.position.y };
		m_box.Amax = { localBounds.position.x + localBounds.size.x,localBounds.position.y + localBounds.size.y };

		auto bl = m_rect->getTransform().transformPoint({ m_box.Amin.x,m_box.Amin.y });
		auto br = m_rect->getTransform().transformPoint({ m_box.Amax.x,m_box.Amin.y });
		auto tl = m_rect->getTransform().transformPoint({ m_box.Amin.x,m_box.Amax.y });
		auto tr = m_rect->getTransform().transformPoint({ m_box.Amax.x,m_box.Amax.y });

		(*m_array)[0].position = bl;
		(*m_array)[1].position = br;
		(*m_array)[2].position = tr;
		(*m_array)[3].position = tl;
		(*m_array)[4].position = bl;
	}
}

CollidableRectangleRLGO::CollidableRectangleRLGO(ISFMLScene* scene): RectangleRLGO(scene)
{
	m_component = AddComponent<CollisionComponent<IGameObject>>();
	m_component->SetTransform(GetRectangle());
	m_component->AddOBB();
}



void CollidableRectangleRLGO::PrivUpdate(float deltatime)
{
	m_component->SetOBB( 0,Mapper2DRectangle::GetOrCreateOBB({ GetRectangle()->getSize().x,GetRectangle()->getSize().y },GetRectangle()));
	RectangleRLGO::PrivUpdate(deltatime);
}

TextRLGO::TextRLGO(ISFMLScene* scene, const sf::Font& font):BaseRendererLGO(scene), m_text(std::make_unique<sf::Text>(font)), m_array(std::make_unique<sf::VertexArray>(sf::PrimitiveType::LineStrip, line_size))
{
	AddDrawable(m_text.get());
	AddDrawable(m_array.get(), false);
	for (int i = 0; i < line_size; ++i)
		(*m_array)[i].color = sf::Color::Red;

}

sf::Text* TextRLGO::GetText() const
{
	return m_text.get();
}

KT::AABB2DF TextRLGO::LocalBox() const
{
	return m_box;
}

void TextRLGO::SetBoxColor(sf::Color color) const
{
	for (int i = 0; i < line_size; ++i)
		(*m_array)[i].color = color;
}

void TextRLGO::PrivUpdate(float deltatime)
{

	if (IsBoxActiveRender())
	{

		auto localBounds = m_text->getLocalBounds();
		m_box.Amin = { localBounds.position.x,localBounds.position.y };
		m_box.Amax = { localBounds.position.x + localBounds.size.x,localBounds.position.y + localBounds.size.y };

		auto bl = m_text->getTransform().transformPoint({ m_box.Amin.x,m_box.Amin.y });
		auto br = m_text->getTransform().transformPoint({ m_box.Amax.x,m_box.Amin.y });
		auto tl = m_text->getTransform().transformPoint({ m_box.Amin.x,m_box.Amax.y });
		auto tr = m_text->getTransform().transformPoint({ m_box.Amax.x,m_box.Amax.y });

		(*m_array)[0].position = bl;
		(*m_array)[1].position = br;
		(*m_array)[2].position = tr;
		(*m_array)[3].position = tl;
		(*m_array)[4].position = bl;
	}
}

CircleRLGO::CircleRLGO(ISFMLScene* scene):BaseRendererLGO(scene), m_circle(std::make_unique<sf::CircleShape>()), m_array(std::make_unique<sf::VertexArray>(sf::PrimitiveType::LineStrip, line_size))
{
	AddDrawable(m_circle.get());
	AddDrawable(m_array.get(), false);
	for (int i = 0; i < line_size; ++i)
		(*m_array)[i].color = sf::Color::Red;


}

sf::CircleShape* CircleRLGO::GetCirle() const
{
	return m_circle.get();
}

KT::AABB2DF CircleRLGO::LocalBox() const
{
	return m_box;
}

void CircleRLGO::SetBoxColor(sf::Color color) const
{
	for (int i = 0; i < line_size; ++i)
		(*m_array)[i].color = color;
}

void CircleRLGO::PrivUpdate(float deltaTime)
{

	if (IsBoxActiveRender())
	{
		auto localBounds = m_circle->getLocalBounds();
		m_box.Amin = { localBounds.position.x,localBounds.position.y };
		m_box.Amax = { localBounds.position.x + localBounds.size.x,localBounds.position.y + localBounds.size.y };

		auto bl = m_circle->getTransform().transformPoint({ m_box.Amin.x,m_box.Amin.y });
		auto br = m_circle->getTransform().transformPoint({ m_box.Amax.x,m_box.Amin.y });
		auto tl = m_circle->getTransform().transformPoint({ m_box.Amin.x,m_box.Amax.y });
		auto tr = m_circle->getTransform().transformPoint({ m_box.Amax.x,m_box.Amax.y });

		(*m_array)[0].position = bl;
		(*m_array)[1].position = br;
		(*m_array)[2].position = tr;
		(*m_array)[3].position = tl;
		(*m_array)[4].position = bl;
	}
}

CollidableCircleRLGO::CollidableCircleRLGO(ISFMLScene* scene): CircleRLGO(scene)
{
	m_component = AddComponent<CollisionComponent<IGameObject>>();
	m_component->SetTransform(GetCirle());
	m_component->AddOBB();
}

void CollidableCircleRLGO::PrivUpdate(float deltatime)
{
	m_component->SetOBB(0,Mapper2DCircle::GetOrCreateOBB(GetCirle()->getRadius(), GetCirle())); 
	CircleRLGO::PrivUpdate(deltatime);
}
