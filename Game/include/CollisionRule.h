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

    void Collide(Bullet& c, Bullet& c2, solver);
    void Collide(BusinessMan& c, MyPlayer& c2, solver s);

    void Collide(BusinessMan& c, BulletPlayer& c2, solver s);

    void Collide(MyPlayer& player, Bullet& bullet, solver s);
    void Collide(Bullet& c, BulletPlayer& c2, solver s);

    void Collide(MyPlayer&, WallToBlock&, solver);
    void Collide(BulletPlayer&, WallToBlock&, solver);
    void Collide(BulletPlayer&, WallToDestroy&, solver);
    void Collide(BusinessMan&, WallToBlock&, solver);
    void Collide(Bullet&, WallToBlock&, solver);
    void Collide(Bullet&, WallToDestroy&, solver);


    void Collide(MyPlayer& c, BulletPlayer& c2, solver);
    void Collide(BulletPlayer& c, BulletPlayer& c2, solver);
    void Collide(BusinessMan& c, Bullet& c2, solver);


    // player balle buisnes 
    void Collide(BulletPlayer& c, BusinessMan& c2, solver s);
    // player buisnes

    // balle player buisness

    //balle player balle buisness
    void Collide(BulletPlayer& c, Bullet& c2, solver s);


}