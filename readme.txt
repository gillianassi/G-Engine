Gillian Assi
-------------

Class: 2DAE06E

Git Repository: 
https://github.com/gillianassi/G-Engine

Design desisions:

- Box2D
	- Box2D library is used for physics, collision and triggers.
	- Box2D implememntations are made using simple wrapper classes
	- Box2D implementations in the engine:
		- RigidBody
		- BoxCollider
		- Triggers (using a callback function)

- Scene graph
	- Creating a GameObject is only possible via the scene or a gameobject using CreateChild
	- Objects can easilly be reparented
	- Objects and components can be destroyed

- Keyboard input
	- easy to use for both controller and keyboard.
	- Command can be linked to both a controller button and a keyboard key