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

	void Input(const std::optional<sf::Event>& event) override;

private:
	bool ZQSD[4];
};