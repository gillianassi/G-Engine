#include "GEnginePCH.h"
#include "BoxColliderComponent.h"

#include "SceneGraph/GameObject.h"
#include "EngineComponents/RigidBodyComponent.h"

dae::BoxCollider::BoxCollider(GameObject* pOwner) :
	BaseColliderComponent(pOwner)
{

}

void dae::BoxCollider::Initialize()
{
}

void dae::BoxCollider::Update()
{
}

void dae::BoxCollider::FixedUpdate()
{
}

void dae::BoxCollider::Render()
{
}

void dae::BoxCollider::RenderImGui()
{
}

void dae::BoxCollider::SetColliderTransform(BoxColliderDescr descr)
{
	m_Description = descr;
}

void dae::BoxCollider::SetWidth(float width)
{
	m_Description.Width = width;
}

void dae::BoxCollider::SetHeight(float height)
{
	m_Description.Height = height;
}

void dae::BoxCollider::SetPivot(float pivotX, float pivotY)
{
	m_Description.PivotX = pivotX;
	m_Description.PivotY = pivotY;
}

void dae::BoxCollider::SetRotation(float rotation)
{
	m_Description.Rotation = rotation;
}

void dae::BoxCollider::AttachToRigidBody(GameObject*)
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

