#include "StartGame.h"

#include "GameScene.h"

void TextBackGround::OnInit()
{
	RectangleComposite::OnInit();
    m_startText = new StartText(this, FontLoader::Load("font.ttf"), { 570,150 });
    m_startText->OnInit();
    GetRectangle()->setSize({ 890,620 });
    GetRectangle()->setFillColor(sf::Color::White);
    GetRectangle()->setPosition({ 500,100 });
    GetRectangle()->setTexture(&TextureLoader::Load("Background.png", {}, {}));
}

void TextBackGround::Update(float deltatime)
{
	RectangleComposite::Update(deltatime);
	if (m_startText->GetEnterPressed())
	{
		EnableDeath();
		static_cast<GameScene*>(GetScene())->StartGame();
	}
}

void StartText::OnInit()
{
	TextComposite::OnInit();
	GetText()->setPosition({ m_position.x, m_position.y });
	GetText()->setCharacterSize(26);
	GetText()->setFillColor(sf::Color{ 87,105,47 });
	GetText()->setString("");
	m_fullText = ("Bienvenue dans Green It!\n"
		"Objectif:\n"
		"Convertissez l état d esprit des Businessmans pour les rendre pro verts.\n"
		"Aidez les en lançant des graines tout en évitant leurs attaques \net leurs plans malveillants pour la ville.\n"
		"Votre mission est de garder la ville propre et verte.\n"
		"Si vous subissez des coups, la ville deviendra plus polluée,\n"
		"alors ne laissez pas les Businessmans prendre le contrôle!\n"
		"Chaque Businessman que vous convertissez rend la ville plus propre.\n"
		"Gagnez en rendant votre ville 100 % écologique et verte.\n\n"
		"Contrôles:\n"
		"- Utilisez les touches Q et D pour vous déplacer à gauche et à droite.\n"
		"- Appuyez sur la Barre d espace pour sauter.\n"
		"- Appuyez sur 'E' pour attaquer.\n"
		"- Appuyez sur 'A' pour utiliser votre bouclier.\n\n"
		"Bonne chance, et sauvez votre ville!                       "
		"ENTRER  pour continuer");
}

void StartText::Input(const std::optional<sf::Event>& event)
{
	TextComposite::Input(event);
	if (m_startTimer.GetElapsedTime().AsSeconds() >= 13)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
		{
			is_EnterPressed = true;
		}
	}
}

void StartText::Update(float deltatime)
{
	TextComposite::Update(deltatime);
	std::string currentText = "";
	std::copy(m_fullText.begin(), m_fullText.begin() + m_index, std::back_inserter(currentText));
	m_index = std::min(m_index + 1, static_cast<int>(m_fullText.size()));
	GetText()->setString(currentText);
}

bool StartText::GetEnterPressed() const
{
	return is_EnterPressed;
}
