#include "CollisionRule.h"

void Rule::Collide(MyPlayer& c, BulletPlayer& c2, solver)
{
}

void Rule::Collide(BulletPlayer& c, BulletPlayer& c2, solver)
{
}

void Rule::Collide(MyGameObject& c, MyPlayer& c2, solver s)
{
	c2.GetRectangle()->move({ -s.mvt.x,-s.mvt.y });
}

void Rule::Collide(MyGameObject& c, BulletPlayer& c2, solver s)
{
	c.MoveBack();
	c2.GetRectangle()->move({- s.mvt.x,-s.mvt.y });
	c2.Stop();
}
