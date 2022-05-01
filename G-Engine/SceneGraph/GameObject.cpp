#include "GEnginePCH.h"
#include "SceneGraph/GameObject.h"

void dae::GameObject::SetParent(GameObject* parent)
{
	if (m_pParent != parent)
	{
		// To do:: check if the new parent is not a child! to avoid loops
		if (m_pParent != nullptr)
		{
			m_pParent->RemoveChild(this);
		}
		m_pParent = parent;
		parent->AddChild(this);
	}
}

dae::GameObject* dae::GameObject::GetParent() const
{
	return m_pParent;
}

size_t dae::GameObject::GetChildCount() const
{
	return m_pChildrenVec.size();
}

dae::GameObject* dae::GameObject::GetChildAt(int index) const
{
	return m_pChildrenVec[index];
}

void dae::GameObject::RemoveChild(int index)
{
	m_pChildrenVec.erase(m_pChildrenVec.begin() + index);
}

void dae::GameObject::RemoveChild(GameObject* go)
{
	auto childItt = std::find_if(m_pChildrenVec.begin(), m_pChildrenVec.end(), [go](GameObject* child)
		{
			return (child == go);
		});
	if (childItt != m_pChildrenVec.end())
	{
		m_pChildrenVec.erase(std::remove(m_pChildrenVec.begin(), m_pChildrenVec.end(), *childItt));
	}
	
}

void dae::GameObject::AddChild(GameObject* go)
{
	// To do:: check if the new child is not a parent in your hirarchy! to avoid loops
	auto childItt = std::find_if(m_pChildrenVec.begin(), m_pChildrenVec.end(), [go](GameObject* child)
		{
			return (child == go);
		});
	if (childItt == m_pChildrenVec.end())
	{
		m_pChildrenVec.push_back(go);
	}
	if (go->GetParent() != this)
	{
		go->SetParent(this);
	}
}
