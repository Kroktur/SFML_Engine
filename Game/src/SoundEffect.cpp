#include "SoundEffect.h"
#include "SFML_Engine_Impl/SFMLLoader.h"
Sound::Sound(BaseComposite* parent, const sf::SoundBuffer& buffer) : SoundComposite(parent, buffer)
{
	
}

void Sound::OnInit()
{
	GetSound()->setVolume(100.0f);
	GetSound()->play();
}

void Sound::Update(float deltatime)
{

	if (timeleft.GetElapsedTime().AsSeconds() > 1.0f)
		EnableDeath();
}

