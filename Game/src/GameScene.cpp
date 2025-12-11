#include "GameScene.h"

GameScene::GameScene(const KT::Chrono<float>::Time& refreshTime): ISFMLScene(refreshTime)
{}

void GameScene::Init()
{
	// Init All Object 
	auto* root = static_cast<SFMLRoot<GameScene>*>(this);
	// create start Object here

	/*new CollidableRectangleRLGO(root);*/



	// Init 
	root->ExecuteAction([&](IGameObject* go)
	{
		go->OnInit();
	});
}

void GameScene::Update(const float& deltatime)
{
	// execute Starting Action if needed like create new Object PLEASE DO IT HERE WHILE THE GAME RUN
	ExecuteStartingAction();

	//UPDATE HERE

	//UPDATE STOP

	// Update All Object Here
	auto* root = static_cast<SFMLRoot<GameScene>*>(this);
	root->ExecuteAction([&](IGameObject* go)
	{
		go->Update(deltatime);
		if (!go->HasComponent<CollisionComponent<IGameObject>>())
			return;
		//TODO Register Physique
		auto box = go->GetComponent<CollisionComponent<IGameObject>>()->GetGlobalOBB();
	});

	// test collision
	//TODO Execute PhysiqueCollision
	//TODO Execute Dispacher

	std::vector<BaseComponent*> toDelet;
	// delete all here
	root->ExecuteAction([&](BaseComponent* component)
	{
		auto go = component->AsBase();
		if (!go)
			return;
		if (!go->HasComponent<LivingComponent<IGameObject>>())
			return;
		auto life = go->GetComponent<LivingComponent<IGameObject>>();
		if (!life->IsLiving())
			toDelet.push_back(component);
	});
	for (int i = (static_cast<int>(toDelet.size()) - 1); i >= 0; --i)
	{
		toDelet[i]->AsBase()->OnDestroy();
		delete toDelet[i];
	}
	toDelet.clear();

	// execute specific Action if needed
	ExecuteEndingAction();
}

void GameScene::ProcessInput()
{
	while (std::optional<sf::Event> event = GetWindow().pollEvent())
	{
		if (event->is<sf::Event::Closed>())
			GetWindow().close();
		// here for switch scene 
	}

	//INPUT HERE

	//INPUT STOP

	//Input All Object Here
	auto* root = static_cast<SFMLRoot<GameScene>*>(this);
	root->ExecuteAction([&](IGameObject* go)
	{
		go->Input(GetWindow().pollEvent());
	});
}

void GameScene::Render(const float& alpha)
{
	// RENDER HERE

	// RENDER STOP

	//Render All Object Here
	auto* root = static_cast<SFMLRoot<GameScene>*>(this);
	root->ExecuteAction([&](IGameObject* go)
	{
		go->Render(alpha);
	});
}

void GameScene::Destroy()
{
	// Destroy all the Composite
	auto* root = static_cast<SFMLRoot<GameScene>*>(this);
	root->ExecuteAction([&](IGameObject* go)
	{
		go->OnDestroy();
	});
}
