#pragma once
#include "SFML_Engine_Impl/Animation.h"
#include "ObjectToUse.h"


class EmptyComposite : public RectangleComposite
{
public:
	EmptyComposite(BaseComposite* base) : RectangleComposite(base) {}
};