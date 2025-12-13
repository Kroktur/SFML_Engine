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
	bool shooting = false;
};

class Bullet : public CollidableRectangleComposite
{
public:
	Bullet(BaseComposite* parent);
	void OnInit() override;
	void Update(float deltatime) override;
};
