#include "SFML_Engine_Impl/GameObject/IGameObject.h"
#include "SFML_Engine_Impl/ISFMLScene.h"

IGameObject::IGameObject(ISFMLScene* scene): KT::ComponentManager<IGameObject>(this), m_scene(scene)
{}

IGameObject::~IGameObject() = default;

void IGameObject::OnInit()
{}

void IGameObject::OnDestroy()
{}

void IGameObject::Update(float deltatime)
{}

void IGameObject::Input(const std::optional<sf::Event>& event)
{}

void IGameObject::Render(float alpha)
{}
