#pragma once
#include <Core/GameLoop.h>
#include <SFML/Graphics/RenderWindow.hpp>

//TODO remove when camera folder ready
#include "ISFMLScene.h"




class SFMLSceneManager : public KT::ISceneManager<sf::RenderWindow, Camera>
{
public:
	SFMLSceneManager(sf::RenderWindow& window);
	void BeginRender() override;
	void EndRender() override;
	bool LoopCondition() override;
};

