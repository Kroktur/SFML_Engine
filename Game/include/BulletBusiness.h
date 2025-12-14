#pragma once
#include "ObjectToUse.h"
#include "Core/StateMachine.h"
#include "SFML_Engine_Impl/Animation.h"

class Bullet : public CollidableRectangleComposite {
	public:
		 Bullet(BaseComposite* parent, KT::Vector2F pos, bool right);
		 void OnInit() override;  // implement this for initiation
		 void OnDestroy() override; // implement this for destroy

		 void Update(float deltatime) override; // if has no logic don't need
		 void Stop();
		 bool GetIsGoingToDie() const;
		 bool GetIsGoingRight() const;

	private:
		KT::Vector2F m_startPos;
		bool m_isRight;
		bool m_isGoingToDie = false;
		
		KT::StateMachine<Bullet>* m_bulletStateMachine;
	};

class BusinessBulletState : public KT::IState<Bullet>
{
public:
	BusinessBulletState(Bullet* owner, LoopAnimation* anim) : KT::IState<Bullet>(owner), m_animation(anim) {}
	void ProcessInput() override {}
	void Update(const float& dt) override {}
	void Render(const float& alpha) override {}
	void OnEnter() override {}
	void OnExit() override {}

protected:
	LoopAnimation* m_animation;


};

class BulletMoveState : public BusinessBulletState
{
public:
	BulletMoveState(Bullet* owner, LoopAnimation* anim) : BusinessBulletState(owner, anim) {}
	void Update(const float& dt) override;
};

class BulletDyingState : public BusinessBulletState
{
public:
	BulletDyingState(Bullet* owner, LoopAnimation* anim) : BusinessBulletState(owner, anim) {}
	void Update(const float& dt) override;
	void OnEnter() override;
	void OnExit() override;
private:
	KT::Chrono<float> m_lifeTime;
	AnimationManager* m_manager;
	LoopAnimation* m_animation2;
};
