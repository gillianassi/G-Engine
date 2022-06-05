#include "GEnginePCH.h"
#include "RigidBodyComponent.h"

#include "SceneGraph/GameObject.h"
#include "SceneGraph/Scene.h"
#include "SceneGraph/SceneManager.h"
#include "TransformComponent.h"
#include "Core/Physics.h"
#include "EngineComponents/BaseColliderComponent.h"

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
	m_pTransform = GetGameObject()->GetTransform();
	m_Description.position = m_pTransform->GetPosition();
}

void dae::RigidBodyComponent::FixedUpdate()
{
	auto pos = m_pBody->GetPosition();
	m_pTransform->SetPosition(pos.x, pos.y);
}

void dae::RigidBodyComponent::OnDestroy()
{
	GetGameObject()->GetScene()->GetScenePhysics()->RemoveRigidBody(this);
}

void dae::RigidBodyComponent::SetTransform(glm::vec2 pos, float angle)
{
	if (!m_pBody)
	{
		m_Description.position = pos;
		m_Description.angle = angle;
		return;
	}
	m_pBody->SetTransform(b2Vec2(pos.x, pos.y), angle);
}

void dae::RigidBodyComponent::SetLinearVelocity(glm::vec2 vel)
{
	if (!m_pBody)
	{
		m_Description.linearVelocity = vel;
		return;
	}
	m_pBody->SetLinearVelocity(b2Vec2(vel.x, vel.y));
}

void dae::RigidBodyComponent::SetAngularVelocity(float vel)
{
	if (!m_pBody)
	{
		m_Description.angularVelocity = vel;
		return;
	}
	m_pBody->SetAngularVelocity(vel);
}

void dae::RigidBodyComponent::SetLinearDamiping(float damp)
{
	if (!m_pBody)
	{
		m_Description.linearDamping = damp;
		return;
	}
	m_pBody->SetLinearDamping(damp);
}

void dae::RigidBodyComponent::SetAngularDamiping(float damp)
{
	m_pBody->SetAngularDamping(damp);
}

void dae::RigidBodyComponent::AllowSleep(bool allow)
{
	if (!m_pBody)
	{
		m_Description.allowSleep = allow;
		return;
	}
	m_pBody->SetSleepingAllowed(allow);
}

void dae::RigidBodyComponent::SetAwake(bool isAwake)
{
	if (!m_pBody)
	{
		m_Description.awake = isAwake;
		return;
	}
	m_pBody->SetAwake(isAwake);
}


void dae::RigidBodyComponent::EnableFixedRotation(bool enable)
{
	if (!m_pBody)
	{
		m_Description.fixedRotation = enable;
		return;
	}
	m_pBody->SetFixedRotation(enable);
}

void dae::RigidBodyComponent::SetBullet(bool enable)
{
	if (!m_pBody)
	{
		m_Description.bullet = enable;
		return;
	}
	m_pBody->SetBullet(enable);
}

void dae::RigidBodyComponent::SetRigidBodyType(RigidBodyType type)
{
	if (!m_pBody)
	{
		m_Description.type = type;
		return; 
	}
	m_pBody->SetType(static_cast<b2BodyType>(type));
	m_pBody->SetAwake(true);
}


void dae::RigidBodyComponent::EnableRigidBody(bool enable)
{
	if (!m_pBody)
	{
		m_Description.enabled = enable;
		return;
	}
	m_pBody->SetEnabled(enable);
}


void dae::RigidBodyComponent::SetGravityScale(float scale)
{
	if (!m_pBody)
	{
		m_Description.gravityScale = scale;
		return;
	}
	m_pBody->SetGravityScale(scale);
}

glm::vec2 dae::RigidBodyComponent::GetPosition()
{
	if (!m_pBody)
	{
		return m_Description.position;
	}
	auto pos = m_pBody->GetPosition();
	return glm::vec2(pos.x, pos.y);
}

float dae::RigidBodyComponent::GetAngle()
{
	if (!m_pBody)
	{
		return m_Description.angle;
	}
	return m_pBody->GetAngle();
}

glm::vec2 dae::RigidBodyComponent::GetLinearVelocity()
{
	if (!m_pBody)
	{
		return m_Description.linearVelocity;
	}
	auto vel = m_pBody->GetLinearVelocity();
	return glm::vec2(vel.x, vel.y);
}

float dae::RigidBodyComponent::GetAngularVelocity()
{
	if (!m_pBody)
	{
		return m_Description.angularVelocity;
	}
	return m_pBody->GetAngularVelocity();
}

float dae::RigidBodyComponent::GetLinearDamping()
{
	if (!m_pBody)
	{
		return m_Description.linearDamping;
	}
	return m_pBody->GetLinearDamping();
}

float dae::RigidBodyComponent::GetAngularDamping()
{
	if (!m_pBody)
	{
		return m_Description.angularDamping;
	}
	return m_pBody->GetAngularDamping();
}

bool dae::RigidBodyComponent::IsSleepAllowed()
{
	if (!m_pBody)
	{
		return m_Description.allowSleep;
	}
	return m_pBody->IsSleepingAllowed();
}

bool dae::RigidBodyComponent::IsAwake()
{
	if (!m_pBody)
	{
		return m_Description.awake;
	}
	return m_pBody->IsAwake();
}

bool dae::RigidBodyComponent::HasFixedRotation()
{
	if (!m_pBody)
	{
		return m_Description.fixedRotation;
	}
	return m_pBody->IsFixedRotation();
}

bool dae::RigidBodyComponent::IsBullet()
{
	if (!m_pBody)
	{
		return m_Description.bullet;
	}
	return m_pBody->IsBullet();
}

dae::RigidBodyComponent::RigidBodyType dae::RigidBodyComponent::GetRigidBodyType()
{
	if (!m_pBody)
	{
		return m_Description.type;
	}
	return static_cast<RigidBodyType>(m_pBody->GetType());
}

bool dae::RigidBodyComponent::IsRigidBodyEnabled()
{
	if (!m_pBody)
	{
		return m_Description.enabled;
	}
	return m_pBody->IsEnabled();
}

float dae::RigidBodyComponent::GetGravityScale()
{
	if (!m_pBody)
	{
		return m_Description.gravityScale;
	}
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

void dae::RigidBodyComponent::AttachShapeToRigidBody(BaseColliderComponent* pCollider)
{
	b2FixtureDef fixtureDef;
	fixtureDef.shape = pCollider->m_pColliderShape;
	fixtureDef.friction = pCollider->m_PhysicsMaterial.Friction;
	fixtureDef.restitution = pCollider->m_PhysicsMaterial.Restitution;
	fixtureDef.restitutionThreshold = pCollider->m_PhysicsMaterial.RestitutionThreshold;
	fixtureDef.density = pCollider->m_PhysicsMaterial.Density;
	fixtureDef.isSensor = pCollider->IsTrigger();

	pCollider->m_pFixture = m_pBody->CreateFixture(&fixtureDef);
}

