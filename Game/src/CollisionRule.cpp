#include "CollisionRule.h"

void Rule::Collide(RandomSquare& c, Player& c2, solver)
{
	c.GetRectangle()->setFillColor(sf::Color::Red);
}

void Rule::Collide(Player& c2, MyCircle& c, solver)
{
	c.GetCirle()->setFillColor(sf::Color::Blue);
}
