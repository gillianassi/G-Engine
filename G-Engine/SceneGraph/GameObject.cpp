#include "GEnginePCH.h"
#include "GameObject.h"

#include "Scene.h"
#include "EngineComponents/TransformComponent.h"

dae::GameObject::GameObject(const std::string& name, GameObject* pParent, Scene* pScene, bool propagateTags):
	m_Name{name},
	m_pParent{pParent},
	m_pScene{pScene},
	m_pTransform{AddComponent<TransformComponent>()}
{
	if (propagateTags && m_pParent != nullptr)
	{
		// if asked, add the parent tags
		for (int tag : m_pParent->GetTags())
		{
			AddTag(tag);
		}
	}
}

dae::GameObject::~GameObject()
{
	for (size_t i = 0; i < m_pChildrenVec.size(); i++)
	{
		delete m_pChildrenVec[i];
		m_pChildrenVec[i] = nullptr;
	}
	m_pChildrenVec.clear();
}

bool dae::GameObject::HasTag(int tag) const
{
	return std::find(m_Tags.begin(), m_Tags.end(), tag) != m_Tags.end();
}

void dae::GameObject::AddTag(int tag, bool propagateToChildren)
{
	// check if it is already in the tag vector
	if (std::find(m_Tags.begin(), m_Tags.end(), tag) != m_Tags.end())
	{
		m_Tags.push_back(tag);
	}
	// propagate if asked
	if (propagateToChildren)
	{
		for (const auto& pChild : m_pChildrenVec)
		{
			pChild->AddTag(tag);
		}
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

void dae::GameObject::RemoveChildFromChildVec(int index)
{
	m_pChildrenVec.erase(m_pChildrenVec.begin() + index);
}

void dae::GameObject::RemoveChildFromChildVec(GameObject* go)
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



dae::GameObject* dae::GameObject::AddChild(std::string name, bool inheritTags)
{
	GameObject* pChild = new GameObject(name, this, m_pScene, inheritTags); // Can't use make_shared because of private constructor
	m_pChildrenVec.push_back(pChild);

	return pChild;

}

void dae::GameObject::SetParent(GameObject* parent, bool hasCheckedHierarchy)
{
	if (!hasCheckedHierarchy)
	{
		if (parent == this)
		{
			// log
			std::cout << "GameObject::SetParent > You cannot parent yourself" << std::endl;
			return;
		}
		if (parent == m_pParent)
		{
			std::cout << "GameObject::SetParent > this gameObject is already a child of the given parent" << std::endl;
			return;
		}

		// Check in case this gameobject already has the "new parent" as a child
		if (HasChildInHierarchy(parent))
		{
			// Log
			std::cout << "You GameObject::SetParent > The given 'parent' gameObject is already a child of this gameObject " << std::endl;
			return;
		}

		if (m_pParent != nullptr)
		{
			m_pParent->RemoveChildFromChildVec(this);
		}
		else // no parent means it is a direct child of the scene
		{
			m_pScene->RemoveChildFromChildVec(this);
		}
		// simply add the child with no extra checks
		parent->AddChild(this, true);
	}

	m_pParent = parent;
}

void dae::GameObject::AddChild(GameObject* pGo, bool hasCheckedHierarchy)
{

	if (!hasCheckedHierarchy)
	{
		if (pGo == this)
		{
			std::cout << "GameObject::AddChild > You cannot child yourself" << std::endl;
		}

		GameObject* previousChildParent = pGo->GetParent();

		if (previousChildParent == m_pParent)
		{
			std::cout << "GameObject::AddChild > the given gameObject is already a child of this parent" << std::endl;
			return;
		}

		// this gameobject is already a child within this hierarchy
		// You cannot Add a parent as a child
		if (pGo->HasChildInHierarchy(this))
		{
			// Log
			std::cout << "You GameObject::AddChild > You cannot add a parent as a Child. Detach first." << std::endl;
			return;
		}
		// remove child from old parent
		if (previousChildParent)
		{
			// be sure that its child will be removed
			previousChildParent->RemoveChildFromChildVec(pGo);
		}
		else // no parent means it is a direct child of the scene
		{
			m_pScene->RemoveChildFromChildVec(pGo);
		}
		// simply set the parent with no extra checks
		pGo->SetParent(this, true);
	}

	m_pChildrenVec.push_back(pGo);


}

bool dae::GameObject::HasChildInHierarchy(GameObject* pGo)
{
	// ask every child if they have this gameObject as a child

	// Does this gameobject have this child?
	auto childItt = std::find_if(m_pChildrenVec.begin(), m_pChildrenVec.end(), [pGo](GameObject* child)
		{
			return (child == pGo);
		});
	// child is not one of your children
	if (childItt != m_pChildrenVec.end())
	{
		// this one has a child
		return true;

	}
	// Does any of the children of this gameobject have this child?
	for (GameObject* pChild : m_pChildrenVec)
	{
		if (pChild->HasChildInHierarchy(pGo))
		{
			return true;
		}
	}
	// gameObject has not been found in hierarchy
	return false;
}


void dae::GameObject::Initialize() const
{
	// don't check enabled, you always want to initialize

	// update components
	for (auto& upComponent : m_upComponentVec) upComponent->Initialize();

	// update children -> make sure their components get initialized
	for (GameObject* pChild : m_pChildrenVec) pChild->Initialize();
}

void dae::GameObject::Update() const
{
	if (!m_IsEnabled)
		return;

	// update components
	for (auto& upComponent : m_upComponentVec) upComponent->Update();

	// update children
	for (GameObject* pChild : m_pChildrenVec) pChild->Update();
}

void dae::GameObject::FixedUpdate() const
{
	if (!m_IsEnabled)
		return;


	// update components
	for (auto& upComponent : m_upComponentVec) upComponent->FixedUpdate();

	// update children
	for (GameObject* pChild : m_pChildrenVec) pChild->FixedUpdate();
}

void dae::GameObject::Render() const
{
	if (!m_IsEnabled)
		return;


	// update components
	for (auto& upComponent : m_upComponentVec) upComponent->Render();

	// update children
	for (GameObject* pChild : m_pChildrenVec) pChild->Render();
}

void dae::GameObject::RenderImGui() const
{
	if (!m_IsEnabled)
		return;


	// update components
	for (auto& upComponent : m_upComponentVec) upComponent->RenderImGui();

	// update children
	for (GameObject* pChild : m_pChildrenVec) pChild->RenderImGui();
}

void dae::GameObject::OnEnable() const
{
	for (auto& upComponent : m_upComponentVec) upComponent->OnEnable();
}

void dae::GameObject::OnDIsable() const
{
	for (auto& upComponent : m_upComponentVec) upComponent->OnDIsable();
}

void dae::GameObject::OnDestroy() const
{
	for (auto& upComponent : m_upComponentVec) upComponent->OnDestroy();

	for (GameObject* pChild : m_pChildrenVec) pChild->OnDestroy();
}

void dae::GameObject::UpdateGameObjectState()
{
	if (m_MarkedForEnable != m_IsEnabled)
	{
		m_IsEnabled = m_MarkedForEnable;
	}
	(m_IsEnabled) ? OnEnable() : OnDIsable();


	for (GameObject* pChild : m_pChildrenVec)
	{
		if (pChild->IsMarkedForDestroy())
		{
			pChild->OnDestroy();
			delete pChild;
			pChild = nullptr;
		}
	}
	// move all elements you want to erase to the end
	const auto beginEraseGameObjectItt = std::remove_if(m_pChildrenVec.begin(), m_pChildrenVec.end(),
		[](GameObject* pObject) { return pObject->IsMarkedForDestroy(); });
	// erase all those elements
	m_pChildrenVec.erase(beginEraseGameObjectItt, m_pChildrenVec.end());
	

	for (const auto& pComponent : m_upComponentVec)
	{
		if (pComponent->IsMarkedForDestroy())
		{
			pComponent->OnDestroy();
		}
	}

	// move all elements you want to erase to the end
	const auto beginEraseComponentItt = std::remove_if(m_upComponentVec.begin(), m_upComponentVec.end(),
		[](const auto& pComponent) { return pComponent->IsMarkedForDestroy(); });
	// erase all those elements
	m_upComponentVec.erase(beginEraseComponentItt, m_upComponentVec.end());




	for (const auto& pComponent : m_upComponentVec)
	{
		pComponent->UpdateComponentState();
	}
	for (GameObject* pChild : m_pChildrenVec)
	{
		pChild->UpdateGameObjectState();
	}

}

