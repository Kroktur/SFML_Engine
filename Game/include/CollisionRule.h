#pragma once
#include "MyGameObject.h"
#include "BusinessMan.h"
#include "BulletBusiness.h"

#include "Core/CollisionSolver.h"

using solver = KT::SolverResult<float, 2, KT::Vector2>;

namespace Rule
{
	 void Collide(BusinessMan& c, Bullet& c2, solver);
	 void Collide(Rect& c, Bullet& c2, solver);
	 void Collide(Bullet& c, Bullet& c2, solver);
}
