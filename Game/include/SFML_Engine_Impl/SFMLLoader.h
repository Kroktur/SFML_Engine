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
	static std::unique_ptr <sf::Texture> LoadSfmlTexture(const std::string& filename, bool sRgb, const sf::IntRect& area)
	{
		std::unique_ptr <sf::Texture>texture = std::make_unique<sf::Texture>();
		if (!texture->loadFromFile(filename, sRgb, area))
			throw std::runtime_error("file not found");
		return std::move(texture);
	}
	static std::unique_ptr <sf::Font> LoadSfmlFont(const std::string& filename)
	{
		std::unique_ptr <sf::Font> font = std::make_unique<sf::Font>();
		if (!font->openFromFile(filename))
			throw std::runtime_error("file not found");
		return std::move(font);
	}
	static std::unique_ptr <sf::SoundBuffer> LoadSfmlSoundBuffer(const std::string& filename)
	{
		std::unique_ptr <sf::SoundBuffer> sBuffer = std::make_unique<sf::SoundBuffer>();
		if (!sBuffer->loadFromFile(filename))
			throw std::runtime_error("file not found");
		return std::move(sBuffer);
	}

	static std::unique_ptr <sf::Music> LoadSfmlMusic(const std::string& filename)
	{
		std::unique_ptr <sf::Music> music = std::make_unique<sf::Music>();
		if (!music->openFromFile(filename))
			throw std::runtime_error("file not found");
		return std::move(music);
	}
}

//Global_using
using TextureLoader = KT::ResourceManager < sf::Texture, KT::typelist<bool,const sf::IntRect&>, Priv::LoadSfmlTexture >;
using FontLoader = KT::ResourceManager < sf::Font, KT::typelist<>, Priv::LoadSfmlFont >;
using SoundBufferLoader = KT::ResourceManager < sf::SoundBuffer, KT::typelist<>, Priv::LoadSfmlSoundBuffer>;
using MusicLoader = KT::ResourceManager < sf::Music, KT::typelist<>, Priv::LoadSfmlMusic>;