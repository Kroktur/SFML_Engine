#include "SFML_Engine_Impl/PhysicSolver.h"
#include "Math/OBB.h"
void SFMLSolver::ADD(BaseComponent* object, const KT::OBB2DF& boxes)
{
	auto abb = ComputeAABB(boxes);
	m_info.push_back(SolverInfo{ object,boxes,abb });

}

void SFMLSolver::Clear()
{
	m_info.clear();
}

std::vector<SolverResult> SFMLSolver::Compute()
{
	std::vector<SolverResult> oobbtest;



	for (int i = 0; i < m_info.size(); ++i)
	{
		for (int j = i + 1; j < m_info.size(); ++j)
		{
			if (m_info[i].object->IsInSubTree(m_info[j].object) || m_info[j].object->IsInSubTree(m_info[i].object))
				continue;
			if (KT::CollisionSolver::SolveAABB(m_info[i].bigBox, m_info[j].bigBox).isColliding)
			{
             
				auto betterCollision = SolveComplex(m_info[i], m_info[j]);
				if (betterCollision.result.isColliding)
				{
					oobbtest.push_back(betterCollision);
				}
			}

		}
	}
	return oobbtest;
}

SolverResult SFMLSolver::SolveComplex(const SolverInfo& lhs, const SolverInfo& rhs)
{
	SolverResult result;
	result.lhsObject = lhs.object;
	result.rhsObject = rhs.object;
	auto SatResult = KT::CollisionSolver::SolveOBB<float,2,KT::Vector2>(lhs.allBox, rhs.allBox);
	result.result = SatResult;
	return result;
}

KT::AABB2DF SFMLSolver::ComputeAABB(const KT::OBB2DF& obb)
{
	// Contribution of axis X scaled
	KT::Vector2F ax = obb.axes[0] * obb.halfSize.x;
	KT::Vector2F  ay = obb.axes[1] * obb.halfSize.y;

	// Abs to get extents
	KT::Vector2F  ex = { KT::Math::AbsoluteValue(ax.x), KT::Math::AbsoluteValue(ax.y) };
	KT::Vector2F  ey = { KT::Math::AbsoluteValue(ay.x), KT::Math::AbsoluteValue(ay.y) };

	KT::Vector2F  extent = ex + ey;

	KT::AABB2DF box;
	box.Amin = obb.center - extent;
	box.Amax = obb.center + extent;

	return box;
}
