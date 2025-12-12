#pragma once
#include <functional>
#include <Core/Scene.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Camera.h"

class ISFMLScene : public KT::ISceneBase<sf::RenderWindow, Camera>
{
public:
	ISFMLScene(const KT::Chrono<float>::Time& refreshTime);

	void AddStartingAction(const std::function<void()>& fn);

	void AddEndingAction(const std::function<void()>& fn);

protected:
	void ExecuteStartingAction();

	void ExecuteEndingAction();

private:
	std::vector<std::function<void()>> m_startingAction;
	std::vector<std::function<void()>> m_endingAction;
};


