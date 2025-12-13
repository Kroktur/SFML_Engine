#pragma once
#include "MyGameObject.h"

#include "Core/CollisionSolver.h"
#include "MyPlayer.h"
#include "BulletPlayer.h"

using solver = KT::SolverResult<float, 2, KT::Vector2>;

namespace Rule
{
	 void Collide(MyPlayer& c, BulletPlayer& c2, solver);
	 void Collide(BulletPlayer& c, BulletPlayer& c2, solver);
	 void Collide(MyGameObject& c, MyPlayer& c2, solver);
	 void Collide(MyGameObject& c, BulletPlayer& c2, solver);


}
