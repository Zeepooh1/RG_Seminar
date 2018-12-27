#include "Player.h"
#include "Collision.h"



Player::Player() {
	m_speed = 2.5f;
	m_sprint = false;
	m_move = 0;
	m_pitch = 0.0f;
	m_yaw = 270.0f;
	m_stepHeight = 50; //higher value --> smaller height
	m_stepLen = 0.2; //higher value --> longer step;
}


Player::~Player() {}

void Player::move(Direction d) {

	m_prevPos = m_pos;
	//m_pos += glm::vec3(0.0f, sin(m_move/m_stepLen)/m_stepHeight, 0.0f);
	glm::vec3 t = glm::vec3(0.0f, 0.0f, 0.0f);
	m_move += 0.05;
	if (d == Direction::FORWARD) {
		m_pos += ((m_speed * (float)DEngine::deltaTime) * ((int)m_sprint + 1))  * glm::vec3(m_front.x, 0.0f, m_front.z);
	}
	
	if (d == Direction::BACKWARD) {
		m_pos -= ((m_speed * (float)DEngine::deltaTime) * ((int)m_sprint + 1))  * glm::vec3(m_front.x, 0.0f, m_front.z);
	}

	if (d == Direction::LEFT) {
		m_pos -= glm::normalize(glm::cross(m_front, m_up)) * (m_speed * (float)DEngine::deltaTime);;
	}
	if (d == Direction::RIGHT) {
		m_pos += glm::normalize(glm::cross(m_front, m_up)) * (m_speed * (float)DEngine::deltaTime);

	}
	

}


void Player::toggleSprint() {
	m_sprint = true;
}

void Player::unToggleSprint() {
	m_sprint = false;
}

void Player::update(glm::vec2 offset) {
	offset.x *= DEngine::sensitivity;
	offset.y *= DEngine::sensitivity;
	m_yaw += offset.x;
	m_pitch += offset.y;
	if (m_pitch > 89.0f) {
		m_pitch = 89.0f;
	}
	if (m_pitch < -89.0f) {
		m_pitch = -89.0f;
	}

	m_front.x = cos(glm::radians(m_pitch)) * cos(glm::radians(m_yaw));
	m_front.y = sin(glm::radians(m_pitch));
	m_front.z = cos(glm::radians(m_pitch)) * sin(glm::radians(m_yaw));
	m_front = glm::normalize(m_front);



	Camera::update();
}
void Player::goBack() {
	m_pos = m_prevPos;
}

