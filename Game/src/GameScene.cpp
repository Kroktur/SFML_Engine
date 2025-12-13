#include "GameScene.h"
#include "MyGameObject.h"
#include "SFML_Engine_Impl/PhysicSolver.h"
#include "CollisionRule.h"
#include "MyPlayer.h"
#include "BulletPlayer.h"

GameScene::GameScene(const KT::Chrono<float>::Time& refreshTime): ISFMLScene(refreshTime)
{}



void GameScene::MyInit()
{
	auto* root = static_cast<SFMLRoot<GameScene>*>(this);
	//First of All Init Dispatcher

	m_dispatcher.Add< MyPlayer, BulletPlayer, Rule::Collide, true>();
	m_dispatcher.Add< BulletPlayer, BulletPlayer, Rule::Collide, false>();
	m_dispatcher.Add< MyGameObject, MyPlayer, Rule::Collide, true>();
	m_dispatcher.Add< MyGameObject, BulletPlayer, Rule::Collide, true>();



	TextureLoader::Load("SpriteSheet_Nova.png", {}, {});
	
	// create start Object here
	/*new CollidableRectangleRLGO(root);*/
	m_player = new MyPlayer(root, 500.0f);
	new MyGameObject(root);
	
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
