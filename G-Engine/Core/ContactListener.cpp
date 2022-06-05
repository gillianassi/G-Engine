#include "GEnginePCH.h"
#include "ContactListener.h"

#include <b2_world.h>
#include <b2_contact.h>
#include "EngineComponents/BaseColliderComponent.h"

namespace dae
{
	class ContactListener::ContactListenerImpl final : public b2ContactListener
	{
	public:

		ContactListenerImpl() = default;
		~ContactListenerImpl()
		{
			ResetContacts();
		}

		void BeginContact(b2Contact* contact) override
		{
			// Get Colliders
			BaseColliderComponent* pContactA = reinterpret_cast<BaseColliderComponent*>(contact->GetFixtureA()->GetUserData().pointer);
			BaseColliderComponent* pContactB = reinterpret_cast<BaseColliderComponent*>(contact->GetFixtureB()->GetUserData().pointer);
	
			if ((pContactA && pContactB) && 
				(!pContactA->IsMarkedForDestroy() && pContactB->IsMarkedForDestroy()))
			{
				Contact* pNewContact = new Contact();
				pNewContact->pContactA = pContactA;
				pNewContact->pContactB = pContactB;
				pNewContact->Type = ContactType::OnCollisionBegin;


				if (pContactA->IsTrigger() || pContactB->IsTrigger())
				{
					pNewContact->Type = ContactType::OnTriggerEnter;
				}

				m_Contacts.emplace_back(pNewContact);
			}


		}

		void EndContact(b2Contact* contact) override
		{
			// Get Colliders
			BaseColliderComponent* pContactA = reinterpret_cast<BaseColliderComponent*>(contact->GetFixtureA()->GetUserData().pointer);
			BaseColliderComponent* pContactB = reinterpret_cast<BaseColliderComponent*>(contact->GetFixtureB()->GetUserData().pointer);
			
			if ((pContactA && pContactB) &&
				(!pContactA->IsMarkedForDestroy() && pContactB->IsMarkedForDestroy()))
			{
				Contact* pNewContact = new Contact();
				pNewContact->pContactA = pContactA;
				pNewContact->pContactB = pContactB;

				pNewContact->Type = ContactType::OnCollisionEnd;
				if (pContactA->IsTrigger() || pContactB->IsTrigger())
				{
					pNewContact->Type = ContactType::OnTriggerLeave;
				}

				m_Contacts.emplace_back(pNewContact);
			}
		}

		std::vector<Contact*> GetContacts() { return m_Contacts; }
		void ResetContacts()
		{
			for (size_t i = 0; i < m_Contacts.size(); i++)
			{
				delete m_Contacts[i];
				m_Contacts[i] = nullptr;
			}
			m_Contacts.clear();
		}

	private:
		std::vector<Contact*> m_Contacts;
	};
}


dae::ContactListener::ContactListener():
	m_pImpl{ new ContactListenerImpl()}
{}

std::vector<dae::ContactListener::Contact*> dae::ContactListener::GetContacts()
{
	return m_pImpl->GetContacts();
}

void dae::ContactListener::ResetContacts()
{
	m_pImpl->ResetContacts();
}
