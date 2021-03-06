#include "Enemy.h"



Enemy::Enemy(){}
Enemy::Enemy(std::ifstream & file): TexturedEntity(file) {
	file.read((char*)glm::value_ptr(m_texCoord), 2 * sizeof(float));
	file.read((char*)glm::value_ptr(m_offset), 2 * sizeof(float));
	file.read((char*)glm::value_ptr(m_dir), 3 * sizeof(float));
	file.read((char*)&m_speed, sizeof(float));
	int tmp;
	file.read((char*)&tmp, sizeof(int));
	m_status = (State)tmp;
	file.read((char*)&m_health, sizeof(float));
	file.read((char*)&m_deathTime, sizeof(float));
	m_prevPos = m_pos;
	DEngine::CollisionManager::changeAABB(m_minAABB, m_maxAABB, m_pos);
	DEngine::Physics(m_pos);

}
Enemy::Enemy(std::string bindName, glm::vec4 p) : TexturedEntity(bindName, p) {
	m_status = State::IDLE;
	m_deathTime = 0.0f;
	m_prevPos = m_pos;
	DEngine::CollisionManager::changeAABB(m_minAABB, m_maxAABB, m_pos);

}




Enemy::~Enemy() {}

void Enemy::update(glm::vec3 playerPos) {
	playerPos -= glm::vec3(0.0f, 0.5f, 0.0f);
	glm::vec3 deltaPos = playerPos - glm::vec3(m_pos.x, m_pos.y, m_pos.z);
	if (m_status != State::DEAD) {
		if (m_health <= 0) {
			m_status = State::DEAD;

		}
		else if (glm::distance(playerPos, glm::vec3(m_pos)) <= 0.75f) {
			m_status = State::ATTACK;
		}
		else if (glm::distance(playerPos, glm::vec3(m_pos)) <= 3.0f) {
			m_status = State::MOVING;
		}
		else if (glm::distance(playerPos, glm::vec3(m_pos)) >= 3.0f) {
			m_status = State::IDLE;
		}
	}
	m_texCoord.y = (float)m_status;
	if (m_status == State::DEAD) {
		if ((float)((int)((glfwGetTime() - m_deathTime) * 5)) < 9) {
			m_texCoord.x = (float)((int)((glfwGetTime() - m_deathTime) * 5) % 10);
		}
		else {
			m_texCoord.x = 9;
		}
	}
	else {
		m_texCoord.x = (float)((int)((glfwGetTime() - m_deathTime) * 5) % 10);
	}
	if (m_status == State::MOVING) {
		move(deltaPos);
	}
	DEngine::Physics::update();
	
}

void Enemy::writeToFile(std::ofstream & file) {
	TexturedEntity::writeToFile(file);
	DEngine::FileManager::write2f(file, m_texCoord);
	DEngine::FileManager::write2f(file, m_offset);
	DEngine::FileManager::write3f(file, m_dir);
	file.write((char*)&m_speed, sizeof(float));
	int tmp;
	tmp = (int)m_status;
	file.write((char*)&tmp, sizeof(int));
	file.write((char*)&m_health, sizeof(float));
	file.write((char*)&m_deathTime, sizeof(float));
}

void Enemy::setBack() {
	DEngine::Physics::setBack(m_pos, m_prevPos);
	DEngine::CollisionManager::changeAABB(m_minAABB, m_maxAABB, m_pos);

}

void Enemy::gravity() {
	DEngine::Physics::gravity(m_pos);
	DEngine::CollisionManager::changeAABB(m_minAABB, m_maxAABB, m_pos);
}

void Enemy::moveUp() {
	DEngine::Physics::moveUp(m_pos, m_prevPos);
	DEngine::CollisionManager::changeAABB(m_minAABB, m_maxAABB, m_pos);

}

void Enemy::die() {
	if (m_status != State::DEAD) {
		m_status = State::DEAD;
		m_deathTime = glfwGetTime();
	}
}

void Enemy::move(glm::vec3 deltaPos) {
	m_prevPos = m_pos;
	m_dir = glm::normalize(deltaPos);
	m_dir *= m_speed * DEngine::deltaTime;
	m_dir.y = 0.0f;
	/*if (deltaPos.x < 0.0f && deltaPos.y < 0.0f && deltaPos.z < 0.0f) {
		m_pos -= m_dir * m_speed;
	}
	else
	{
		m_pos += m_dir * m_speed;
	}*/
	Entity::translate(m_dir);
	DEngine::CollisionManager::changeAABB(m_minAABB, m_maxAABB, m_pos);

}
