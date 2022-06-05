#include "GEnginePCH.h"
#include "RigidBodyComponent.h"

#include "SceneGraph/GameObject.h"
#include "SceneGraph/Scene.h"
#include "SceneGraph/SceneManager.h"
#include "TransformComponent.h"
#include "EngineComponents/BoxColliderComponent.h"
#include "Core/Physics.h"

#include <b2_body.h>
#include <b2_polygon_shape.h>
#include <b2_fixture.h>

dae::RigidBodyComponent::RigidBodyComponent(GameObject* pOwner):
	BaseComponent(pOwner)
{
}

void dae::RigidBodyComponent::Initialize()
{
	GetGameObject()->GetScene()->GetScenePhysics()->AddRigidBody(this);
}

void dae::RigidBodyComponent::OnDestroy()
{
	GetGameObject()->GetScene()->GetScenePhysics()->RemoveRigidBody(this);
}

void dae::RigidBodyComponent::SetTransform(glm::vec2 pos, float angle)
{
	m_pBody->SetTransform(b2Vec2(pos.x, pos.y), angle);
}

void dae::RigidBodyComponent::SetLinearVelocity(glm::vec2 vel)
{
	m_pBody->SetLinearVelocity(b2Vec2(vel.x, vel.y));
}

void dae::RigidBodyComponent::SetAngularVelocity(float vel)
{
	m_pBody->SetAngularVelocity(vel);
}

void dae::RigidBodyComponent::SetLinearDamiping(float damp)
{
	m_pBody->SetLinearDamping(damp);
}

void dae::RigidBodyComponent::SetAngularDamiping(float damp)
{
	m_pBody->SetAngularDamping(damp);
}

void dae::RigidBodyComponent::AllowSleep(bool allow)
{
	m_pBody->SetSleepingAllowed(allow);
}

void dae::RigidBodyComponent::SetAwake(bool isAwake)
{
	m_pBody->SetAwake(isAwake);
}


void dae::RigidBodyComponent::EnableFixedRotation(bool enable)
{
	m_pBody->SetFixedRotation(enable);
}

void dae::RigidBodyComponent::SetBullet(bool enable)
{
	m_pBody->SetBullet(enable);
}

void dae::RigidBodyComponent::SetRigidBodyType(RigidBodyType type)
{
	if (!m_pBody) return;
	m_BodyType = type;
	m_pBody->SetType(static_cast<b2BodyType>(type));
	m_pBody->SetAwake(true);
}


void dae::RigidBodyComponent::EnableRigidBody(bool enable)
{
	m_pBody->SetEnabled(enable);
}


void dae::RigidBodyComponent::SetGravityScale(float scale)
{
	m_pBody->SetGravityScale(scale);
}

glm::vec2 dae::RigidBodyComponent::GetPosition()
{
	auto pos = m_pBody->GetPosition();
	return glm::vec2(pos.x, pos.y);
}

float dae::RigidBodyComponent::GetAngle()
{
	return m_pBody->GetAngle();
}

glm::vec2 dae::RigidBodyComponent::GetLinearVelocity()
{
	auto vel = m_pBody->GetLinearVelocity();
	return glm::vec2(vel.x, vel.y);
}

float dae::RigidBodyComponent::GetAngularVelocity()
{
	return m_pBody->GetAngularVelocity();
}

float dae::RigidBodyComponent::GetLinearDamping()
{
	return m_pBody->GetLinearDamping();
}

float dae::RigidBodyComponent::GetAngularDamping()
{
	return m_pBody->GetAngularDamping();
}

bool dae::RigidBodyComponent::IsSleepAllowed()
{
	return m_pBody->IsSleepingAllowed();
}

bool dae::RigidBodyComponent::IsAwake()
{
	return m_pBody->IsAwake();
}

bool dae::RigidBodyComponent::HasFixedRotation()
{
	return m_pBody->IsFixedRotation();
}

bool dae::RigidBodyComponent::IsBullet()
{
	return m_pBody->IsBullet();
}

dae::RigidBodyComponent::RigidBodyType dae::RigidBodyComponent::GetRigidBodyType()
{
	return static_cast<RigidBodyType>(m_pBody->GetType());
}

bool dae::RigidBodyComponent::IsRigidBodyEnabled()
{
	return m_pBody->IsEnabled();
}

float dae::RigidBodyComponent::GetGravityScale()
{
	return m_pBody->GetGravityScale();
}


void dae::RigidBodyComponent::UpdateTransformComponent()
{
	const auto& pos = m_pBody->GetPosition();
	GetGameObject()->GetTransform()->SetPosition(pos.x, pos.y);
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

