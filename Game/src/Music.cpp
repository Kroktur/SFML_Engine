#include "Music.h"
#include"SFML_Engine_Impl/SFMLLoader.h"
void Music::OnInit()
{
    GetMusic()->openFromFile(MusicLoader::Load("La_folie_des_graines.wav"));
    GetMusic()->setVolume(300.0f);

    GetMusic()->setLooping(true);
    GetMusic()->play();
}

void Music::OnDestroy()
{
}

void Music::Render(float alpha)
{
}

void Music::Input(const std::optional<sf::Event>& event)
{
}

void Music::Update(float deltatime)
{
}