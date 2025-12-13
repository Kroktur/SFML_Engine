#include "CollisionRule.h"

void Rule::Collide(BusinessMan& c, Bullet& c2, solver)
{
}

void Rule::Collide(Rect& c, Bullet& c2, solver t)
{
	c2.GetRectangle()->move({ -t.mvt.x,-t.mvt.y });
	c2.Stop();
}

void Rule::Collide(Bullet& c, Bullet& c2, solver)
{

}
