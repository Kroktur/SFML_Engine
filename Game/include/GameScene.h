#pragma once
#include "SFML_Engine_Impl/ISFMLScene.h"
#include "SFML_Engine_Impl/SFMLComposite.h"

//Important for Composite
#include "SFML_Engine_Impl/GameObject/BaseIGameObject.h"
#include "SFML_Engine_Impl/GameObject/IGameObject.h"


class GameScene : public ISFMLScene, public SFMLRoot<GameScene>
{
public:
	GameScene(const KT::Chrono<float>::Time& refreshTime);

	void Init() override;

	void Update(const float& deltatime) override;

	void ProcessInput() override;

	void Render(const float& alpha) override;

	void Destroy() override;

private:
};
