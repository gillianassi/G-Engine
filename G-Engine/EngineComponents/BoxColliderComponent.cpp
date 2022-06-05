#include "GEnginePCH.h"
#include "BoxColliderComponent.h"

#include "SceneGraph/GameObject.h"
#include "EngineComponents/RigidBodyComponent.h"
#include "EngineComponents/TransformComponent.h"
#include "Core/Renderer.h"

#include <b2_fixture.h>
#include <b2_polygon_shape.h>
#include <b2_body.h>


dae::BoxColliderComponent::BoxColliderComponent(GameObject* pOwner) :
	BaseColliderComponent(pOwner),
	m_Color{1.f,0.f,0.f,1.f}
{

}

void dae::BoxColliderComponent::Initialize()
{
	b2PolygonShape* boxShape = new b2PolygonShape();
	boxShape->SetAsBox(m_Description.Width * 0.5f, m_Description.Height * 0.5f);
	m_pColliderShape = boxShape;
	AttachShapeToRigidBody();
}

void dae::BoxColliderComponent::Render()
{
	if (m_RenderCollider)
	{
		const auto& pos = GetGameObject()->GetTransform()->GetWorldPosition();
		Renderer::GetInstance().DrawRect(pos, m_Description.Width, m_Description.Height, m_Color);
	}
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


