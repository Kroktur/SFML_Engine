#include "CollisionRule.h"

void Rule::Collide(BusinessMan& c, Bullet& c2, solver)
{
}


void Rule::Collide(Bullet& c, Bullet& c2, solver)
{

}

void Rule::Collide(MyPlayer& p, WallToBlock& w , solver t)
{
	p.GetRectangle()->move({ t.mvt.x,t.mvt.y });
}

void Rule::Collide(BulletPlayer&, WallToBlock&, solver)
{

}

void Rule::Collide(BulletPlayer& bp, WallToDestroy&, solver)
{
	bp.EnableDeath();
}

void Rule::Collide(BusinessMan& p, WallToBlock&, solver t)
{
	p.GetRectangle()->move({ t.mvt.x,t.mvt.y });

}

void Rule::Collide(Bullet&, WallToBlock&, solver)
{

}

void Rule::Collide(Bullet& b , WallToDestroy&, solver)
{
	b.EnableDeath();
}

void Rule::Collide(MyPlayer& c, BulletPlayer& c2, solver)
{
}

void Rule::Collide(BulletPlayer& c, BulletPlayer& c2, solver)
{
	c.Stop();
	c2.Stop();
}

void Rule::Collide(BulletPlayer& c, BusinessMan& c2, solver s)
{
	c2.MoveBack();
	c.GetRectangle()->move({ -s.mvt.x,-s.mvt.y });
	c.Stop();
}

void Rule::Collide(BusinessMan& c, MyPlayer& c2, solver s)
{
	c2.GetRectangle()->move({ -s.mvt.x,-s.mvt.y });
}

void Rule::Collide(BusinessMan& c, BulletPlayer& c2, solver s)
{
	c.MoveBack();
	c2.GetRectangle()->move({- s.mvt.x,-s.mvt.y });
	c2.Stop();
}

void Rule::Collide(BulletPlayer& c, Bullet& c2, solver s)
{

}

void Rule::Collide(MyPlayer& player, Bullet& bullet, solver s)
{
	bullet.Stop();
}

void Rule::Collide(Bullet& c, BulletPlayer& c2, solver s)
{
}
