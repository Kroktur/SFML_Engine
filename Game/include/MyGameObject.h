#pragma once
#include "SFML_Engine_Impl/Animation.h"
#include "ObjectToUse.h"

class Enemy : public CollidableRectangleComposite
{
public:
	Enemy(BaseComposite* parent);

	void OnInit() override;

	void Update(float deltatime) override;

	void Input(const std::optional<sf::Event>& event) override;

	void OnDestroy() override;

	AnimationManager* m_manager;
	LoopAnimation* m_animation;

private:
	bool ZQSD[4];
};


  class MyClassRect : public CollidableRectangleComposite
  {
  public:
	  MyClassRect(BaseComposite* parent) : CollidableRectangleComposite(parent){}
	  void OnInit() override {
		  GetRectangle()->setSize({ 100.0f, 100.0f });
		  GetRectangle()->setPosition({ 600, 500 });
		  GetRectangle()->setFillColor(sf::Color::Green);
		  GetRectangle()->setOrigin(GetRectangle()->getSize() / 2.0f);
	  }
	  // implement this for initiation
	  void OnDestroy() override {
	  }
		  // implement this for destroy
	  void Render(float alpha) override {
		  CollidableRectangleComposite::Render(alpha);
	  }// if you don't need to render a specific object automatic 
	  void Input(const std::optional<sf::Event>& event) override {
	  }
		  // if has no input don't need
	  void Update(float deltatime) override {
		  CollidableRectangleComposite::Update(deltatime);
	  }
		  // if has no logic don't need
};

  class MyClassCircle : public CollidableCircleComposite
  {
  public:
	  MyClassCircle(BaseComposite* parent) : CollidableCircleComposite(parent) {}
	  void OnInit() override {
		  GetCirle()->setRadius(20);
		  GetCirle()->setPosition({ 100, 200 });
		  GetCirle()->setFillColor(sf::Color::Red);
		  GetCirle()->setOrigin({20,20});
	  }
	  // implement this for initiation
	  void OnDestroy() override {
	  }
	  // implement this for destroy
	  void Render(float alpha) override {
		  CollidableCircleComposite::Render(alpha);
	  }// if you don't need to render a specific object automatic 
	  void Input(const std::optional<sf::Event>& event) override {
	  }
	  // if has no input don't need
	  void Update(float deltatime) override {
		  CollidableCircleComposite::Update(deltatime);
		  GetCirle()->setFillColor(sf::Color::Red);

		  
	  }
	  // if has no logic don't need
  };