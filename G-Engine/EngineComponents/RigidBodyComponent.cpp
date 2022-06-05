#include "GEnginePCH.h"
#include "RigidBodyComponent.h"

#include "SceneGraph/GameObject.h"
#include "SceneGraph/Scene.h"
#include "SceneGraph/SceneManager.h"
#include "TransformComponent.h"
#include "EngineComponents/BoxColliderComponent.h"

#include <b2_body.h>
#include <b2_polygon_shape.h>
#include <b2_fixture.h>

dae::RigidBodyComponent::RigidBodyComponent(GameObject* pOwner):
	BaseComponent(pOwner),
	m_BodyType{ RigidBodyType::Dynamic},
	m_HasFixedRotation{false},
	m_GravityScale{1.f}

{

}

void dae::RigidBodyComponent::Initialize()
{
	
}

void dae::RigidBodyComponent::OnDestroy()
{
	
}

void dae::RigidBodyComponent::UpdateTransformComponent()
{
	const auto& pos = m_pBody->GetPosition();
	GetGameObject()->GetTransform()->SetPosition(pos.x, pos.y);


}

void dae::RigidBodyComponent::EnableFixedRotation(bool enable)
{
	if (!m_pBody) return;
	m_HasFixedRotation = enable;
	m_pBody->SetFixedRotation(enable);
}

void dae::RigidBodyComponent::SetGravityScale(float scale)
{
	if (!m_pBody) return;
	m_GravityScale = scale;
	m_pBody->SetGravityScale(scale);
}

void dae::RigidBodyComponent::SetRigidBodyType(RigidBodyType type)
{
	if (!m_pBody) return;
	m_BodyType = type;
	m_pBody->SetType(static_cast<b2BodyType>(type));
	m_pBody->SetAwake(true);
}

void dae::RigidBodyComponent::ApplyForce(const glm::fvec2& force, bool wake)
{
	if (!m_pBody) return;
	m_pBody->ApplyForceToCenter(b2Vec2(force.x, force.y), wake);
}

void dae::RigidBodyComponent::ApplyImpulse(const glm::fvec2& impulse, bool wake)
{
	if (!m_pBody) return;
	m_pBody->ApplyLinearImpulseToCenter(b2Vec2(impulse.x, impulse.y), wake);
}

