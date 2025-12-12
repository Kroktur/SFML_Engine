#pragma once
#include <SFML/Graphics/Shape.hpp>

#include <SFML/Graphics/Sprite.hpp>

#include "Tools/Counter.h"
#include "Math/Vector2.h"
#include "SFML_Engine_Impl/SFMLLoader.h"
#include "Tools/Chrono.h"

class AnimationManager
{
public:
	AnimationManager(const std::string& textureFileLocation,const KT::Vector2UI& spriteSheetSize,const KT::Vector2UI& deadZone,const KT::Vector2UI& frameCount);
	void Reset(const std::string& textureFileLocation, const KT::Vector2UI& spriteSheetSize, const KT::Vector2UI& deadZone, const KT::Vector2UI& frameCount);
	sf::IntRect GetFrame(size_t i) const;
	sf::IntRect GetFrame(size_t x, size_t y) const;
	size_t GetTotalFrameCount() const;
	std::string GetTextureFile() const;
private:
	std::string m_textureFileLocation;
	KT::Vector2UI m_spriteSheetSize;
	KT::Vector2UI m_spriteFrameSize;
	KT::Vector2UI m_deadZoneSize;
	KT::Vector2UI m_frameCount;
};

class IAnimation
{
public:
	virtual ~IAnimation();
	IAnimation(AnimationManager* manager,size_t start, size_t end,const KT::Chrono<float>::Time& point);
	void SetMinMax(size_t start, size_t end);
	void SetAnimationTime(const KT::Chrono<float>::Time& time);
	void SetTexture(sf::Shape* shape) const;
	void SetTexture(sf::Sprite* sprite) const;
	void UpdateShapeFrame(sf::Shape* shape);
	void UpdateSpriteFrame(sf::Sprite* sprite);
protected:
	virtual sf::IntRect GetRect() = 0;
	AnimationManager* m_manager;
	KT::Chrono<float>::Time m_point;
	KT::Chrono<float> m_timePassed;
	KT::Counter<size_t> m_counter;
};

class LoopAnimation : public IAnimation
{
public:
	LoopAnimation(AnimationManager* manager, size_t start, size_t end, const KT::Chrono<float>::Time& point);
private:
	sf::IntRect GetRect() override;
};
