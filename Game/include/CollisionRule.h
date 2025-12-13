#pragma once
#include "MyGameObject.h"
#include "BusinessMan.h"
#include "BulletBusiness.h"

#include "Core/CollisionSolver.h"
#include "MyPlayer.h"
#include "BulletPlayer.h"
#include "Wall.h"

using solver = KT::SolverResult<float, 2, KT::Vector2>;

namespace Rule
{
	 void Collide(MyPlayer& c, BulletPlayer& c2, solver);
	 void Collide(BulletPlayer& c, BulletPlayer& c2, solver);
	 void Collide(MyGameObject& c, MyPlayer& c2, solver);
	 void Collide(MyGameObject& c, BulletPlayer& c2, solver);


	 void Collide(BusinessMan& c, Bullet& c2, solver);
	 void Collide(Rect& c, Bullet& c2, solver);
	 void Collide(Bullet& c, Bullet& c2, solver);



	 void Collide(MyPlayer&, WallToBlock&, solver);
	 void Collide(BulletPlayer&, WallToBlock&, solver);
	 void Collide(BulletPlayer&, WallToDestroy&, solver);
}
