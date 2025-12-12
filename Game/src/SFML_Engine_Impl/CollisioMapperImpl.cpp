#include"SFML_Engine_Impl/CollisioMapperImpl.h"

KT::OBB2DF Priv::ExtractPoints(sf::RectangleShape* box)
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

KT::OBB2DF Priv::ExtractPoints(sf::CircleShape* circle)
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
