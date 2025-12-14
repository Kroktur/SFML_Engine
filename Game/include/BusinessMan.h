#pragma once
#include "ObjectToUse.h"
#include "Core/StateMachine.h"
#include "SFML_Engine_Impl/Animation.h"
#include "Tools/Random.h"


class GameScene;
class BusinessManState;

class BusinessMan : public CollidableRectangleComposite
{
public:
	BusinessMan(BaseComposite* parent, float capY);
	void OnDestroy() override;
	void OnInit() override;
	float GetCapY() const;

	float GetSpeed();
	void Update(float deltatime) override;

	void Render(float alpha) override;
	void Attack();
	void Input(const std::optional<sf::Event>& event) override;
	GameScene* GetMyScene() const;

private:
	float m_capY;
	KT::StateMachine<BusinessMan>* m_playerStateMachine;
	AnimationManager* m_manager;
	LoopAnimation* m_animation;
	KT::Chrono<float> m_coolDown;
	KT::Random m_random;
};

class BusinessManState : public KT::IState<BusinessMan>
{
public:
	BusinessManState(BusinessMan* owner, LoopAnimation* anim);
	void ProcessInput() override {}
	void Update(const float& dt) override {}
	void Render(const float& alpha) override{}
	void OnEnter() override{}
	void OnExit() override{}
protected:
	LoopAnimation* m_animation;
};

class BaseBusinessIdle :public BusinessManState
{
	public:
	BaseBusinessIdle(BusinessMan* owner, LoopAnimation* anim);
	void Update(const float& dt) override;
};

class BusinessIdleLeft : public BaseBusinessIdle
{
	public:
	BusinessIdleLeft(BusinessMan* owner, LoopAnimation* anim);
	void OnEnter() override;
};

class BusinessIdleRight : public BaseBusinessIdle
{
public:
	BusinessIdleRight(BusinessMan* owner, LoopAnimation* anim);
	void OnEnter() override;
};

class BaseBusinessMove :public BusinessManState
{
public:
	BaseBusinessMove(BusinessMan* owner, LoopAnimation* anim, float factor);
	void Update(const float& dt) override;
private:
	float m_dirFactor;
};

class BusinessMoveLeft : public BaseBusinessMove
{
	public:
	BusinessMoveLeft(BusinessMan* owner, LoopAnimation* anim);
	void OnEnter() override;
	void Update(const float& dt) override;
private:
	KT::Random m_random;
	KT::Chrono<float> m_coolDown;
};

class BusinessMoveRight : public BaseBusinessMove
{
	public:
	BusinessMoveRight(BusinessMan* owner, LoopAnimation* anim);
	void OnEnter() override;
	void Update(const float& dt) override;
private:
	KT::Random m_random;
	KT::Chrono<float> m_coolDown;

};

class BusinessBaseAttack : public BusinessManState
{
	public:
	BusinessBaseAttack(BusinessMan* owner, LoopAnimation* anim);
	void Update(const float& dt) override;
protected:
	KT::Chrono<float> m_attackTimer;
	bool m_endAtack;
};

class BusinessAtackLeft : public BusinessBaseAttack
{
	public:
	BusinessAtackLeft(BusinessMan* owner, LoopAnimation* anim);
	void OnEnter() override;
	void Update(const float& dt) override;
};

class BusinessAtackRight: public BusinessBaseAttack
{
public:
	BusinessAtackRight(BusinessMan* owner, LoopAnimation* anim);
	void OnEnter() override;
	void Update(const float& dt) override;
};