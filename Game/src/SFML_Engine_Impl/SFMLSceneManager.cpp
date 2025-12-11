#include <SFML_Engine_Impl/SFMLSceneManager.h>

SFMLSceneManager::SFMLSceneManager(sf::RenderWindow& window): KT::ISceneManager<sf::RenderWindow, Camera>(window)
{}

void SFMLSceneManager::BeginRender()
{
	m_window.clear();
}

void SFMLSceneManager::EndRender()
{
	m_window.display();
}

bool SFMLSceneManager::LoopCondition()
{
	return m_window.isOpen();
}
