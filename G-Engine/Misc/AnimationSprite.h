#pragma once


#include <string>
#include<vector>
#include "Structs.h"

namespace dae
{
	class Texture2D;
	class AnimationSprite final
	{
	public:
		struct SpriteDescription
		{
			SpriteDescription()
			{
				nrFrames = 1;
				nrPerType = { 1 };
				nrAngles = 1;
				framesPerSecond = 0.f;
			}
			int nrFrames;
			std::vector<int> nrPerType;
			int nrAngles;
			float framesPerSecond;
		};
		// Create a sprite
		// 
		// This function devides a sprite sheet in sections to know which ones it has to show.
		//----------------------------------- Variable explenation ------------------------------------	
		// filename: 
		//		name of the texture file.
		//	nrFrames: 
		//		amount of  frames (#coloumns).
		// 	nrPerType: 
		//		The length of this vector represent the # of types in the sprite sheet (f.e. standing, croutching, jumping,...)
		//		Each number represent the amount of unique actions each type has 
		//		(f.e. Type <standing> has an idle, hipFire, aimUp, and aimDown. This brings us to a total of 4)
		//		(NOTE: this does NOT include two of the same actions but in a different angles, ex. run right, run left)
		//  nrAngles:
		//		This tells the class how many angles there are for every unique action. (these are located underneath the specific action)
		// 	    For a typical game, the characters is most of the time shot from two angles, left and right, this means that nrAngles = 2;
		// Framesec: 
		//		ammount of type each frame takes.
		AnimationSprite(const std::string& path, SpriteDescription desc);
		~AnimationSprite() = default;
		AnimationSprite(const AnimationSprite& other) = delete;
		AnimationSprite(AnimationSprite&& other) = delete;
		AnimationSprite& operator=(const AnimationSprite& other) = delete;
		AnimationSprite& operator=(AnimationSprite&& other) = delete;



		void SetAnimation(int type, int action, int angle, bool reverse);
		void SetAnimationType(int type);
		void SetAnimationAction(int action);
		void SetAnimationAngle(int angle);
		void SetAnimationFrame(int frameNr);
		void SetAnimationDone(bool animationDone);
		void SetAnimationReverse(bool reverse);
		void ResetAnimationFrame(bool reverse);
		void Update();


		int GetAnimationFrame();
		// Control if the animation is finished
		bool IsAnimationDone() const;

		Rectanglef GetSourceRect() { return m_srcRect; }
		const std::shared_ptr<Texture2D>& GetTexture() { return m_spTexture; }

		float GetFrameWidth() const;
		float GetFrameHeight() const;


	private:
		struct AnimationInfo
		{
			AnimationInfo()
			{
				AnimFrame = 0;
				CurrentType = 0;
				CurrentAction = 0;
				CurrentAngle = 0;
				Reverse = false;
				AnimationDone = false;
			}
			int   AnimFrame;
			int CurrentType;
			int CurrentAction;
			int CurrentAngle;
			bool Reverse;
			bool AnimationDone;
		};
		// Base animation
		std::shared_ptr<Texture2D> m_spTexture;
		std::string m_Path;
		SpriteDescription m_Description;
		AnimationInfo m_Info;

		float m_AnimTime;

		// Selection box
		float m_ClipHeight;
		float m_ClipWidth;
		Rectanglef m_srcRect;




		void DetermineAnimationFrame();
		int GetAnimationRow() const;
	};

}


