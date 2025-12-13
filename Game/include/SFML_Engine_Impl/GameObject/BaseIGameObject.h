#pragma once
#include <SFML_Engine_Impl/GameObject/IGameObject.h>
#include "SFML_Engine_Impl/GameComponent.h"
#include "Math/AABB.h"
#include "SFML_Engine_Impl/CollisioMapperImpl.h"

//IMPORTANT
//if you see std::unique_ptr<...> toto its work like a pointer but you don't need to delete it and if you need access you need to do toto.get()
// but that only if you want to create your own implementation of GameObject 


#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFMl/Audio/Music.hpp>
#include <SFMl/Audio/Sound.hpp>
#include <SFMl/Audio/SoundBuffer.hpp>

class ISFMLScene;

// LivingGameObject hav 2 function relative to component but it's just a child of IGameObject, must use the child implementation if your not fully in control of what your doing 
class LivingGameObject : public IGameObject
{
public:
	LivingGameObject(ISFMLScene* scene);
	// for the Engine to know if he need to Destroy an Entity
	bool NeedToBeDestroy() const;
	// Use This if you need to kill a GameObject fully automatic 
	void EnableDeath();
private:
	LivingComponent<IGameObject>* m_component;
};

// ALivingGameObject that cary a music
class MusicLGO : public LivingGameObject
{
public:
	MusicLGO(ISFMLScene* scene);
	// This is the function ton get access at your music :)
	sf::Music* GetMusic() const;
private:
	std::unique_ptr<sf::Music> m_music;
};

// ALivingGameObject that cary a sound
class SoundLGO : public LivingGameObject
{
public:
	// mus be initialize with the SoundBufferLoader for sf::SoundBuffer
	SoundLGO(ISFMLScene* scene,const sf::SoundBuffer& buffer);
	// This is the function ton get access at your sound :)
	sf::Sound* GetSound() const;
private:
	std::unique_ptr<sf::Sound> m_sound;
};



// This Child is Use For ALl the Object that can be render in the game,  must use the child implementation if your not fully in control of what your doing
class BaseRendererLGO : public LivingGameObject
{
public:
	BaseRendererLGO(ISFMLScene* scene);
	//Some Obvius function to render shape / text  or the OBB box for the shape
	virtual void EnableMainRender();
	virtual void EnableBoxRender() const;
	virtual void DisableMainRender() const;
	virtual  void DisableBoxRender() const;
	virtual bool IsMainActiveRender() const;
	virtual bool IsBoxActiveRender() const;
	// give you the local AABB
	virtual KT::AABB2DF LocalBox() const = 0;
	// Red by default
	virtual void SetBoxColor(sf::Color color) const = 0;
	// this is where the render is automatic so if you use a child class or struct be sure to call BaseRendererLGO::Render(alpha)
	void PrivRender(float alpha) override;
protected:
	// its automatic (if you use child) don't touch if not call it to add a new item to render or override render
	void AddDrawable(sf::Drawable* drawable, bool active = true);
	GraphicComponent<IGameObject>* m_component;
};
// Same as BaseRenderLGO but have  a full setup rectangle with automatic render
class RectangleRLGO : public  BaseRendererLGO
{

public:
	// need 5 line because of sfml don't ask question lol
	static constexpr size_t line_size = 5;
	RectangleRLGO(ISFMLScene* scene);
	// This is the function ton get access at your rectangle :)
	sf::RectangleShape* GetRectangle() const;
	KT::AABB2DF LocalBox() const override;
	void SetBoxColor(sf::Color color) const override;
	// IMPORTANT automatic logic for box if you want debug tool YOU MUST CALL THIS implementation like that : RectangleRLGO::Update(deltatime) in child class 
	void PrivUpdate(float deltatime) override;
private:
	// basic Rectangle
	std::unique_ptr<sf::RectangleShape> m_rect;
	// line to draw the box
	std::unique_ptr< sf::VertexArray> m_array;
	KT::AABB2DF m_box;
};
// Same as RectangleRLGO but have automatic collision detection
class CollidableRectangleRLGO : public RectangleRLGO
{
public:
	CollidableRectangleRLGO(ISFMLScene* scene);
	// IMPORTANT automatic logic for collision if you want debug tool YOU MUST CALL THIS implementation like that : CollidableRectangleRLGO::Update(deltatime) in child class 
	void PrivUpdate(float deltatime) override;
	void DisableCollision(size_t index);

private:
	CollisionComponent<IGameObject>* m_component;
};


// Same as BaseRenderLGO but have  a full setup text with automatic render
class TextRLGO : public  BaseRendererLGO
{
public:
	// need 5 line because of sfml don't ask question lol
	static constexpr size_t line_size = 5;
	// mus be initialize with the FontLoader for sf::Font
	TextRLGO(ISFMLScene* scene,const sf::Font& font);
	// This is the function ton get access at your text :)
	sf::Text* GetText() const;
	KT::AABB2DF LocalBox() const override;
	void SetBoxColor(sf::Color color)  const override;
	// IMPORTANT automatic logic for box if you want debug tool YOU MUST CALL THIS implementation like that : TextRLGO::Update(deltatime) in child class 
	void PrivUpdate(float deltatime) override;
private:
	// basic text
	std::unique_ptr<sf::Text> m_text;
	// line to draw the box
	std::unique_ptr< sf::VertexArray> m_array;
	KT::AABB2DF m_box;
};

// Same as BaseRenderLGO but have  a full setup circle with automatic render
class CircleRLGO : public  BaseRendererLGO
{

public:
	// need 5 line because of sfml don't ask question lol
	static constexpr size_t line_size = 5;
	CircleRLGO(ISFMLScene* scene);
	// This is the function ton get access at your circle :)
	sf::CircleShape* GetCirle() const;
	KT::AABB2DF LocalBox() const override;
	void SetBoxColor(sf::Color color) const override;
	// IMPORTANT automatic logic for box if you want debug tool YOU MUST CALL THIS implementation like that : CircleRLGO::Update(deltatime) in child class 
	void PrivUpdate(float deltaTime) override;
private:
	// basic Circle
	std::unique_ptr<sf::CircleShape> m_circle;
	// line to draw the box
	std::unique_ptr< sf::VertexArray> m_array;
	KT::AABB2DF m_box;
};

// Same as CircleRLGO but have  a automatic collision detection
class CollidableCircleRLGO : public CircleRLGO
{
public:
	CollidableCircleRLGO(ISFMLScene* scene);
	// IMPORTANT automatic logic for collision if you want debug tool YOU MUST CALL THIS implementation like that : CollidableCircleRLGO::Update(deltatime) in child class 
	void PrivUpdate(float deltatime) override;
	void DisableCollision(size_t index);

private:
	CollisionComponent<IGameObject>* m_component;
};

//class GORectComposite : public RectangleRLGO,public SFMLComposite<GORectComposite>
//{
//public:
//	GORectComposite(BaseComposite* owenr) : SFMLComposite<GORectComposite>(owenr),RectangleRLGO(owenr->GetRoot()->AsRoot()){}
//
//	void OnInit() override
//	{
//	//	auto* rect = GetRectangle();
//
//	//	rect->setPosition({ 300,300 });
//	//	rect->setSize({ 100,100 });
//	//	rect->setRotation(sf::degrees(60));
//	///*	DisableMainRender();*/
//	//	EnableBoxRender();
//	}
//};
//
//class Player : GORectComposite
//{
//public:
//	Player(BaseComposite* owenr) :GORectComposite(owenr){}
//	void OnInit() override
//	{
//		auto* rect = GetRectangle();
//		rect->setTexture(&TextureLoader::Load("test.jpg",false,{}));
//		rect->setPosition({ 300,300 });
//		rect->setScale({ 1,1 });
//		rect->setSize({ 100,100 });
//		rect->setRotation(sf::degrees(60));
//		/*	DisableMainRender();*/
//		EnableBoxRender();
//	}
//	void Input(const std::optional<sf::Event>& event) override
//	{
//	/*	m_scene->AddStartingAction([&]
//			{
//				auto* cast = static_cast<SFMLComposite<GORectComposite>*>(static_cast<GORectComposite*>(this));
//				auto* root = cast->GetRoot();
//				new Player(root);
//			}
//		);*/
//	}
//};