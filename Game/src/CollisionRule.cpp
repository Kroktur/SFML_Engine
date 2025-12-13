#include "CollisionRule.h"

void Rule::Collide(MyClassCircle& c, Enemy& c2, solver)
{
	c.GetCirle()->setFillColor(sf::Color::Blue);

}

void Rule::Collide(Enemy& c2, MyClassRect& c, solver)
{
	c2.MoveRight();
	
}


