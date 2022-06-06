#pragma once

#include "BaseComponent.h"
#include "ResourceManagement/Texture2D.h"
#include "Misc/AnimationSprite.h"
#include <unordered_map>




namespace dae
{
	class AnimationSprite;
	class RenderComponent;
	class AnimatorComponent final : public BaseComponent
	{
	public:
		struct AnimationDescription
		{
			bool loop; // does the animation loop
			int spriteSheetId; // id of the spritesheet in the spritesheetvec (THIS IS THE INDEX)
			int type; // which type of animation
			int action; // which exact action
			bool reverse; // does it have to be played in reverse
			bool mirrorHorizontal;
			bool mirrorVertical;
			AnimationDescription(int spriteSheetId_, bool loop_, int type_,int action_, 
				bool reverse_ = false, bool mirrorHorizontal_ = false, bool mirrorVertical_ = false)
				:spriteSheetId(spriteSheetId_),
				loop(loop_),
				type(type_),
				action(action_),
				reverse(reverse_),
				mirrorHorizontal(mirrorHorizontal_),
				mirrorVertical(mirrorVertical_)
			{
			}
			AnimationDescription()
			{
				loop = true; 
				spriteSheetId = 0; 
				type = 0;
				action = 0; 
				reverse = false;
				mirrorHorizontal = false;
				mirrorVertical = false;
			}

			AnimationDescription(const AnimationDescription&) = default;
			AnimationDescription(AnimationDescription&&) = default;
			AnimationDescription& operator=(const AnimationDescription&) = default;
			AnimationDescription& operator=(AnimationDescription&&) = default;
		};

		AnimatorComponent(GameObject* pOwner);
		virtual ~AnimatorComponent() override;

		AnimatorComponent(const AnimatorComponent& other) = delete;
		AnimatorComponent(AnimatorComponent&& other) = delete;
		AnimatorComponent& operator=(const AnimatorComponent& other) = delete;
		AnimatorComponent& operator=(AnimatorComponent&& other) = delete;

		void Initialize() override;
		void Update() override;

		int AddSpriteSheet(const std::string& fileName, const AnimationSprite::SpriteDescription& desc);
		int AddAnimation(const AnimationDescription& desc);
		void PlayAnimation(int animationId, bool IsLookingLeft);

		float GetFrameWidth(int spriteSheetId) ;
		float GetFrameHeight(int spriteSheetId);
		int GetCurrentAnimationId() const;
		int GetCurrentAnimationFrame();
		bool GetCurrentIsLookingLeft() const;
		bool IsCurrentAnimationDone();

		void TransferAnimation(int animationId, bool lookingLeft, int animationFrame, bool isAnimationDone);


	private:
		RenderComponent* m_pRenderComponent;

		std::unordered_map<int, AnimationSprite*> m_SpriteSheetMap;
		std::unordered_map<int, AnimationDescription*> AnimationMap;

		int m_CurrentAnimationIndex;
		int m_CurrentSpriteSheetIndex;
		int m_PreviousSpriteSheetIndex;
		bool m_AnimationComplete;

		int m_NrOfSpriteSheets;
		int m_NrOfAnimations;
		bool m_IsLookingLeft;
	};
}
