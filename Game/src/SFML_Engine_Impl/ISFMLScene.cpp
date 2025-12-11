#include "SFML_Engine_Impl/ISFMLScene.h"

ISFMLScene::ISFMLScene(const KT::Chrono<float>::Time& refreshTime): KT::ISceneBase<sf::RenderWindow, Camera>(refreshTime)
{}

void ISFMLScene::AddStartingAction(const std::function<void()>& fn)
{
	m_startingAction.push_back(fn);
}

void ISFMLScene::AddEndingAction(const std::function<void()>& fn)
{
	m_endingAction.push_back(fn);
}

void ISFMLScene::ExecuteStartingAction()
{
	for (auto& fn : m_startingAction)
		fn();
	m_startingAction.clear();
}

void ISFMLScene::ExecuteEndingAction()
{
	for (auto& fn : m_endingAction)
		fn();
	m_endingAction.clear();
}
