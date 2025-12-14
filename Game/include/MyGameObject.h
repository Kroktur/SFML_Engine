#pragma once
#include "SFML_Engine_Impl/Animation.h"
#include "ObjectToUse.h"

class Rect : public CollidableRectangleComposite
{
public:
	Rect(BaseComposite* parent) : CollidableRectangleComposite(parent) {}
	void OnInit() override; // implement this for initiation
	void OnDestroy() override; // implement this for destroy
	void Render(float alpha) override; // if you don't need to render a specific object automatic 
	void Input(const std::optional<sf::Event>& event) override; // if has no input don't need
	};
class MyGameObject : public CollidableRectangleComposite
{
public:
	MyGameObject(BaseComposite* parent);
	void OnInit() override;
	void Update(float deltatime) override;
	void OnDestroy() override;

};

class EmptyComposite : public RectangleComposite
{
public:
	EmptyComposite(BaseComposite* base) : RectangleComposite(base) {}
};

class BackGround : public RectangleComposite
{
public:
	BackGround(BaseComposite* parent) : RectangleComposite(parent),m_scored(20),factor(10) {}
	void OnInit() override;
	void Update(float deltatime) override;
	void AddScore();
	void RemoveScore();
private:
	float m_scored;
	int factor;
	
};
