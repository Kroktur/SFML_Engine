#pragma once
#include "SFML_Engine_Impl/Animation.h"
#include "ObjectToUse.h"

class MyGameObject : public CollidableRectangleComposite
{
public:
	MyGameObject(BaseComposite* parent);
	void OnInit() override;
	void Update(float deltatime) override;
	void OnDestroy() override;

};