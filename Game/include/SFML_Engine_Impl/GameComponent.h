#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include "Core/Component.h"
#include "Math/OBB.h"

template<typename Entity>
class LivingComponent : public KT::Component<Entity>
{
public:
	LivingComponent() : KT::Component<Entity>(), m_isLiving(true) {}
	void EnableDeath()
	{
		m_isLiving = false;
	}
	void StopDeath()
	{
		m_isLiving = true;
	}
	bool IsLiving()
	{
		return m_isLiving;
	}
private:
	bool m_isLiving;
};



template<typename Entity>
class GraphicComponent : public KT::Component<Entity>
{
public:
	using value_type = std::pair<sf::Drawable*,bool>;
	void AddObject(sf::Drawable* object,bool active = true)
	{
		m_objectToRender.push_back(value_type{object,active});
	}
	void EnableRender(size_t index)
	{
		if (index >= m_objectToRender.size())
			throw std::out_of_range("impossible to find item");
		m_objectToRender[index].second = true;
	}
	void DisableRender(size_t index)
	{
		if (index >= m_objectToRender.size())
			throw std::out_of_range("impossible to find item");
		m_objectToRender[index].second = false;
	}
	void Render(sf::RenderWindow* window)
	{
		for (auto& object:m_objectToRender)
		{
			if (object.second)
				window->draw(*object.first);
		}
	}
	bool IsRenderable(size_t index) const 
	{
		if (index >= m_objectToRender.size())
			throw std::out_of_range("impossible to find item");
		return m_objectToRender[index].second;
	}
private:
	std::vector<value_type> m_objectToRender;
};


template<typename Entity>
class CollisionComponent: public KT::Component<Entity>
{
public:

	CollisionComponent() = default;
	static void TranslateOrigin(KT::OBB2DF& obb,sf::Transformable* transform) 
	{
		sf::Vector2f origin = transform->getOrigin();
		KT::Matrix<float, 3> TranslationMatrix{
			1.0f, 0.0f, -origin.x,
			0.0f, 1.0f, -origin.y,
			0.f, 0.f,1.0f
		};
		KT::Vector3F centerHomogeneous{ obb.center.x, obb.center.y, 1.f };
		KT::Vector3F transformedCenter = TranslationMatrix.MatrixProduct(centerHomogeneous);
		obb.center.x = transformedCenter.x;
		obb.center.y = transformedCenter.y;
	}
	static void Scale(KT::OBB2DF& obb, sf::Transformable* transform)
	{
		sf::Vector2f scale = transform->getScale();
		KT::Matrix<float, 3> ScaleMatrix{
			scale.x, 0.0f, 0,
			0.0f,scale.y, 0,
			0.f, 0.f,1.0f
		};
		KT::Vector3F centerHomogeneous{ obb.center.x, obb.center.y, 1.0f };
		KT::Vector3F transformedCenter = ScaleMatrix.MatrixProduct(centerHomogeneous);
	
		obb.center.x = transformedCenter.x;
		obb.center.y = transformedCenter.y;

		obb.halfSize.x = obb.halfSize.x * KT::Math::AbsoluteValue(scale.x);
		obb.halfSize.y = obb.halfSize.y * KT::Math::AbsoluteValue(scale.y);
	}

	static void Rotate(KT::OBB2DF& obb, sf::Transformable* transform)
	{
		float angleRad = transform->getRotation().asRadians();
		float cosA = std::cos(angleRad);
		float sinA = std::sin(angleRad);
		KT::Matrix<float, 3> RotationMatrix{
			cosA, -sinA, 0,
			sinA,cosA, 0,
			0.f, 0.f,1.0f
		};
		KT::Vector3F centerHomogeneous{ obb.center.x, obb.center.y, 1.f };
		KT::Vector3F transformedCenter = RotationMatrix.MatrixProduct(centerHomogeneous);

		obb.center.x = transformedCenter.x;
		obb.center.y = transformedCenter.y;

		for (int i = 0; i < 2; ++i) {
			KT::Vector3F axeHomogenous{ obb.axes[i].x, obb.axes[i].y, 0.f };
			KT::Vector3F transformedAxe = RotationMatrix.MatrixProduct(axeHomogenous);

			obb.axes[i].x = transformedAxe.x;
			obb.axes[i].y = transformedAxe.y;
		}
	}

	static void TranslatePosition(KT::OBB2DF& obb, sf::Transformable* transform)
	{
		sf::Vector2f psotion = transform->getPosition();
		KT::Matrix<float, 3> TranslationMatrix{
			1.0f, 0.0f, psotion.x,
			0.0f, 1.0f, psotion.y,
			0.f, 0.f,1.0f
		};
		KT::Vector3F centerHomogeneous{ obb.center.x, obb.center.y, 1.f };
		KT::Vector3F transformedCenter = TranslationMatrix.MatrixProduct(centerHomogeneous);
		obb.center.x = transformedCenter.x;
		obb.center.y = transformedCenter.y;
	}

	static KT::OBB2DF ToWorldPosition(const KT::OBB2DF& obb,sf::Transformable* transform)
	{
		// copy OBB
		KT::OBB2DF globalOBB = obb;
		TranslateOrigin(globalOBB, transform);
		Scale(globalOBB, transform);
		Rotate(globalOBB, transform);
		TranslatePosition(globalOBB, transform);
		return globalOBB;
	}
	void AddOBB(const KT::OBB2DF& obb = KT::OBB2DF{})
	{
		m_localOBBs.push_back(obb);
	}
	size_t getNumberOfOBB() const
	{
		return m_localOBBs.size();
	}
	void eraseOBB(size_t index)
	{
		if (index >= m_localOBBs.size())
			throw std::out_of_range("out of range");

		m_localOBBs.erase(m_localOBBs.begin() + static_cast<int>(index));
	}
	void SetOBB(size_t index,const KT::OBB2DF& obb)
	{
		if (index >= m_localOBBs.size())
			throw std::out_of_range("out of range");
		m_localOBBs[index] = obb;
	}
	void SetTransform(sf::Transformable* transform)
	{
		m_transform = transform;
	}
	std::vector<KT::OBB2DF> GetLocalOBB() const
	{
		return m_localOBBs;
	}
	std::vector<KT::OBB2DF> GetGlobalOBBs() const
	{
		std::vector<KT::OBB2DF> m_globalOBBs;
		if (!m_transform)
			throw std::runtime_error("you must set a transform");
		for (auto& obb : m_localOBBs)
		{
			m_globalOBBs.push_back(ToWorldPosition(obb, m_transform));
		}
		return m_globalOBBs;
	}
private:
	std::vector<KT::OBB2DF> m_localOBBs;
	sf::Transformable* m_transform;
};