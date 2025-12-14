#pragma once
#include "SFML_Engine_Impl/ISFMLScene.h"
#include "SFML_Engine_Impl/SFMLComposite.h"

//Important for Composite
#include "Core/CollisionSolver.h"
#include "SFML_Engine_Impl/GameObject/BaseIGameObject.h"
#include "SFML_Engine_Impl/GameObject/IGameObject.h"

#include "Core/Dispacher.h"

class BackGround;
class MyPlayer;
using solver = KT::SolverResult<float, 2, KT::Vector2>;


class GameScene : public ISFMLScene, public SFMLRoot<GameScene>
{
public:
	GameScene(const KT::Chrono<float>::Time& refreshTime);

	void Init() override;
	void Update(const float& deltatime) override;
	void ProcessInput() override;
	void Render(const float& alpha) override;
	void Destroy() override;
	MyPlayer* GetPlayer() const;
	BaseComposite* GetLayer1() const;
	BaseComposite* GetLayer2() const;
	void StartGame();
	void AddScore();
	void RemoveScore();
private:
	void MyInit();
	void MyUpdate(const float& deltatime);
	void MyInput(const std::optional<sf::Event>& event) ;
	void MyRender(const float& alpha) ;
	void MyDestroy();
	KT::FNDispatcher<IGameObject, IGameObject, void, KT::typelist<solver>> m_dispatcher;
	std::optional<bool> m_debugMode;
	MyPlayer* m_player;
	BaseComposite* m_layer1;
	BaseComposite* m_layer2;
	KT::Chrono<float> m_timeSpawn;
	std::optional<bool> m_init;
	BackGround* background;
};
