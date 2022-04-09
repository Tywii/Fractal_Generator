#pragma once
#include "Geometry.h"
#include <string>

class Fractals {
public:

	SquaresDiamonds(int m, CPU_Geometry& cpuGeom, GPU_Geometry& gpuGeom)
	Fractals(float L[3], float T[3], float R[3], int m, CPU_Geometry& cpuGeom, GPU_Geometry& gpuGeom, glm::vec3 colour);
	void Sierpinsky(float L[3], float T[3], float R[3], int m, CPU_Geometry& cpuGeom, GPU_Geometry& gpuGeom, glm::vec3 colour);

private:

	//CPU_Geometry cpu;
	//GPU_Geometry gpu;




};
