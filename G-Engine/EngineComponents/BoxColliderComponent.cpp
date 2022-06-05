#include "GEnginePCH.h"
#include "BoxColliderComponent.h"

#include "SceneGraph/GameObject.h"
#include "EngineComponents/RigidBodyComponent.h"

#include <b2_fixture.h>
#include <b2_polygon_shape.h>
#include <b2_body.h>


dae::BoxColliderComponent::BoxColliderComponent(GameObject* pOwner) :
	BaseColliderComponent(pOwner)
{

}

void dae::BoxColliderComponent::Initialize()
{
	b2PolygonShape boxShape;
	boxShape.SetAsBox(0.f, 0.f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = m_PhysicsMaterial.Density;
	fixtureDef.friction = m_PhysicsMaterial.Friction;

}

void dae::BoxColliderComponent::Update()
{
}

void dae::BoxColliderComponent::FixedUpdate()
{
}

void dae::BoxColliderComponent::Render()
{
}

void dae::BoxColliderComponent::RenderImGui()
{
}

void dae::BoxColliderComponent::SetColliderTransform(BoxColliderDescr descr)
{
	m_Description = descr;
}

void dae::BoxColliderComponent::SetWidth(float width)
{
	m_Description.Width = width;
}

void dae::BoxColliderComponent::SetHeight(float height)
{
	m_Description.Height = height;
}

void dae::BoxColliderComponent::SetPivot(float pivotX, float pivotY)
{
	m_Description.PivotX = pivotX;
	m_Description.PivotY = pivotY;
}

void dae::BoxColliderComponent::SetRotation(float rotation)
{
	m_Description.Rotation = rotation;
}

void dae::BoxColliderComponent::AttachToRigidBody(GameObject*)
{
	//const auto rigidBody = pGameObject->GetComponentOfType<RigidBodyComponent>();

	//if (rigidBody == nullptr)
	//{
	//	// check if the parent has a rigid body to attach to
	//	GameObject* pParent = pGameObject->GetParent();
	//	if (pParent != nullptr)
	//	{
	//		AttachToRigidBody(pParent);
	//	}
	//	else
	//	{
	//		std::cout << "BoxCollider:AttachToRigidBody() No Rigidbody found!" << std::endl;
	//	}
	//}
	//else
	//{
	//	rigidBody->
	//}

}

