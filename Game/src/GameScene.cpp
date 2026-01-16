#include "GameScene.h"
#include "SFML_Engine_Impl/PhysicSolver.h"
#include "CollisionRule.h"
#include "ObjectToUse.h"
#include "SFML_Engine_Impl/SFMLLoader.h"
struct player : RectangleComposite
{
	player(BaseComposite* base) : RectangleComposite(base),zqsd(false,false,false,false)
	{
		// DO NOT TOUCH
		GetRectangle()->setSize({ 100,100 });
		GetRectangle()->setPosition({ 100,100 });
		GetRectangle()->setOrigin(GetRectangle()->getPosition() / 2.0f);
		GetRectangle()->setTexture(&TextureLoader::Load("test.jpg", false, {}));
	}
	void Input(const std::optional<sf::Event>& event) override
	{
		// DO NOT TOUCH
		for (int i = 0 ; i < 4 ; ++i)
		{
			zqsd[i] = false;
		}
		

		// Exemple for Z input 
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
			zqsd[0] = true;
		// Code here
	}
	void Update(float deltatime) override
	{
		// DO NOT TOUCH
		static float speed = 100.0f;
		sf::Vector2f dir = {};

		// Exemple for Z
		if (zqsd[0] == true)
			dir.y = -1;

		// CODE HERE







		// DO NOT TOUCH
		for (int i = 0 ; i < 4; ++i)
		{
			zqsd[0] *= speed * deltatime;
		}
		GetRectangle()->move(dir);
	}
	bool zqsd[4];
};

// DO NOT TOUCH
GameScene::GameScene(const KT::Chrono<float>::Time& refreshTime): ISFMLScene(refreshTime)
{}
void GameScene::MyInit()
{
	auto* root = static_cast<SFMLRoot<GameScene>*>(this);
	//First of All Init Dispatcher

	// m_dispatcher.Add< Bullet, Bullet, Rule::Collide, false>();



	player* p = new player(root);
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
