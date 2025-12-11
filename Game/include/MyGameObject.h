#pragma once
#include "ObjectToUse.h"
class RandomSquare : public CollidableRectangleComposite
{
public:
	RandomSquare(BaseComposite* parent) : CollidableRectangleComposite(parent) {}
	void OnInit() override
	{
		GetRectangle()->setSize({ 100,100 });
		GetRectangle()->move({ 100,4 });
		GetRectangle()->rotate(sf::degrees(23));
	}
	void Update(float deltatime) override
	{
		GetRectangle()->setFillColor(sf::Color::White);
		CollidableRectangleComposite::Update(deltatime);
	}
};

class Player : public CollidableRectangleComposite
{
public:
	Player(BaseComposite* parent) : CollidableRectangleComposite(parent) {}
	void OnInit() override
	{
		GetRectangle()->setSize({ 100,100 });
		GetRectangle()->move({ 400,4 });
		GetRectangle()->rotate(sf::degrees(23));
	}
	void Update(float deltatime) override
	{
		auto rect = GetRectangle();


		if (ZQSD[0])
			rect->move({ 0,-100 * deltatime });
		if (ZQSD[1])
			rect->move({ -100 * deltatime ,0 });
		if (ZQSD[2])
			rect->move({ 0,100 * deltatime });
		if (ZQSD[3])
			rect->move({ 100 * deltatime,0 });


		CollidableRectangleComposite::Update(deltatime);
	}
	void Input(const std::optional<sf::Event>& event) override
	{
		ZQSD[0] = false;
		ZQSD[1] = false;
		ZQSD[2] = false;
		ZQSD[3] = false;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
		{
			ZQSD[0] = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
		{
			ZQSD[1] = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			ZQSD[2] = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			ZQSD[3] = true;
		}
	}
private:
	bool ZQSD[4];
};