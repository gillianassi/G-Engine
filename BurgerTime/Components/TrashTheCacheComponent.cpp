#include "BurgerTimePCH.h"
#include "TrashTheCacheComponent.h"
#include "imgui.h"
#include "imgui_plot.h"
#include <chrono>

dae::TrashTheCacheComponent::TrashTheCacheComponent(GameObject* pOwner):
	dae::BaseComponent(pOwner),
	m_CalcInts{true},
	m_CalcGameObject3D{true},
	m_CalcGameObject3DAlt{true}
{
	memset(m_IntDurationArr, 0, sizeof(float)* m_nrOfStepsizes);
	memset(m_GameObject3DDurationArr, 0, sizeof(float)* m_nrOfStepsizes);
	memset(m_GameObject3DAltDurationArr, 0, sizeof(float)* m_nrOfStepsizes);
}

dae::TrashTheCacheComponent::~TrashTheCacheComponent()
{
	delete[] m_IntBuffer;
	m_IntBuffer = nullptr;
	delete[] m_GameObject3DBuffer;
	m_GameObject3DBuffer = nullptr;
	delete[] m_GameObject3DAltBuffer;
	m_GameObject3DAltBuffer = nullptr;

}

void dae::TrashTheCacheComponent::Update()
{
	// Clamp the values
	if (m_NrOfSamplesEx1 < 0) m_NrOfSamplesEx1 = 0;
	if (m_NrOfSamplesEx1 > 100) m_NrOfSamplesEx1 = 100;
	if (m_NrOfSamplesEx2 < 0) m_NrOfSamplesEx2 = 0;
	if (m_NrOfSamplesEx2 > 100) m_NrOfSamplesEx2 = 100;

	if (m_CalcInts)
		CalculateWithInts();
	if (m_CalcGameObject3D)
		CalculateWithGameObject3D();
	if (m_CalcGameObject3DAlt)
		CalculateWithGameObject3DAlt();
}

void dae::TrashTheCacheComponent::FixedUpdate()
{
}

void dae::TrashTheCacheComponent::RenderImGui()
{
	static uint32_t selection_start = 0, selection_length = 0;
	IM_ASSERT(ImGui::GetCurrentContext() != NULL && "Missing dear imgui context. Refer to examples app!");
	ImGui::Begin("Exercise 1");
	ImGui::InputInt("# samples", &m_NrOfSamplesEx1);
	if (ImGui::Button("Trash the cache"))
	{
		m_CalcInts = true;
	}
	ImGui::PlotConfig confInt;
	confInt.values.ys = m_IntDurationArr;
	confInt.values.count = m_nrOfStepsizes;
	confInt.scale.min = -1;
	confInt.scale.max = 1000;
	confInt.tooltip.show = true;
	confInt.tooltip.format = "x=%.2f, y=%.2f";
	confInt.grid_x.show = true;
	confInt.grid_y.show = true;
	confInt.frame_size = ImVec2(250, 100);
	confInt.line_thickness = 2.f;
	confInt.values.color = ImColor(255, 0, 0);
	ImGui::Plot("Exercise 1", confInt);
	ImGui::End();

	// Second window
	ImGui::Begin("Exercise 2");
	ImGui::InputInt("# samples", &m_NrOfSamplesEx2);
	if (ImGui::Button("Trash the cache with GameObject3D"))
	{
		m_CalcGameObject3D = true;
	}
	ImGui::PlotConfig conf;
	conf.values.ys = m_GameObject3DDurationArr;
	conf.values.count = m_nrOfStepsizes;
	conf.scale.min = -1;
	conf.scale.max = 5000;
	conf.tooltip.show = true;
	conf.tooltip.format = "x=%.2f, y=%.2f";
	conf.grid_x.show = true;
	conf.grid_y.show = true;
	conf.frame_size = ImVec2(250, 100);
	conf.line_thickness = 2.f;
	conf.selection.start = &selection_start;
	conf.values.color = ImColor(255, 255, 0);

	ImGui::Plot("Exercise2-GameObject3D", conf);

	if (ImGui::Button("Trash the cache with GameObject3DAlt"))
	{
		m_CalcGameObject3DAlt = true;
	}
	// reset previous values	
	conf.values.ys = nullptr;
	conf.selection.show = false;
	conf.values.ys = m_GameObject3DAltDurationArr;
	conf.values.offset = selection_start;
	conf.selection.start = &selection_start;
	conf.values.color = ImColor(255, 0, 255);

	ImGui::Plot("Exercise2-GameObject3DAlt", conf);

	ImGui::Text("Combined:");
	// reset previous values
	conf.values.ys = nullptr;
	conf.selection.show = false;
	const float* y_data[] = {m_GameObject3DDurationArr, m_GameObject3DAltDurationArr};
	//ImGui::Begin("Example plot", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	// Draw first plot with multiple sources
	conf.values.ys_list = y_data;
	conf.values.offset = selection_start;
	conf.values.ys_count = 2;
	ImU32 colors[2] = { ImColor(255, 255, 0), ImColor(255, 0, 255) };
	conf.values.colors = colors;

	ImGui::Plot("Comparisson", conf);
	ImGui::End();

}

void dae::TrashTheCacheComponent::CalculateWithInts()
{
	memset(m_IntDurationArr, 0, sizeof(m_IntDurationArr));
	for (int samplenNr = 0; samplenNr < m_NrOfSamplesEx1; samplenNr++)
	{
		int stepSize = 1;
		for (int current_StepIdx = 0; current_StepIdx < m_nrOfStepsizes; current_StepIdx += 1) // Go to stepsize 1024
		{
			stepSize *= 2;
			auto start{ std::chrono::high_resolution_clock::now() };

			for (size_t idx{}; idx < m_BufferSize; idx += stepSize)
			{
				m_IntBuffer[idx] *= (int)idx;
			}

			auto end{ std::chrono::high_resolution_clock::now() };

			m_IntDurationArr[current_StepIdx] += (int)std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

		}
	}
	for (size_t i = 0; i < m_nrOfStepsizes; i++)
	{
		m_IntDurationArr[i] /= (int)m_NrOfSamplesEx1;
	}
	//std::cout << "Exercise 1 Results: " << std::endl;
	//std::cout << "--------------------" << std::endl;
	//PrintTimeStepArray(m_IntDurationArr, m_nrOfStepsizes);

	m_CalcInts = false;
}

void dae::TrashTheCacheComponent::CalculateWithGameObject3D()
{
	memset(m_GameObject3DDurationArr, 0, sizeof(m_GameObject3DDurationArr));
	for (int samplenNr = 0; samplenNr < m_NrOfSamplesEx2; samplenNr++)
	{
		int stepSize = 1;
		for (int current_StepIdx = 0; current_StepIdx < m_nrOfStepsizes; current_StepIdx += 1) // Go to stepsize 1024
		{
			stepSize *= 2;
			auto start{ std::chrono::high_resolution_clock::now() };

			for (size_t idx{}; idx < m_BufferSize; idx += stepSize)
			{
				m_GameObject3DBuffer[idx].ID *= (int)idx;
			}

			auto end{ std::chrono::high_resolution_clock::now() };

			m_GameObject3DDurationArr[current_StepIdx] += (int)std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

		}
	}
	for (size_t i = 0; i < m_nrOfStepsizes; i++)
	{
		m_GameObject3DDurationArr[i] /= (int)m_NrOfSamplesEx2;
	}
	//std::cout << "Exercise 2 Results: " << std::endl;
	//std::cout << "--------------------" << std::endl;
	//PrintTimeStepArray(m_GameObject3DDurationArr, m_nrOfStepsizes);


	m_CalcGameObject3D = false;
}

void dae::TrashTheCacheComponent::CalculateWithGameObject3DAlt()
{
	memset(m_GameObject3DAltDurationArr, 0, sizeof(m_GameObject3DAltDurationArr));
	for (int samplenNr = 0; samplenNr < m_NrOfSamplesEx2; samplenNr++)
	{
		int stepSize = 1;
		for (int current_StepIdx = 0; current_StepIdx < m_nrOfStepsizes; current_StepIdx += 1) // Go to stepsize 1024
		{
			stepSize *= 2;
			auto start{ std::chrono::high_resolution_clock::now() };

			for (size_t idx{}; idx < m_BufferSize; idx += stepSize)
			{
				m_GameObject3DAltBuffer[idx].ID *= (int)idx;
			}

			auto end{ std::chrono::high_resolution_clock::now() };

			m_GameObject3DAltDurationArr[current_StepIdx] += (int)std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

		}
	}
	for (size_t i = 0; i < m_nrOfStepsizes; i++)
	{
		m_GameObject3DAltDurationArr[i] /= (int)m_NrOfSamplesEx2;
	}
	//std::cout << "Exercise 3 Results: " << std::endl;
	//std::cout << "--------------------" << std::endl;
	//PrintTimeStepArray(m_GameObject3DAltDurationArr, m_nrOfStepsizes);


	m_CalcGameObject3DAlt = false;
}

void dae::TrashTheCacheComponent::PrintTimeStepArray(const float timeStepArray[], size_t nrOfSteps)
{
	for (size_t i = 0; i < nrOfSteps; i++)
	{
		std::cout << pow(2, i + 1) << "; " << timeStepArray[i] << std::endl;
	}
	std::cout << std::endl;
}
