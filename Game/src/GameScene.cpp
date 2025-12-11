#include "GameScene.h"
#include "MyGameObject.h"
#include "SFML_Engine_Impl/PhysicSolver.h"
#include "CollisionRule.h"

GameScene::GameScene(const KT::Chrono<float>::Time& refreshTime): ISFMLScene(refreshTime)
{}



void GameScene::MyInit()
{
	auto* root = static_cast<SFMLRoot<GameScene>*>(this);
	//First of All Init Dispatcher
	m_dispatcher.Add< RandomSquare, Player, Rule::Collide, true>();

	
	
	// create start Object here
	/*new CollidableRectangleRLGO(root);*/
	auto* player = new Player(root);
	new RandomSquare(root);

}

void GameScene::MyUpdate(const float& deltatime)
{

}

void GameScene::MyInput(const std::optional<sf::Event>& event)
{
	
}

void GameScene::MyRender(const float& alpha)
{
	
}

void GameScene::MyDestroy()
{
}
