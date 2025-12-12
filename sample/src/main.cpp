#include <iostream>

#include "GameScene.h"
#include "SFML_Engine_Impl/SFMLLoader.h"
#include "SFML_Engine_Impl/SFMLSceneManager.h"


int main(int argc, char** argv)
{
    // Path to SFML_Engine
    std::filesystem::path exePath = argv[0];
    std::filesystem::path projectRoot = exePath.parent_path().parent_path().parent_path().parent_path().parent_path();

    FontLoader::SetGlobalFIlePath((projectRoot / "Ressources" / "Fonts").relative_path() );
    TextureLoader::SetGlobalFIlePath(projectRoot / "Ressources" / "Assets");
    SoundBufferLoader::SetGlobalFIlePath(projectRoot / "Ressources" / "Sounds");
    MusicLoader::SetGlobalFIlePath(projectRoot / "Ressources" / "Musics");
    sf::RenderWindow window{ sf::VideoMode(sf::Vector2u(1920, 1080)),"SFML_Game",sf::State::Windowed};

    SFMLSceneManager manager(window);
    manager.AddScene(0,std::make_unique<GameScene>(KT::Chrono<float>::Time::CreateFromValue<KT::ratio<1>>(1.0f / 60.0f)),true);
    manager.Run(KT::Chrono<float>::Time::CreateFromValue<KT::ratio<1>>(1.0f / 60.0f));
}
