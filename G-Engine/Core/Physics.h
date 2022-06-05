#pragma once

// box2D implementation created using 
// https://www.youtube.com/watch?v=kEClRFKyGkw as reference

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

		// bodies that can undergo physics
		void AddRigidBody(RigidBodyComponent* rigidBody);
		void RemoveRigidBody(RigidBodyComponent* rigidBody);

	private:
		// will hold all the different rigid bodies and physics shapes for the 
		// physics simulation 
		std::unique_ptr< b2World> m_pWorld;
		std::unique_ptr<ContactListener> m_pContactListener;

		std::vector<RigidBodyComponent*> m_pRigidBodies;
	};
}
