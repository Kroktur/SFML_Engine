#pragma once
//Base For Composite
#include "Core/CompositeCrtp.h"

//Forward so you must include file 
class ISFMLScene;
class IGameObject;



template<typename Derived>
using SFMLRoot = KT::ExcludeRootCRTP<Derived, IGameObject, ISFMLScene>;

using BaseComposite = KT::IComposite<IGameObject, ISFMLScene>;
 
template<typename Derived>
using SFMLComposite = KT::CompositeCRTP<Derived, IGameObject, ISFMLScene>;

using BaseLeaf = KT::ILeaf<IGameObject, ISFMLScene>;

template<typename Derived>
using SFMLLeaf= KT::LeafCRTP<Derived, IGameObject, ISFMLScene>;

using BaseComponent = KT::IComponent<IGameObject, ISFMLScene>;