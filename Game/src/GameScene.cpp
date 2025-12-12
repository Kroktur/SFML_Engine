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
	m_dispatcher.Add< MyClassCircle, Enemy, Rule::Collide, true>();
	m_dispatcher.Add< Enemy, MyClassRect, Rule::Collide, true>();

	TextureLoader::Load("SpriteSheet_Nova.png", {}, {});
	
	// create start Object here
	new MyClassCircle(root);
	new MyClassRect(root);


	/*new CollidableRectangleRLGO(root);*/
	auto* player = new Enemy(root);
	

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
