#include "GEnginePCH.h"
#include "AnimationSprite.h"
#include "ResourceManagement/ResourceManager.h"
#include "ResourceManagement/Texture2D.h"
#include "Core/Time.h"

#include "SDL_rect.h"

dae::AnimationSprite::AnimationSprite(const std::string& path, SpriteDescription desc):
	m_Path{ path },
	m_Description{desc},
	m_Info{},
	m_AnimTime{ 0.f }
{


	if (m_Description.nrAngles < 1)
	{
		m_Description.nrAngles = 1;
	}
	m_spTexture = ResourceManager::GetInstance().LoadTexture(path);
	m_ClipHeight = GetFrameHeight();
	m_ClipWidth = GetFrameWidth();
	m_srcRect = Rectanglef{ 0.f,0.f, m_ClipWidth, m_ClipHeight };
}

void dae::AnimationSprite::SetAnimation(int type, int action, int angle, bool reverse)
{
	int newType = type % (int)(m_Description.nrPerType.size());
	int newAction = action % (int)(m_Description.nrPerType[type]);
	int newAngle = angle % (m_Description.nrAngles);
	if (m_Info.CurrentType != newType || m_Info.CurrentAction != newAction || m_Info.CurrentAngle != newAngle || m_Info.Reverse != reverse)
	{
		ResetAnimationFrame(reverse);
	}
	m_Info.CurrentType = newType;
	m_Info.CurrentAction = newAction;
	m_Info.CurrentAngle = newAngle;
	m_Info.Reverse = reverse;
}

void dae::AnimationSprite::SetAnimationType(int type)
{
	int newType = type % (int)(m_Description.nrPerType.size());
	if (m_Info.CurrentType != newType)
	{
		ResetAnimationFrame(m_Info.Reverse);
	}
	m_Info.CurrentType = newType;
}

void dae::AnimationSprite::SetAnimationAction(int action)
{
	int newAction = action % (int)(m_Description.nrPerType[m_Info.CurrentType]);
	if (m_Info.CurrentAction != newAction)
	{
		ResetAnimationFrame(m_Info.Reverse);
	}
	m_Info.CurrentAction = newAction;
}

void dae::AnimationSprite::SetAnimationAngle(int angle)
{
	int newAngle = angle % (m_Description.nrAngles);
	if (m_Info.CurrentAngle != newAngle)
	{
		ResetAnimationFrame(m_Info.Reverse);
	}
	m_Info.CurrentAngle = newAngle;
}

void dae::AnimationSprite::SetAnimationFrame(int frameNr)
{
	m_Info.AnimFrame = frameNr;
}

void dae::AnimationSprite::SetAnimationDone(bool animationDone)
{
	m_Info.AnimationDone = animationDone;
}

void dae::AnimationSprite::SetAnimationReverse(bool reverse)
{
	if (m_Info.Reverse != reverse)
	{
		ResetAnimationFrame(reverse);
	}
	m_Info.Reverse = reverse;
}

void dae::AnimationSprite::ResetAnimationFrame(bool reverse)
{
	// set the correct frame
	if (reverse)
	{
		m_Info.AnimFrame = m_Description.nrFrames;
	}
	else
	{
		m_Info.AnimFrame = 0;
	}
	// indicate that the animation didn't loop yet
	m_Info.AnimationDone = false;
}

void dae::AnimationSprite::Update()
{
	// Determine frame
	DetermineAnimationFrame();

	// Determine position
	m_srcRect.left = m_ClipWidth * m_Info.AnimFrame;

	m_srcRect.bottom = m_ClipHeight + m_ClipHeight * GetAnimationRow();
}

int dae::AnimationSprite::GetAnimationFrame()
{
	return m_Info.AnimFrame;
}

bool dae::AnimationSprite::IsAnimationDone() const
{
	return m_Info.AnimationDone;
}


float dae::AnimationSprite::GetFrameWidth() const
{
	return m_spTexture->GetWidth() / float(m_Description.nrFrames);
}

float dae::AnimationSprite::GetFrameHeight() const
{
	int rows{};
	for (size_t i = 0; i < m_Description.nrPerType.size(); i++)
	{
		rows += m_Description.nrPerType[i] * m_Description.nrAngles;
	}
	return m_spTexture->GetHeight() / float(rows);
}

void dae::AnimationSprite::DetermineAnimationFrame()
{
	m_AnimTime += Time::deltaTime;
	if (m_AnimTime > m_Description.framesPerSecond)
	{
		// Go to next frame
		if (!m_Info.Reverse)
		{
			++m_Info.AnimFrame;
			if (m_Info.AnimFrame >= m_Description.nrFrames)
			{
				m_Info.AnimFrame = 0;
				m_Info.AnimationDone = true;
			}
		}
		else
		{
			--m_Info.AnimFrame;
			if (m_Info.AnimFrame < 0)
			{
				m_Info.AnimFrame = m_Description.nrFrames;
				m_Info.AnimationDone = true;
			}
		}

		// Only keep the remaining time
		m_AnimTime -= m_Description.framesPerSecond;
	}
}

int dae::AnimationSprite::GetAnimationRow() const
{
	int row{};
	for (size_t i = 0; i < m_Info.CurrentType; i++)
	{
		row += m_Description.nrPerType[i] * m_Description.nrAngles;
	}
	row += m_Info.CurrentAction * m_Description.nrAngles + m_Info.CurrentAngle;
	return row;
}
