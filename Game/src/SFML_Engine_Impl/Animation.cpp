#include "SFML_Engine_Impl/Animation.h"

AnimationManager::AnimationManager(const std::string& textureFileLocation, const KT::Vector2UI& spriteSheetSize,
	const KT::Vector2UI& deadZone, const KT::Vector2UI& frameCount):m_textureFileLocation(textureFileLocation),
	                                                                m_spriteSheetSize(spriteSheetSize)
	                                                                , m_deadZoneSize(deadZone)
	                                                                , m_frameCount(frameCount)
{
	m_spriteFrameSize.x = (m_spriteSheetSize.x / m_frameCount.x) - m_deadZoneSize.x;
	m_spriteFrameSize.y = (m_spriteSheetSize.y / m_frameCount.y) - m_deadZoneSize.y;
}

void AnimationManager::Reset(const std::string& textureFileLocation, const KT::Vector2UI& spriteSheetSize,
	const KT::Vector2UI& deadZone, const KT::Vector2UI& frameCount)
{
	m_textureFileLocation = textureFileLocation;
	m_spriteSheetSize = spriteSheetSize;
	m_deadZoneSize = deadZone;
	m_frameCount = frameCount;
	m_spriteFrameSize.x = (m_spriteSheetSize.x / m_frameCount.x) - m_deadZoneSize.x;
	m_spriteFrameSize.y = (m_spriteSheetSize.y / m_frameCount.y) - m_deadZoneSize.y;
}

sf::IntRect AnimationManager::GetFrame(size_t i) const
{
	if (i < 1 || i > GetTotalFrameCount())
		throw std::out_of_range("out of limits");

	size_t index = i - 1;

	auto row = index / m_frameCount.x;
	auto col = index % m_frameCount.x;

	auto x = col * (m_spriteFrameSize.x + m_deadZoneSize.x);
	auto y = row * (m_spriteFrameSize.y + m_deadZoneSize.y);

	return sf::IntRect(sf::Vector2i(x, y), sf::Vector2i(m_spriteFrameSize.x, m_spriteFrameSize.y));
}

sf::IntRect AnimationManager::GetFrame(size_t x, size_t y) const
{
	size_t i = (y - 1) * m_frameCount.x + (x - 1);
	return GetFrame(i + 1);
}

size_t AnimationManager::GetTotalFrameCount() const
{
	return static_cast<size_t>(m_frameCount.y * m_frameCount.x);
}

std::string AnimationManager::GetTextureFile() const
{
	return m_textureFileLocation;
}

IAnimation::~IAnimation() = default;

IAnimation::IAnimation(AnimationManager* manager, size_t start, size_t end, const KT::Chrono<float>::Time& point):
	m_manager(manager)
	,m_counter(start,end)
	,m_point(point)
{}

void IAnimation::SetMinMax(size_t start, size_t end)
{
	m_counter.SetMinCounter(start);
	m_counter.SetMaxCounter(end);
}

void IAnimation::SetAnimationTime(const KT::Chrono<float>::Time& time)
{
	m_point = time;
}

void IAnimation::SetTexture(sf::Shape* shape) const
{
	shape->setTexture(&TextureLoader::Load(m_manager->GetTextureFile(),false,{}));
}

void IAnimation::SetTexture(sf::Sprite* sprite) const
{
	sprite->setTexture(TextureLoader::Load(m_manager->GetTextureFile(), false, {}));
}

void IAnimation::UpdateShapeFrame(sf::Shape* shape)
{
	shape->setTextureRect(GetRect());
}

void IAnimation::UpdateSpriteFrame(sf::Sprite* sprite)
{
	sprite->setTextureRect(GetRect());
}

LoopAnimation::LoopAnimation(AnimationManager* manager, size_t start, size_t end, const KT::Chrono<float>::Time& point): IAnimation(manager,start,end,point)
{}

sf::IntRect LoopAnimation::GetRect()
{
	if (m_timePassed.GetElapsedTime() > m_point)
	{
		m_timePassed.Reset();
		m_counter.GetAutoCounterMinToMax();
	}
	return m_manager->GetFrame(m_counter.GetCurrentCounter());
}
