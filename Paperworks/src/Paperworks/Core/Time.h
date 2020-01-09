#pragma once

namespace Paperworks {

	class Time {
	public:
		Time(float time = 0.0f)
			:m_Time(time)
		{}

		operator float() const { return m_Time; }

		float DeltaTime() const { return m_Time; }
		float GetMilliseconds() const { return m_Time * 1000.0f; }

	private:
		float m_Time;
	};
}