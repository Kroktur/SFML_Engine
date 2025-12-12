#pragma once
#include "MyGameObject.h"

#include "Core/CollisionSolver.h"

using solver = KT::SolverResult<float, 2, KT::Vector2>;

namespace Rule
{
	 void Collide(MyClassCircle& c, Enemy& c2, solver);
	 void Collide(Enemy& c2, MyClassRect& c, solver);

}

