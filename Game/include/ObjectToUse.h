#pragma once
#include "SFML_Engine_Impl/SFMLComposite.h"
#include "SFML_Engine_Impl/GameObject/BaseIGameObject.h"

// YOU will Found Here All the Object you can create child From
// Composite One can have multiple child like player has gun has bullet ....
// leaf One are for the last leaf like a bullet 
// THAT THE COMPLICATED PART

                                                                   //               MUSIC CLASS                       //

// CompositeOne 
class MusicComposite : public MusicLGO, public SFMLComposite<MusicComposite>
{
public:
	MusicComposite(BaseComposite* parent) : SFMLComposite<MusicComposite>(parent), MusicLGO(parent->GetRoot()->AsRoot()){}
};
// how to use

//  class MyClass : public MusicComposite
//  {
//  public:
//	  MyClass(BaseComposite* parent) : MusicComposite(parent){} 
//	  void OnInit() override; // implement this for initiation
//	  void OnDestroy() override; // implement this for destroy
//	  void Render(float alpha) override; // if you don't need to render a specific object automatic 
//	  void Input(const std::optional<sf::Event>& event) override; // if has no input don't need
//	  void Update(float deltatime) override; // if has no logic don't need
//};

// LeafOne 
class MusicLeaf : public MusicLGO, public SFMLLeaf<MusicLeaf>
{
public:
	MusicLeaf(BaseComposite* parent) : SFMLLeaf<MusicLeaf>(parent), MusicLGO(parent->GetRoot()->AsRoot()) {}
};
// how to use

//  class MyClass : public MusicLeaf
//  {
//  public:
//	  MyClass(BaseComposite* parent) : MusicLeaf(parent){} 
//	  void OnInit() override; // implement this for initiation
//	  void OnDestroy() override; // implement this for destroy
//	  void Render(float alpha) override; // if you don't need to render a specific object automatic 
//	  void Input(const std::optional<sf::Event>& event) override; // if has no input don't need
//	  void Update(float deltatime) override; // if has no logic don't need
//};


                                                                //               SOUND CLASS                       //

// CompositeOne 
class SoundComposite : public SoundLGO, public SFMLComposite<SoundComposite>
{
public:
	SoundComposite(BaseComposite* parent, const sf::SoundBuffer& buffer) : SFMLComposite<SoundComposite>(parent), SoundLGO(parent->GetRoot()->AsRoot(), buffer) {}
};
// how to use

//  class MyClass : public SoundComposite
//  {
//  public:
//	  MyClass(BaseComposite* parent, const sf::SoundBuffer& buffer)  : SoundComposite(parent,buffer){} 
//	  void OnInit() override; // implement this for initiation
//	  void OnDestroy() override; // implement this for destroy
//	  void Render(float alpha) override; // if you don't need to render a specific object automatic 
//	  void Input(const std::optional<sf::Event>& event) override; // if has no input don't need
//	  void Update(float deltatime) override; // if has no logic don't need
//};

// LeafOne 
class SoundLeaf : public SoundLGO, public SFMLLeaf<SoundLeaf>
{
public:
	SoundLeaf(BaseComposite* parent, const sf::SoundBuffer& buffer) : SFMLLeaf<SoundLeaf>(parent), SoundLGO(parent->GetRoot()->AsRoot(),buffer) {}
};
// how to use

//  class MyClass : public SoundLeaf
//  {
//  public:
//	  MyClass(BaseComposite* parent, const sf::SoundBuffer& buffer) : SoundLeaf(parent,buffer){} 
//	  void OnInit() override; // implement this for initiation
//	  void OnDestroy() override; // implement this for destroy
//	  void Render(float alpha) override; // if you don't need to render a specific object automatic 
//	  void Input(const std::optional<sf::Event>& event) override; // if has no input don't need
//	  void Update(float deltatime) override; // if has no logic don't need
//};


																//               TEXT CLASS                       //

// CompositeOne 
class TextComposite : public TextRLGO, public SFMLComposite<TextComposite>
{
public:
	TextComposite(BaseComposite* parent, const sf::Font& buffer) : SFMLComposite<TextComposite>(parent), TextRLGO(parent->GetRoot()->AsRoot(), buffer) {}
};
// how to use

//  class MyClass : public TextComposite
//  {
//  public:
//	  MyClass(BaseComposite* parent, const sf::Font& buffer)  : TextComposite(parent,buffer){} 
//	  void OnInit() override; // implement this for initiation
//	  void OnDestroy() override; // implement this for destroy
//	  void Render(float alpha) override; // if you don't need to render a specific object automatic 
//	  void Input(const std::optional<sf::Event>& event) override; // if has no input don't need
//	  void Update(float deltatime) override; // if has no logic don't need
//};

// LeafOne 
class TextLeaf : public TextRLGO, public SFMLLeaf<TextLeaf>
{
public:
	TextLeaf(BaseComposite* parent, const sf::Font& buffer) : SFMLLeaf<TextLeaf>(parent), TextRLGO(parent->GetRoot()->AsRoot(), buffer) {}
};
// how to use

//  class MyClass : public TextLeaf
//  {
//  public:
//	  MyClass(BaseComposite* parent, const sf::Font& buffer) : TextLeaf(parent,buffer){} 
//	  void OnInit() override; // implement this for initiation
//	  void OnDestroy() override; // implement this for destroy
//	  void Render(float alpha) override; // if you don't need to render a specific object automatic 
//	  void Input(const std::optional<sf::Event>& event) override; // if has no input don't need
//	  void Update(float deltatime) override; // if has no logic don't need
//};


																   //               ClASIC RECTANGLE CLASS                       //

// CompositeOne 
class RectangleComposite : public RectangleRLGO, public SFMLComposite<RectangleComposite>
{
public:
	RectangleComposite(BaseComposite* parent) : SFMLComposite<RectangleComposite>(parent), RectangleRLGO(parent->GetRoot()->AsRoot()) {}
};
// how to use

//  class MyClass : public RectangleComposite
//  {
//  public:
//	  MyClass(BaseComposite* parent) : RectangleComposite(parent){} 
//	  void OnInit() override; // implement this for initiation
//	  void OnDestroy() override; // implement this for destroy
//	  void Render(float alpha) override; // if you don't need to render a specific object automatic 
//	  void Input(const std::optional<sf::Event>& event) override; // if has no input don't need
//	  void Update(float deltatime) override; // if has no logic don't need
//};

// LeafOne 
class RectangleLeaf : public RectangleRLGO, public SFMLLeaf<RectangleLeaf>
{
public:
	RectangleLeaf(BaseComposite* parent) : SFMLLeaf<RectangleLeaf>(parent), RectangleRLGO(parent->GetRoot()->AsRoot()) {}
};
// how to use

//  class MyClass : public RectangleLeaf
//  {
//  public:
//	  MyClass(BaseComposite* parent) : RectangleLeaf(parent){} 
//	  void OnInit() override; // implement this for initiation
//	  void OnDestroy() override; // implement this for destroy
//	  void Render(float alpha) override; // if you don't need to render a specific object automatic 
//	  void Input(const std::optional<sf::Event>& event) override; // if has no input don't need
//	  void Update(float deltatime) override; // if has no logic don't need
//};


																   //               COLLIDABLE RECTANGLE CLASS                       //

// CompositeOne 
class CollidableRectangleComposite : public CollidableRectangleRLGO, public SFMLComposite<CollidableRectangleComposite>
{
public:
	CollidableRectangleComposite(BaseComposite* parent) : SFMLComposite<CollidableRectangleComposite>(parent), CollidableRectangleRLGO(parent->GetRoot()->AsRoot()) {}
};
// how to use

//  class MyClass : public CollidableRectangleComposite
//  {
//  public:
//	  MyClass(BaseComposite* parent) : CollidableRectangleComposite(parent){} 
//	  void OnInit() override; // implement this for initiation
//	  void OnDestroy() override; // implement this for destroy
//	  void Render(float alpha) override; // if you don't need to render a specific object automatic 
//	  void Input(const std::optional<sf::Event>& event) override; // if has no input don't need
//	  void Update(float deltatime) override; // if has no logic don't need
//};

// LeafOne 
class CollidableRectangleLeaf : public CollidableRectangleRLGO, public SFMLLeaf<CollidableRectangleLeaf>
{
public:
	CollidableRectangleLeaf(BaseComposite* parent) : SFMLLeaf<CollidableRectangleLeaf>(parent), CollidableRectangleRLGO(parent->GetRoot()->AsRoot()) {}
};
// how to use

//  class MyClass : public CollidableRectangleLeaf
//  {
//  public:
//	  MyClass(BaseComposite* parent) : CollidableRectangleLeaf(parent){} 
//	  void OnInit() override; // implement this for initiation
//	  void OnDestroy() override; // implement this for destroy
//	  void Render(float alpha) override; // if you don't need to render a specific object automatic 
//	  void Input(const std::optional<sf::Event>& event) override; // if has no input don't need
//	  void Update(float deltatime) override; // if has no logic don't need
//};


																   //               ClASIC CIRCLE CLASS                       //

// CompositeOne 
class CircleComposite : public CircleRLGO, public SFMLComposite<CircleComposite>
{
public:
	CircleComposite(BaseComposite* parent) : SFMLComposite<CircleComposite>(parent), CircleRLGO(parent->GetRoot()->AsRoot()) {}
};
// how to use

//  class MyClass : public CircleComposite
//  {
//  public:
//	  MyClass(BaseComposite* parent) : CircleComposite(parent){} 
//	  void OnInit() override; // implement this for initiation
//	  void OnDestroy() override; // implement this for destroy
//	  void Render(float alpha) override; // if you don't need to render a specific object automatic 
//	  void Input(const std::optional<sf::Event>& event) override; // if has no input don't need
//	  void Update(float deltatime) override; // if has no logic don't need
//};

// LeafOne 
class CircleLeaf : public CircleRLGO, public SFMLLeaf<CircleLeaf>
{
public:
	CircleLeaf(BaseComposite* parent) : SFMLLeaf<CircleLeaf>(parent), CircleRLGO(parent->GetRoot()->AsRoot()) {}
};
// how to use

//  class MyClass : public CircleLeaf
//  {
//  public:
//	  MyClass(BaseComposite* parent) : CircleLeaf(parent){} 
//	  void OnInit() override; // implement this for initiation
//	  void OnDestroy() override; // implement this for destroy
//	  void Render(float alpha) override; // if you don't need to render a specific object automatic 
//	  void Input(const std::optional<sf::Event>& event) override; // if has no input don't need
//	  void Update(float deltatime) override; // if has no logic don't need
//};


																   //               COLLIDABLE RECTANGLE CLASS                       //

// CompositeOne 
class CollidableCircleComposite : public CollidableCircleRLGO, public SFMLComposite<CollidableCircleComposite>
{
public:
	CollidableCircleComposite(BaseComposite* parent) : SFMLComposite<CollidableCircleComposite>(parent), CollidableCircleRLGO(parent->GetRoot()->AsRoot()) {}
};
// how to use

//  class MyClass : public CollidableCircleComposite
//  {
//  public:
//	  MyClass(BaseComposite* parent) : CollidableCircleComposite(parent){} 
//	  void OnInit() override; // implement this for initiation
//	  void OnDestroy() override; // implement this for destroy
//	  void Render(float alpha) override; // if you don't need to render a specific object automatic 
//	  void Input(const std::optional<sf::Event>& event) override; // if has no input don't need
//	  void Update(float deltatime) override; // if has no logic don't need
//};

// LeafOne 
class CollidableCircleLeaf : public CollidableCircleRLGO, public SFMLLeaf<CollidableCircleLeaf>
{
public:
	CollidableCircleLeaf(BaseComposite* parent) : SFMLLeaf<CollidableCircleLeaf>(parent), CollidableCircleRLGO(parent->GetRoot()->AsRoot()) {}
};
// how to use

//  class MyClass : public CollidableCircleLeaf
//  {
//  public:
//	  MyClass(BaseComposite* parent) : CollidableCircleLeaf(parent){} 
//	  void OnInit() override; // implement this for initiation
//	  void OnDestroy() override; // implement this for destroy
//	  void Render(float alpha) override; // if you don't need to render a specific object automatic 
//	  void Input(const std::optional<sf::Event>& event) override; // if has no input don't need
//	  void Update(float deltatime) override; // if has no logic don't need
//};