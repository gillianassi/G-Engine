#include "GEnginePCH.h"
#include "AnimatorComponent.h"
#include <cassert>

#include "SceneGraph/GameObject.h"
#include "EngineComponents/RenderComponent.h"

dae::AnimatorComponent::AnimatorComponent(GameObject* pOwner) :
	BaseComponent(pOwner),
	m_pRenderComponent{nullptr},
	m_SpriteSheetMap{},
	AnimationMap{},
	m_CurrentAnimationIndex{},
	m_CurrentSpriteSheetIndex{},
	m_PreviousSpriteSheetIndex{},
	m_AnimationComplete{},
	m_NrOfSpriteSheets{0},
	m_NrOfAnimations{0},
	m_IsLookingLeft{}
{

}

dae::AnimatorComponent::~AnimatorComponent()
{
	for (auto& [key, pValue] : m_SpriteSheetMap)
	{
		delete pValue;
		pValue = nullptr;
	}
	for (auto& [key, pValue] : AnimationMap)
	{
		delete pValue;
		pValue = nullptr;
	}
}

void dae::AnimatorComponent::Initialize()
{
	m_pRenderComponent = GetGameObject()->GetComponentOfType<RenderComponent>();
	if (m_pRenderComponent == nullptr)
	{
		std::cout << "AnimatorComponent Initialize() > No Rendercomponent found on gameObject! Please add one first." << std::endl;
		assert(m_pRenderComponent != nullptr);
	}
}

void dae::AnimatorComponent::Update()
{
	if (m_NrOfSpriteSheets == 0  || m_NrOfAnimations == 0|| !IsInitialized())
		return;

	m_SpriteSheetMap[m_CurrentSpriteSheetIndex]->Update();

	if ((m_PreviousSpriteSheetIndex != m_CurrentSpriteSheetIndex) || (m_pRenderComponent->GetTexture() == nullptr))
	{
		m_pRenderComponent->SetTexture(m_SpriteSheetMap[m_CurrentSpriteSheetIndex]->GetTexture());
	}
	auto srcRect = m_SpriteSheetMap[m_CurrentSpriteSheetIndex]->GetSourceRect();
	SDL_Rect rect{};
	rect.x = int(srcRect.left);
	rect.y = int(srcRect.bottom);
	rect.w = int(srcRect.width);
	rect.h = int(srcRect.height);
	m_pRenderComponent->SetSourceRect(rect);
	m_pRenderComponent->MirrorHorizontal(AnimationMap[m_CurrentSpriteSheetIndex]->mirrorHorizontal);
	m_pRenderComponent->MirrorVertical(AnimationMap[m_CurrentSpriteSheetIndex]->mirrorVertical);

	m_PreviousSpriteSheetIndex = m_CurrentSpriteSheetIndex;
}


int dae::AnimatorComponent::AddSpriteSheet(const std::string& path, const AnimationSprite::SpriteDescription& desc)
{
	m_SpriteSheetMap[m_NrOfSpriteSheets] = new AnimationSprite(path, desc);


	++m_NrOfSpriteSheets;

    return m_NrOfSpriteSheets - 1;
}

int dae::AnimatorComponent::AddAnimation(const AnimationDescription& desc)
{
	if (size_t(desc.spriteSheetId) < m_SpriteSheetMap.size())
	{
		AnimationMap[m_NrOfAnimations] = new AnimationDescription(desc.spriteSheetId, desc.loop, desc.type, desc.action,
			desc.reverse, desc.mirrorHorizontal, desc.mirrorVertical);
		++m_NrOfAnimations;
	}
	else
	{
		std::cout << "The current animation (animationID = " << std::to_string(m_NrOfAnimations)
			<< ") references a spriteSheetID that is out of scope!  Final SpriteSheetId:" << std::to_string(m_SpriteSheetMap.size() - 1)
			<< ". Your inserted SpriteSheetId: " << std::to_string(desc.spriteSheetId) << std::endl;
		assert(m_SpriteSheetMap.size() < size_t(desc.spriteSheetId));
	}
	return m_NrOfAnimations;
}


void dae::AnimatorComponent::PlayAnimation(int animationId, bool IsLookingLeft)
{
	if (size_t(animationId) < AnimationMap.size())
	{
		// no check needed for the spriteID because it is checked while making the animation
		AnimationDescription* sprite = AnimationMap[animationId];
		m_CurrentSpriteSheetIndex = sprite->spriteSheetId;
		m_CurrentAnimationIndex = animationId;
		//------------------ NEW ANIMATION IS SET OVER HERE
		m_IsLookingLeft = IsLookingLeft;
		m_SpriteSheetMap[m_CurrentSpriteSheetIndex]->SetAnimation(sprite->type, sprite->action, (int)IsLookingLeft, sprite->reverse);
		// remove the reference
		sprite = nullptr;
	}
	else
	{
		std::cout << "Animation ID is out of scope! Final ID number:" << std::to_string(AnimationMap.size() - 1)
			<< ". Your inserted ID number" << std::to_string(animationId) << std::endl;
		assert(size_t(animationId) < AnimationMap.size());
	}
}

float dae::AnimatorComponent::GetFrameWidth(int spriteSheetId)
{
	if (size_t(spriteSheetId) >= m_SpriteSheetMap.size())
	{
		std::cout << "Sprite ID is out of scope! (Max ID =" << std::to_string(m_SpriteSheetMap.size() - 1)
			<< "). Yours was: " << std::to_string(spriteSheetId) << std::endl;
		assert(size_t(spriteSheetId) < m_SpriteSheetMap.size());
	}

	return m_SpriteSheetMap[spriteSheetId]->GetFrameWidth();;
}

float dae::AnimatorComponent::GetFrameHeight(int spriteSheetId)
{
	if (size_t(spriteSheetId) >= m_SpriteSheetMap.size())
	{
		std::cout << "Sprite ID is out of scope! (Max ID =" << std::to_string(m_SpriteSheetMap.size() - 1)
			<< "). Yours was: " << std::to_string(spriteSheetId) << std::endl;
		assert(size_t(spriteSheetId) < m_SpriteSheetMap.size());
	}

	return m_SpriteSheetMap[spriteSheetId]->GetFrameHeight();;
}

int dae::AnimatorComponent::GetCurrentAnimationId() const
{
	return m_CurrentAnimationIndex;
}

int dae::AnimatorComponent::GetCurrentAnimationFrame()
{
	return m_SpriteSheetMap[m_CurrentSpriteSheetIndex]->GetAnimationFrame();

}

bool dae::AnimatorComponent::GetCurrentIsLookingLeft() const 
{
	return m_IsLookingLeft;
}

bool dae::AnimatorComponent::IsCurrentAnimationDone()
{
	return m_SpriteSheetMap[m_CurrentSpriteSheetIndex]->IsAnimationDone();
}

void dae::AnimatorComponent::TransferAnimation(int animationId, bool lookingLeft, int animationFrame, bool isAnimationDone)
{
	PlayAnimation(animationId, lookingLeft);
	m_SpriteSheetMap[m_CurrentSpriteSheetIndex]->ResetAnimationFrame(animationFrame);
	m_SpriteSheetMap[m_CurrentSpriteSheetIndex]->SetAnimationDone(isAnimationDone);
}


