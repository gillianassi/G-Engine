#pragma once

class Contact;
namespace dae
{

	class BaseColliderComponent;
	class ContactListener final
	{
	public:
		enum class ContactType
		{
			OnTriggerEnter,
			OnTriggerLeave,
			OnCollisionBegin,
			OnCollisionEnd,
		};

		struct Contact
		{
			BaseColliderComponent* pContactA;
			BaseColliderComponent* pContactB;
			ContactType Type;
		};
		ContactListener();
		~ContactListener() = default;

		ContactListener(const ContactListener& other) = delete;
		ContactListener(ContactListener&& other) = delete;
		ContactListener& operator=(const ContactListener& other) = delete;
		ContactListener& operator=(ContactListener&& other) = delete;

		std::vector<Contact* > GetContacts();
		void ResetContacts();

	private:
		class ContactListenerImpl;
		ContactListenerImpl* m_pImpl;


	};
}
