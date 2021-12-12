#include "Camera.h"

Camera* Camera::s_Instance = nullptr;

void Camera::Update(float dt) {
	if (m_Target != nullptr) {
		m_ViewBox.x = m_Target->x - 1280 / 2;
		m_ViewBox.y = m_Target->y - 720 / 2;

		if (m_ViewBox.x < 0) {
			m_ViewBox.x = 0;
		}

		if (m_ViewBox.y < 0) {
			m_ViewBox.y = 0;
		}

		if (m_ViewBox.x > (2 * 1280 - m_ViewBox.w)) {
			m_ViewBox.x = (2 * 1280 - m_ViewBox.w);
		}

		if (m_ViewBox.y > (720 - m_ViewBox.h)) {
			m_ViewBox.y = (720 - m_ViewBox.h);
		}

		m_Position = Vector2f(m_ViewBox.x, m_ViewBox.y);
	}
}