#include "GameScene.h"
#include "SFML_Engine_Impl/PhysicSolver.h"


void GameScene::Init()
{
	auto* root = static_cast<SFMLRoot<GameScene>*>(this);
	MyInit();
	// Init 
	root->ExecuteAction([&](IGameObject* go)
		{
			go->OnInit();
		});
}


void GameScene::Update(const float& deltatime)
{
	auto* root = static_cast<SFMLRoot<GameScene>*>(this);
	// execute Starting Action if needed like create new Object PLEASE DO IT HERE WHILE THE GAME RUN
	ExecuteStartingAction();

	//Deleta ALl
	std::vector<BaseComponent*> toDelet;
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

	//UPDATE HERE
	MyUpdate(deltatime);
	//UPDATE STOP

	// Update All Object Here
	SFMLSolver::Clear();
	root->ExecuteAction([&](BaseComponent* component)
		{
			auto* go = component->AsBase();
			go->Update(deltatime);
			go->PrivUpdate(deltatime);
			if (go->HasComponent<GraphicComponent<IGameObject>>())
			{
				if (m_debugMode.has_value())
				{
					if (m_debugMode.value() == true)
						go->GetComponent<GraphicComponent<IGameObject>>()->EnableRender(1);
					else
						go->GetComponent<GraphicComponent<IGameObject>>()->DisableRender(1);
				}
			}
			if (!go->HasComponent<CollisionComponent<IGameObject>>())
				return;
			auto box = go->GetComponent<CollisionComponent<IGameObject>>()->GetGlobalOBBs();
			if (box.empty())
				return;
			SFMLSolver::ADD(component, box[0]);
		});
	auto ToExecute = SFMLSolver::Compute();

	for (auto exe : ToExecute)
	{
		KT::SolverResult<float, 2, KT::Vector2> result = exe.result;
		m_dispatcher(*exe.lhsObject->AsBase(), *exe.rhsObject->AsBase(), result);
	}

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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::B))
		{

			if (!m_debugMode.has_value())
				m_debugMode = true;
			else if (m_debugMode.value() == false)
				m_debugMode = true;
			else
				m_debugMode = false;
		}
	}

	//INPUT HERE
	MyInput(GetWindow().pollEvent());
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
	MyRender(alpha);
	// RENDER STOP

	//Render All Object Here
	auto* root = static_cast<SFMLRoot<GameScene>*>(this);
	root->ExecuteAction([&](IGameObject* go)
		{
			go->Render(alpha);
			go->PrivRender(alpha);
		});
}

void GameScene::Destroy()
{
	MyDestroy();
	// Destroy all the Composite
	auto* root = static_cast<SFMLRoot<GameScene>*>(this);
	root->ExecuteAction([&](IGameObject* go)
		{
			go->OnDestroy();
		});
}

MyPlayer* GameScene::GetPlayer() const
{
	return m_player;
}

BaseComposite* GameScene::GetLayer1() const
{
	return m_layer1;
}

BaseComposite* GameScene::GetLayer2() const
{
	return m_layer2;
}
