#pragma once
#include "ObjectToUse.h"
class Music : public MusicComposite
{
public:
    Music(BaseComposite* parent) : MusicComposite(parent) {}
    void OnInit() override; // implement this for initiation
    void OnDestroy() override; // implement this for destroy
    void Render(float alpha) override; // if you don't need to render a specific object automatic 
    void Input(const std::optional<sf::Event>& event) override; // if has no input don't need
    void Update(float deltatime) override; // if has no logic don't need
};