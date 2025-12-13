#pragma once
#include "ObjectToUse.h"
#include "Core/StateMachine.h"
#include "SFML_Engine_Impl/Animation.h"



class GameScene;
class BusinessManState;

class BusinessMan : public CollidableRectangleComposite
{
public:
	BusinessMan(BaseComposite* parent, float capY);
	void OnDestroy() override;
	void OnInit() override;
	float GetCapY() const;

	void Update(float deltatime) override;

	void Render(float alpha) override;

	void Input(const std::optional<sf::Event>& event) override;
	GameScene* GetMyScene() const;

private:
	float m_capY;
	KT::StateMachine<BusinessMan>* m_playerStateMachine;
	AnimationManager* m_manager;
	LoopAnimation* m_animation;
	KT::Chrono<float> m_coolDown;
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

class BusinessManIdleState : public BusinessManState
{
public:
	BusinessManIdleState(BusinessMan* owner, LoopAnimation* anim);
	void OnEnter() override;
	void Update(const float& dt) override;
};

class BusinessManRightState : public BusinessManState
{
public:
	BusinessManRightState(BusinessMan* owner, LoopAnimation* anim);
	void OnEnter() override;
	void Update(const float& dt) override;
};
class BusinessManLeftState : public BusinessManState
{
public:
	BusinessManLeftState(BusinessMan* owner, LoopAnimation* anim);
	void OnEnter() override;
	void Update(const float& dt) override;
};
