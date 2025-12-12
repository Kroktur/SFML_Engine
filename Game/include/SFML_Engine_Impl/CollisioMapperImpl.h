#pragma once
#include <SFML/Graphics/CircleShape.hpp>

#include "Core/CollisionMapper.h"
#include <SFML/Graphics/RectangleShape.hpp>
namespace Priv
{
	KT::OBB2DF ExtractPoints(sf::RectangleShape* box);
	KT::OBB2DF ExtractPoints(sf::CircleShape* circle);
}
using Mapper2DRectangle = OBB2DFMapper<KT::Vector2F, sf::RectangleShape, Priv::ExtractPoints>;
using Mapper2DCircle = OBB2DFMapper<float, sf::CircleShape, Priv::ExtractPoints>;