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
	void Render(float alpha) override;
	void Input(const std::optional<sf::Event>& event) override;
	void Attack(bool);
private:
	float m_capY;
	KT::StateMachine<MyPlayer>* m_playerStateMachine;
	AnimationManager* m_manager;
	LoopAnimation* m_animation;
	KT::Chrono<float> m_attackCooldown;
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

class IdleBaseState : public PlayerState
{
public:
	IdleBaseState(MyPlayer* owner, LoopAnimation* anim);

	void Update(const float& dt) override;

	void ProcessInput() override;
};

class LeftIdle : public IdleBaseState
{
public:
	LeftIdle(MyPlayer* owner, LoopAnimation* anim);

	void ProcessInput() override;

	void OnEnter() override;
};
class RightIdle : public IdleBaseState
{
public:
	RightIdle(MyPlayer* owner, LoopAnimation* anim);

	void ProcessInput() override;

	void OnEnter() override;
};

class MovingBase : public PlayerState
{
public:
	MovingBase(MyPlayer* owner, LoopAnimation* anim,float dirFactor);

	void Update(const float& dt) override;

protected:
	float m_dirFactor;
};

class MovingLeft : public  MovingBase
{
public:
	MovingLeft(MyPlayer* owner, LoopAnimation* anim);

	void OnEnter() override;

	void ProcessInput() override;
};

class MovingRight : public  MovingBase
{
public:
	MovingRight(MyPlayer* owner, LoopAnimation* anim);

	void OnEnter() override;

	void ProcessInput() override;
};


class JumpIdleBase : public PlayerState
{
public:
	JumpIdleBase(MyPlayer* owner, LoopAnimation* anim);

	void Update(const float& dt) override;

	void ProcessInput() override;
};

class JumpIdleLeftState : public JumpIdleBase
{
public:
	JumpIdleLeftState(MyPlayer* owner, LoopAnimation* anim);

	void ProcessInput() override;

	void OnEnter() override;
};

class JumpIdleRightState : public JumpIdleBase
{
public:
	JumpIdleRightState(MyPlayer* owner, LoopAnimation* anim);

	void ProcessInput() override;

	void OnEnter() override;
};

class BaseJumpMoving : public PlayerState
{
public:
	BaseJumpMoving(MyPlayer* owner, LoopAnimation* anim, float dirFactor);

	void Update(const float& dt) override;

protected:
	float m_dirFactor;
};

class JumpLeft : public BaseJumpMoving
{
public:
	JumpLeft(MyPlayer* owner, LoopAnimation* anim);

	void ProcessInput() override;

	void OnEnter() override;
};

class JumpRight : public BaseJumpMoving
{
public:
	JumpRight(MyPlayer* owner, LoopAnimation* anim);

	void ProcessInput() override;

	void OnEnter() override;
};


/// code here
///
///
///
///
///
///
class DownIdleBase : public PlayerState
{
public:
	DownIdleBase(MyPlayer* owner, LoopAnimation* anim);

	void Update(const float& dt) override;

	void ProcessInput() override;
};

class DownIdleLeftState : public DownIdleBase
{
public:
	DownIdleLeftState(MyPlayer* owner, LoopAnimation* anim);

	void ProcessInput() override;

	void OnEnter() override;
};

class DownIdleRightState : public DownIdleBase
{
public:
	DownIdleRightState(MyPlayer* owner, LoopAnimation* anim);

	void ProcessInput() override;

	void OnEnter() override;
};


class BaseDownMoving : public PlayerState
{
public:
	BaseDownMoving(MyPlayer* owner, LoopAnimation* anim, float dirFactor);

	void Update(const float& dt) override;

protected:
	float m_dirFactor;
};

class DownLeft : public BaseDownMoving
{
public:
	DownLeft(MyPlayer* owner, LoopAnimation* anim);

	void ProcessInput() override;

	void OnEnter() override;
};

class DownRight : public BaseDownMoving
{
public:
	DownRight(MyPlayer* owner, LoopAnimation* anim);

	void ProcessInput() override;

	void OnEnter() override;
};
//
class AttackState : public PlayerState
{
public:
	AttackState(MyPlayer* owner, LoopAnimation* anim,bool isRight);
	void Update(const float& dt) override;
protected:
	bool m_isRight;
	KT::Chrono<float> m_attackTimer;
	bool endAtack;
};

class AttackRightState : public AttackState
{
public:
	AttackRightState(MyPlayer* owner, LoopAnimation* anim);
	void OnEnter() override;
	void ProcessInput() override;
};

class AttackLeftState : public AttackState
{
public:
	AttackLeftState(MyPlayer* owner, LoopAnimation* anim);
	void OnEnter() override;
	void ProcessInput() override;
};
