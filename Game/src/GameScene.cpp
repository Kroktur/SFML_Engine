#include "GameScene.h"
#include "MyGameObject.h"
#include "SFML_Engine_Impl/PhysicSolver.h"
#include "CollisionRule.h"
#include "BusinessMan.h"
#include "MyPlayer.h"
#include "BulletPlayer.h"
#include "Wall.h"

GameScene::GameScene(const KT::Chrono<float>::Time& refreshTime): ISFMLScene(refreshTime)
{}



void GameScene::MyInit()
{
	auto* root = static_cast<SFMLRoot<GameScene>*>(this);
	//First of All Init Dispatcher

	m_dispatcher.Add< Bullet, Bullet, Rule::Collide, false>();
	m_dispatcher.Add< BusinessMan, MyPlayer, Rule::Collide, true>();
	m_dispatcher.Add< MyPlayer, Bullet, Rule::Collide, true>();
	m_dispatcher.Add< Bullet, BulletPlayer, Rule::Collide, true>();

	//proper Rules
	m_dispatcher.Add< MyPlayer, WallToBlock, Rule::Collide, true>();
	m_dispatcher.Add< BulletPlayer, WallToBlock, Rule::Collide, true>();
	m_dispatcher.Add< BulletPlayer, WallToDestroy, Rule::Collide, true>();
	m_dispatcher.Add< BusinessMan, WallToBlock, Rule::Collide, true>();
	m_dispatcher.Add< Bullet, WallToBlock, Rule::Collide, true>();
	m_dispatcher.Add< Bullet, WallToDestroy, Rule::Collide, true>();

	m_dispatcher.Add< MyPlayer, BulletPlayer, Rule::Collide, true>();
	m_dispatcher.Add< BulletPlayer, BulletPlayer, Rule::Collide, false>();
	m_dispatcher.Add< BusinessMan, Bullet, Rule::Collide, true>();
	m_dispatcher.Add< BulletPlayer, BusinessMan, Rule::Collide, true>();
	m_dispatcher.Add< BusinessMan, WallToDestroy, Rule::Collide, true>();
	m_dispatcher.Add< BusinessMan, BusinessMan, Rule::Collide, false>();


	TextureLoader::Load("SpriteSheet_Nova.png", {}, {});
	
	// create start Object here
	/*new CollidableRectangleRLGO(root);*/

	 m_layer1 = new EmptyComposite(root);
	
	 m_layer2 = new EmptyComposite(root);

	 new WallToBlock(m_layer2, { -100,0 }, { 100, static_cast<float>(GetWindow().getSize().y) });
	 new WallToBlock(m_layer2, { static_cast<float>(GetWindow().getSize().x),0 }, { 100, static_cast<float>(GetWindow().getSize().y) });
	 new WallToDestroy(m_layer2, { -2 - 500.0f,0 }, { 2, static_cast<float>(GetWindow().getSize().y) });
	 new WallToDestroy(m_layer2, { static_cast<float>(GetWindow().getSize().x + 500),0 }, { 2, static_cast<float>(GetWindow().getSize().y) });
	 new BackGround(m_layer1);
	m_player = new MyPlayer(root, 735);
	new BusinessMan(m_layer2, 700);
	//new Rect(root);
	//new BusinessMan(root, 800.0f);
	//m_player = new MyPlayer(root, 500.0f);
	//new MyGameObject(root);
	
}

void GameScene::MyUpdate(const float& deltatime)
{
	if (m_timeSpawn.GetElapsedTime().AsSeconds() > 3.0f)
	{
		auto businessMan = new BusinessMan(m_layer2, 700);
		businessMan->OnInit();
		m_timeSpawn.Reset();
	}

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
