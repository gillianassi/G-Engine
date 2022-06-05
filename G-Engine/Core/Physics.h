#pragma once


class b2World;


namespace dae
{
	class ContactListener;

	class RigidBodyComponent;
	class Physics final
	{
	public:
		Physics();
		~Physics();

		Physics(const Physics& other) = delete;
		Physics(Physics&& other) = delete;
		Physics& operator=(const Physics& other) = delete;
		Physics& operator=(Physics&& other) = delete;

		void Update() const;

		void AddRigidBody(RigidBodyComponent* rigidBody);
		void RemoveRigidBody(RigidBodyComponent* rigidBody);

	private:
		b2World* m_pWorld;
		std::unique_ptr<ContactListener> m_pContactListener;

		std::vector<RigidBodyComponent*> m_pRigidBodies;
	};
}
