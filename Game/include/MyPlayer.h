#pragma once
#include "ObjectToUse.h"
#include "Core/StateMachine.h"
#include "SFML_Engine_Impl/Animation.h"

class PlayerStateMachine;

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
	KT::StateMachine<MyPlayer>* m_playerStateMachine;
	AnimationManager* m_manager;
	LoopAnimation* m_animation;
	bool mleft;
	bool mright;
};

class PlayerState : public KT::IState<MyPlayer>
{
public:
	PlayerState(MyPlayer* owner,LoopAnimation* anim);

protected:
	LoopAnimation* m_animation;
};

class IdlePlayerState : public PlayerState
{
public:
	IdlePlayerState(MyPlayer* owner, LoopAnimation* anim);

	void ProcessInput() override;

	void Update(const float& dt) override;

	void Render(const float& alpha) override;

	void OnEnter() override;

	void OnExit() override;
};
