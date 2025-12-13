#pragma once
#include "ObjectToUse.h"
#include "Core/StateMachine.h"
#include "SFML_Engine_Impl/Animation.h"

class BulletPlayer : public CollidableRectangleComposite 
{
public:
	BulletPlayer(BaseComposite* parent, KT::Vector2F pos, bool isGoingRight);
	void OnInit() override;
	void Update(float deltatime) override;
	void Stop();
	void OnDestroy() override;
	bool GetIsGoingRight() const;
	bool GetIsGoingToDie() const;
private:
	float m_capY;
	KT::Vector2F m_startPos;
	bool IsGoingRight = true;
	bool isGoingToDie = false;
	KT::StateMachine<BulletPlayer>* m_bulletStateMachine;
};

class BulletState : public KT::IState<BulletPlayer>
{
public:
	BulletState(BulletPlayer* owner, LoopAnimation* anim) : KT::IState<BulletPlayer>(owner), m_animation(anim) {}
	void ProcessInput() override {}
	void Update(const float& dt) override {}
	void Render(const float& alpha) override {}
	void OnEnter() override {}
	void OnExit() override {}
protected:
	LoopAnimation* m_animation;
};

class MoveBulletState : public BulletState
{
public:
	MoveBulletState(BulletPlayer* owner, LoopAnimation* anim) : BulletState(owner, anim) {};
	void Update(const float& dt) override;
};

class DyingBulletState : public BulletState
{
public:
	DyingBulletState(BulletPlayer* owner, LoopAnimation* anim) : BulletState(owner, anim) {};
	void Update(const float& dt) override;
private: 
	KT::Chrono<float> m_livingTime;
};