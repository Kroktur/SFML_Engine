#pragma once
#include "SFML_Engine_Impl/Animation.h"
#include "ObjectToUse.h"
class RandomSquare : public CollidableRectangleComposite
{
public:
	RandomSquare(BaseComposite* parent);

	void OnInit() override;

	void Update(float deltatime) override;

	void OnDestroy() override;
	AnimationManager* m_manager;
	LoopAnimation* m_animation;
};

class Player : public CollidableRectangleComposite
{
public:
	Player(BaseComposite* parent);

	void OnInit() override;

	void Update(float deltatime) override;

	AnimationManager* m_managerPlayer;
	LoopAnimation* m_animationPlayer;
	void Input(const std::optional<sf::Event>& event) override;

private:
	bool moveLeft = false;
	bool moveRight = false;
	bool jump = false;
	bool movingUp = false;
	bool movingDown = false;
};

class MyCircle : public CollidableCircleComposite {
public:
	MyCircle(BaseComposite* parent) : CollidableCircleComposite(parent) {}
	void OnInit() override
	{
		GetCirle()->setRadius({ 50 });
		GetCirle()->setFillColor(sf::Color::Red);
		GetCirle()->setPosition({ 800,800 });
	}// implement this for initiation
	void OnDestroy() override
	{

	}// implement this for destroy
	void Update(float deltatime) override
	{
		CollidableCircleComposite::Update(deltatime);
		GetCirle()->setFillColor(sf::Color::Red);

	}
	void Render(float alpha) override
	{
		CollidableCircleComposite::Render(alpha);

	}
};