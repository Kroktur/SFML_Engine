#pragma once 
#include "SFML_Engine_Impl/Animation.h"
#include "ObjectToUse.h"

class StartText;

class TextBackGround : public RectangleComposite
{
	public:
	TextBackGround(BaseComposite* parent) : RectangleComposite(parent),m_startText(nullptr) {}
	void OnInit() override;
    void Update(float deltatime) override;
	StartText* m_startText;
};


class StartText : public TextComposite
{
	public:
	StartText(BaseComposite* parent, const sf::Font& font, const KT::Vector2F& position) : TextComposite(parent, font),m_position(position),m_index(0) {}
    void OnInit() override;
    void Input(const std::optional<sf::Event>& event) override; // if has no input don't need
    void Update(float deltatime) override; // if has no logic don't need
    bool GetEnterPressed() const;
private:
    std::string m_fullText;
    int m_index;
    KT::Vector2F m_position;
    bool is_EnterPressed = false;
    KT::Chrono<float> m_startTimer;

};
