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
	b2PolygonShape* boxShape = new b2PolygonShape();
	boxShape->SetAsBox(m_Description.Width, m_Description.Height);
	m_pColliderShape = boxShape;
	AttachShapeToRigidBody();
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


