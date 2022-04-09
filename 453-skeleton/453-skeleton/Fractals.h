#pragma once
#include "Geometry.h"
#include <string>

class Fractals {
public:

	Fractals(int switcher, int m, CPU_Geometry& cpuGeom, GPU_Geometry& gpuGeom);
	void Switcher(int switcher, int m, CPU_Geometry& cpuGeom, GPU_Geometry& gpuGeom);

	

	Fractals(float L[3], float T[3], float R[3], int m, CPU_Geometry &cpuGeom, GPU_Geometry &gpuGeom, glm::vec3 colour);
	void Sierpinsky(float L[3], float T[3], float R[3], int m, CPU_Geometry& cpuGeom, GPU_Geometry& gpuGeom, glm::vec3 colour);

	Fractals(int m, float A[3], float B[3], float C[3], float D[3], CPU_Geometry& cpuGeom, GPU_Geometry& gpuGeom, glm::vec3 colour);
	void SquaresDiamonds(int m, float A[3], float B[3], float C[3], float D[3], CPU_Geometry& cpuGeom, GPU_Geometry& gpuGeom, glm::vec3 colour);

	Fractals(int m, float start[3], float end[3], CPU_Geometry& cpuGeom, GPU_Geometry& gpuGeom);
	void Koch(int m, float start[3], float end[3], CPU_Geometry& cpuGeom, GPU_Geometry& gpuGeom);

	Fractals(int m , CPU_Geometry& cpuGeom, GPU_Geometry& gpuGeom);
	void Dragon(int m, CPU_Geometry& cpuGeom, GPU_Geometry& gpuGeom);
	
private:
	int mOrig;
	//CPU_Geometry cpu;
	//GPU_Geometry gpu;
	



};
