#pragma once
#ifndef WALL_H
#define WALL_H

#include <vector>

#include "Mesh.h"
#include "Model.h"

class Wall {
public:
	Wall() {}
	~Wall() {
		Release();
	}
	void Initialise();
	void Update(float dTime);
	void Render(float dTime);
	void Release();

	Model mBox, mQuad;

private:
	std::vector<Model*> mOpaques;
};
#endif