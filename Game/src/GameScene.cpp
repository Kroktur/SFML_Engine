#include "GameScene.h"
#include "MyGameObject.h"
#include "SFML_Engine_Impl/PhysicSolver.h"
#include "CollisionRule.h"
#include "BusinessMan.h"
#include "MyPlayer.h"

GameScene::GameScene(const KT::Chrono<float>::Time& refreshTime): ISFMLScene(refreshTime)
{}



void GameScene::MyInit()
{
	auto* root = static_cast<SFMLRoot<GameScene>*>(this);
	//First of All Init Dispatcher

	//m_dispatcher.Add< RandomSquare, Player, Rule::Collide, true>();

	TextureLoader::Load("SpriteSheet_Nova.png", {}, {});
	
	// create start Object here
	/*new CollidableRectangleRLGO(root);*/
	m_player = new MyPlayer(root, 300.0f);
	new BusinessMan(root, 800.0f);
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
