#pragma once

#include "Paperworks/Core/Core.h"
#include "Paperworks/Events/Event.h"
#include "Paperworks/Core/Time.h"

namespace Paperworks {

	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Time ts) {}
		virtual void OnFixedUpdate() {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		const std::string& GetName() const { return m_DebugName; }
	private:
		std::string m_DebugName;
	};
}