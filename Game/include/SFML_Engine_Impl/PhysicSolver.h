#pragma once
#include <map>
#include <vector>

#include "SFMLComposite.h"
#include "Math/OBB.h"
#include "Core/CollisionSolver.h"
#include "Math/AABB.h"


struct SolverInfo
{
    BaseComponent* object = nullptr;
    KT::OBB2DF allBox;
    KT::AABB2DF bigBox;
};

struct SolverResult
{
    BaseComponent* lhsObject =nullptr;
    BaseComponent* rhsObject = nullptr;
    KT::SolverResult<float, 2, KT::Vector2> result;
    int lhsIndex = 0;
    int rhsIndex = 0;
};

class SFMLSolver
{
public:
	static void ADD(BaseComponent* object, const KT::OBB2DF& boxes);
	static void Clear();
	static std::vector<SolverResult> Compute();
private:
    static SolverResult SolveComplex(const SolverInfo& lhs, const SolverInfo& rhs);
	static KT::AABB2DF ComputeAABB(const KT::OBB2DF& obb);
	static std::vector<SolverInfo> m_info;
};
inline std::vector<SolverInfo> SFMLSolver::m_info={};
