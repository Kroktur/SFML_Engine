#pragma once
#include <SFML/Graphics/CircleShape.hpp>

#include "Core/CollisionMapper.h"
#include <SFML/Graphics/RectangleShape.hpp>

static KT::OBB2DF ExtractPoints(sf::RectangleShape* box)
{
	auto localBounds = box->getLocalBounds();
	std::vector<KT::Vector2F> vec{
		KT::Vector2F{localBounds.position.x,localBounds.position.y},
		KT::Vector2F{localBounds.position.x + localBounds.size.x,localBounds.position.y},
		KT::Vector2F{localBounds.position.x + localBounds.size.x,localBounds.position.y + localBounds.size.y},
		KT::Vector2F{localBounds.position.x,localBounds.position.y + localBounds.size.y}
	};
	return KT::OBB2DF(vec);
}

using Mapper2DRectangle = OBB2DFMapper<KT::Vector2F, sf::RectangleShape, ExtractPoints>;

static KT::OBB2DF ExtractPoints(sf::CircleShape* circle)
{
	auto localBounds = circle->getLocalBounds();
	std::vector<KT::Vector2F> vec{
		KT::Vector2F{localBounds.position.x,localBounds.position.y},
		KT::Vector2F{localBounds.position.x + localBounds.size.x,localBounds.position.y},
		KT::Vector2F{localBounds.position.x + localBounds.size.x,localBounds.position.y + localBounds.size.y},
		KT::Vector2F{localBounds.position.x,localBounds.position.y + localBounds.size.y}
	};
	return KT::OBB2DF(vec);
}

using Mapper2DCircle = OBB2DFMapper<float, sf::CircleShape, ExtractPoints>;