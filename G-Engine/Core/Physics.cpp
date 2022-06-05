#include "GEnginePCH.h"
#include "Physics.h"

#include "SceneGraph/GameObject.h"
#include "EngineComponents/BaseComponent.h"
#include "EngineComponents/BaseColliderComponent.h"
#include "ContactListener.h"
#include "EngineComponents/TransformComponent.h"
#include "EngineComponents/RigidBodyComponent.h"
#include "Core/Time.h"

#include "b2_world.h"
#include "b2_body.h"
#include "b2_contact.h"
#include "b2_polygon_shape.h"
#include "b2_fixture.h"

dae::Physics::Physics()
{
	// setup the world
	// define the gravity
	b2Vec2 gravity = b2Vec2(0.f, -9.81f);
	m_pWorld = std::make_unique<b2World>(gravity);
	m_pContactListener = std::make_unique<dae::ContactListener>();
}

dae::Physics::~Physics()
{
}

void dae::Physics::Update() const
{
	m_pContactListener->ResetContacts();

	constexpr int32_t velocityIterations = 5;
	constexpr int32_t positionIterations = 5;

	m_pWorld->Step(Time::fixedTimeStep, velocityIterations, positionIterations);

	for (RigidBodyComponent* pComponents : m_pRigidBodies)
	{
		pComponents->Update();
	}

	for (ContactListener::Contact* contact : m_pContactListener->GetContacts())
	{
		GameObject* pTriggerObject = contact->pContactA->GetGameObject();
		GameObject* pOtherObject = contact->pContactB->GetGameObject();
		if (!pTriggerObject->IsMarkedForDestroy() && pOtherObject->IsMarkedForDestroy())
		{
			ContactListener::ContactType action = contact->Type;

			contact->pContactA->m_OnTriggerCallback(pTriggerObject, pOtherObject, action);
			contact->pContactB->m_OnTriggerCallback(pOtherObject, pTriggerObject, action);
		}
	}
}

void dae::Physics::AddRigidBody(RigidBodyComponent* rigidBody)
{
	m_pRigidBodies.push_back(rigidBody);

	const auto pos = rigidBody->GetGameObject()->GetTransform()->GetWorldPosition();

	b2BodyDef bodyDef = b2BodyDef();
	bodyDef.position.Set(
		pos.x,
		pos.y);
	bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(rigidBody);

	const auto body = m_pWorld->CreateBody(&bodyDef);
	rigidBody->SetBody(body);
}

void dae::Physics::RemoveRigidBody(RigidBodyComponent* rigidBody)
{
	m_pWorld->DestroyBody(rigidBody->GetBody());
	m_pRigidBodies.erase(std::remove(m_pRigidBodies.begin(), m_pRigidBodies.end(), rigidBody),m_pRigidBodies.end()); 
}
