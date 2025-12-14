#pragma once
// global Include
#include "Core/ResourcesManager.h"
#include <memory>

// Sfml Include
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Music.hpp>
namespace Priv
{
	 std::unique_ptr <sf::Texture> LoadSfmlTexture(const std::string& filename, bool sRgb, const sf::IntRect& area);

	 std::unique_ptr <sf::Font> LoadSfmlFont(const std::string& filename);

	 std::unique_ptr <sf::SoundBuffer> LoadSfmlSoundBuffer(const std::string& filename);

	 std::unique_ptr <std::string> LoadSfmlMusic(const std::string& filename);
}

//Global_using
using TextureLoader = KT::ResourceManager < sf::Texture, KT::typelist<bool,const sf::IntRect&>, Priv::LoadSfmlTexture >;
using FontLoader = KT::ResourceManager < sf::Font, KT::typelist<>, Priv::LoadSfmlFont >;
using SoundBufferLoader = KT::ResourceManager < sf::SoundBuffer, KT::typelist<>, Priv::LoadSfmlSoundBuffer>;
using MusicLoader = KT::ResourceManager < std::string , KT::typelist<>, Priv::LoadSfmlMusic > ;