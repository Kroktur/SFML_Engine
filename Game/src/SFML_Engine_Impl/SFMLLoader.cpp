#include "SFML_Engine_Impl/SFMLLoader.h"

std::unique_ptr<sf::Texture> Priv::LoadSfmlTexture(const std::string& filename, bool sRgb, const sf::IntRect& area)
{
	std::unique_ptr <sf::Texture>texture = std::make_unique<sf::Texture>();
	if (!texture->loadFromFile(filename, sRgb, area))
		throw std::runtime_error("file not found");
	return std::move(texture);
}

std::unique_ptr<sf::Font> Priv::LoadSfmlFont(const std::string& filename)
{
	std::unique_ptr <sf::Font> font = std::make_unique<sf::Font>();
	if (!font->openFromFile(filename))
		throw std::runtime_error("file not found");
	return std::move(font);
}

std::unique_ptr<sf::SoundBuffer> Priv::LoadSfmlSoundBuffer(const std::string& filename)
{
	std::unique_ptr <sf::SoundBuffer> sBuffer = std::make_unique<sf::SoundBuffer>();
	if (!sBuffer->loadFromFile(filename))
		throw std::runtime_error("file not found");
	return std::move(sBuffer);
}

std::unique_ptr<sf::Music> Priv::LoadSfmlMusic(const std::string& filename)
{
	std::unique_ptr <sf::Music> music = std::make_unique<sf::Music>();
	if (!music->openFromFile(filename))
		throw std::runtime_error("file not found");
	return std::move(music);
}
