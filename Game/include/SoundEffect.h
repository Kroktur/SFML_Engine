#pragma once

#include "ObjectToUse.h"
#include "Tools/Chrono.h"

class Sound : public SoundComposite
{
public:
	Sound(BaseComposite* parent, const sf::SoundBuffer& buffer);
	void OnInit() override;
	void Update(float deltatime) override;
private:
	KT::Chrono<float> timeleft;
};
