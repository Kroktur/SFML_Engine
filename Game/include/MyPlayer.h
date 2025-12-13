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
	float GetSpeed() const;
	float GetJumpHeight() const;
	void Update(float deltatime) override;
	void SetDirShoot(bool shootRight);
	void Render(float alpha) override;

	void Input(const std::optional<sf::Event>& event) override;
	void Attack();
private:
	float m_capY;
	KT::StateMachine<MyPlayer>* m_playerStateMachine;
	AnimationManager* m_manager;
	LoopAnimation* m_animation;
	KT::Chrono<float> m_attackCooldown;
	bool isShootingRight;
};

class PlayerState : public KT::IState<MyPlayer>
{
public:
	PlayerState(MyPlayer* owner,LoopAnimation* anim);
	void ProcessInput() override{}
	void Update(const float& dt) override {}
	void Render(const float& alpha) override {}
	void OnEnter() override {}
	void OnExit() override {}
protected:
	LoopAnimation* m_animation;
};

class IdlePlayerState : public PlayerState
{
public:
	IdlePlayerState(MyPlayer* owner, LoopAnimation* anim);

	void ProcessInput() override;

	void Update(const float& dt) override;

	void OnEnter() override;
private : 

};

class LeftPlayerState : public PlayerState
{
public:
	LeftPlayerState(MyPlayer* owner, LoopAnimation* anim) : PlayerState(owner, anim) {};

	void ProcessInput() override;

	void Update(const float& dt) override;

	void OnEnter() override;

};

class RightPlayerState : public PlayerState
{
public:
	RightPlayerState(MyPlayer* owner, LoopAnimation* anim) : PlayerState(owner, anim) {};

	void ProcessInput() override;

	void Update(const float& dt) override;

	void OnEnter() override;

};

class JumpPlayerState : public PlayerState
{
public:
	JumpPlayerState(MyPlayer* owner, LoopAnimation* anim);

	void ProcessInput() override;

	void Update(const float& dt) override;

	void OnEnter() override;
private:

};

class JumpLeftPlayerState : public PlayerState
{
public:
	JumpLeftPlayerState(MyPlayer* owner, LoopAnimation* anim) : PlayerState(owner, anim) {};

	void ProcessInput() override;

	void Update(const float& dt) override;

	void OnEnter() override;

};

class JumpRightPlayerState : public PlayerState
{
public:
	JumpRightPlayerState(MyPlayer* owner, LoopAnimation* anim) : PlayerState(owner, anim) {};

	void ProcessInput() override;

	void Update(const float& dt) override;

	void OnEnter() override;

};

class DawnPlayerState : public PlayerState
{
public:
	DawnPlayerState(MyPlayer* owner, LoopAnimation* anim);

	void ProcessInput() override;

	void Update(const float& dt) override;

	void OnEnter() override;
private:

};

class DawnLeftPlayerState : public PlayerState
{
public:
	DawnLeftPlayerState(MyPlayer* owner, LoopAnimation* anim) : PlayerState(owner, anim) {};

	void ProcessInput() override;

	void Update(const float& dt) override;

	void OnEnter() override;

};

class DawnRightPlayerState : public PlayerState
{
public:
	DawnRightPlayerState(MyPlayer* owner, LoopAnimation* anim) : PlayerState(owner, anim) {};

	void ProcessInput() override;

	void Update(const float& dt) override;

	void OnEnter() override;

};
