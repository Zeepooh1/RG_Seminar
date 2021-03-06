#pragma once

#include <vector>

#include "Entity.h"

class TexturedEntity: public Entity {
public:
	TexturedEntity();
	TexturedEntity(std::ifstream& file);
	TexturedEntity(std::string bindName, glm::vec4 p);
	~TexturedEntity();
	std::vector<std::string> getTex() { return m_texBind; }
	void setTexBind(std::string texBind);
	void draw(DEngine::Binder& b);
	void writeToFile(std::ofstream& file);
protected:
	std::vector<std::string> m_texBind;
};

