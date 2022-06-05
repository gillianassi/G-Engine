#include "GEnginePCH.h"
#include "BaseColliderComponent.h"

#include "RigidBodyComponent.h"
#include "SceneGraph/GameObject.h"
#include <b2_shape.h>

dae::BaseColliderComponent::~BaseColliderComponent()
{
	delete m_pColliderShape;
	m_pColliderShape = nullptr;
}

void dae::BaseColliderComponent::AttachShapeToRigidBody()
{
	RigidBodyComponent* rigidBody = GetGameObject()->GetComponentOfType<RigidBodyComponent>();
	if (rigidBody == nullptr)
	{
		std::cerr << "BoxColliderComponent::Initialize() > Tried To create collider on an object without Rigid Body" << std::endl;
	}
	if (m_pColliderShape == nullptr)
	{
		std::cerr << "BoxColliderComponent::Initialize() > No shape has been assigned to m_pColliderShape" << std::endl;
	}
	rigidBody->AttachShapeToRigidBody(this);
}

