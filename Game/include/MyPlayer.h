#pragma once
#include "ObjectToUse.h"
#include "Core/StateMachine.h"
#include "SFML_Engine_Impl/Animation.h"


class MyPlayer : public CollidableRectangleComposite
{
public:
	MyPlayer(BaseComposite* parent,float capY);
	void OnDestroy() override;
	void OnInit() override;
	float GetCapY() const;

	void Update(float deltatime) override;

	void Render(float alpha) override;

	void Input(const std::optional<sf::Event>& event) override;

private:
	float m_capY;
	AnimationManager* m_manager;
	LoopAnimation* m_animation;

};

