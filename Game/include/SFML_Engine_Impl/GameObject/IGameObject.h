#pragma once
#include "Core/Component.h"
#include <optional>

// Forward Declaration don't mind 
class ISFMLScene;
namespace sf
{
	class Event;
}

//Base Of All GameObject
//ComponentManager Is here for Instantiate Component don't touch it 
//For All virtual function except destructor you must use the child implementation if your not fully in control of what your doing 
class IGameObject : public KT::ComponentManager<IGameObject>
{
public:
	// Basic Ctor but priority at OnInit need Scene To Be Created 
	IGameObject(ISFMLScene* scene);
	// Default Constructor Override it Only if really needed priority at OnDestroy
	virtual ~IGameObject();
	// Put here everything for initialisation
	virtual void OnInit();
	// Put here everything that need to be done before delete  
	virtual void OnDestroy();
	// Update Function put here all the physics and stuff like move rotate ...
	virtual void Update(float deltatime);
	// Put only the input here no move no rotate nothing juste put variable like is_moving and move it in the update
	virtual void Input(const std::optional<sf::Event>& event);
	// render your item IMPORTANT automatic if you do not instantiate a new shape or text 
	virtual void Render(float alpha);
protected:
	// pointer to the Scene
	ISFMLScene* m_scene;
};