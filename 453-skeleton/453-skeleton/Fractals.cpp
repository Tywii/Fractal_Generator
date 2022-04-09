#include "Fractals.h"
#include "Geometry.h"
#define _USE_MATH_DEFINES
#include <math.h>

Fractals::Fractals(int switcher, int m, CPU_Geometry& cpuGeom, GPU_Geometry& gpuGeom) {
	Switcher(switcher, m, cpuGeom, gpuGeom);
	gpuGeom.setVerts(cpuGeom.verts);
	gpuGeom.setCols(cpuGeom.cols);
}

void Fractals::Switcher(int switcher, int m, CPU_Geometry& cpuGeom, GPU_Geometry& gpuGeom) {
	if (switcher == 0) {
		glm::vec3 baseColour(0.05f, 0.05f, 0.05f);

		float L[3] = { -1, -1, 0 };
		float T[3] = { 0, 1, 0 };
		float R[3] = { 1, -1, 0 };

		/*cpuGeom.verts.push_back(glm::vec3(L[0], L[1], L[2]));
		cpuGeom.verts.push_back(glm::vec3(R[0], R[1], R[2]));
		cpuGeom.verts.push_back(glm::vec3(T[0], T[1], T[2]));

		cpuGeom.cols.push_back(glm::vec3(0.f, 0.f, 0.f));
		cpuGeom.cols.push_back(glm::vec3(0.f, 0.f, 0.f));
		cpuGeom.cols.push_back(glm::vec3(0.f, 0.f, 0.f));*/

		Sierpinsky(L, T, R, m, cpuGeom, gpuGeom, baseColour);
	/*	gpuGeom.setVerts(cpuGeom.verts);
		gpuGeom.setCols(cpuGeom.cols);*/
	}
	else if (switcher == 1) {
		glm::vec3 baseColour(0.f, 0.f, 0.f);

		float A[3] = { -0.99, -0.99, 0 };
		float B[3] = { -0.99, 0.99, 0 };
		float C[3] = { 0.99, 0.99, 0 };
		float D[3] = { 0.99, -0.99, 0 };

		mOrig = m;
		SquaresDiamonds(m, A, B, C, D, cpuGeom, gpuGeom, baseColour);
		/*gpuGeom.setVerts(cpuGeom.verts);
		gpuGeom.setCols(cpuGeom.cols);*/
	}
	else if (switcher == 2) {
		float a1[3] = { -sqrt(3) / 2, -0.5, 0 };
		float a2[3] = { 0, 1, 0 };

		float b1[3] = { 0, 1, 0 };
		float b2[3] = { sqrt(3) / 2, -0.5, 0 };

		float c1[3] = { -sqrt(3) / 2, -0.5, 0 };
		float c2[3] = { sqrt(3) / 2, -0.5, 0 };

		Koch(m, a1, a2, cpuGeom, gpuGeom);
		Koch(m, b1, b2, cpuGeom, gpuGeom);
		Koch(m, c2, c1, cpuGeom, gpuGeom);
	/*	gpuGeom.setVerts(cpuGeom.verts);
		gpuGeom.setCols(cpuGeom.cols);*/
	}
	else if (switcher == 3) {
		float scaler = 1;
		if (m > 0) {
			scaler = pow((float)m, 1.2);
		}

		cpuGeom.verts.push_back(glm::vec3(0, 0, 0));
		cpuGeom.verts.push_back(glm::vec3(0.2 / scaler, -0.2 / scaler, 0));
		cpuGeom.verts.push_back(glm::vec3(0.4 / scaler, 0, 0));

		cpuGeom.cols.push_back(glm::vec3(0.f, 0.f, 0.f));
		cpuGeom.cols.push_back(glm::vec3(0.f, 0.f, 0.f));
		cpuGeom.cols.push_back(glm::vec3(0.f, 0.f, 0.f));

		float x1 = cpuGeom.verts[0][0];
		float y1 = cpuGeom.verts[0][1];

		Dragon(m, cpuGeom, gpuGeom);
		//gpuGeom.setVerts(cpuGeom.verts);
		//gpuGeom.setCols(cpuGeom.cols);
	}
}

Fractals::Fractals(float L[3], float T[3], float R[3], int m, CPU_Geometry& cpuGeom, GPU_Geometry& gpuGeom, glm::vec3 colour) {

	//cpu = cpuGeom;
	//gpu = gpuGeom;
	/*glm::vec3 baseColour(0.05f, 0.05f, 0.05f);

	float L[3] = { -1, -1, 0 };
	float T[3] = { 0, 1, 0 };
	float R[3] = { 1, -1, 0 };

	cpuGeom.verts.push_back(glm::vec3(L[0], L[1], L[2]));
	cpuGeom.verts.push_back(glm::vec3(R[0], R[1], R[2]));
	cpuGeom.verts.push_back(glm::vec3(T[0], T[1], T[2]));

	Sierpinsky(L, T, R, m, cpuGeom, gpuGeom, colour);
	gpuGeom.setVerts(cpuGeom.verts);
	gpuGeom.setCols(cpuGeom.cols);*/
}

Fractals::Fractals(int m, float A[3], float B[3], float C[3], float D[3], CPU_Geometry& cpuGeom, GPU_Geometry& gpuGeom, glm::vec3 colour) {
	//glm::vec3 baseColour(0.f, 0.f, 0.f);

	//float A[3] = { -0.99, -0.99, 0 };
	//float B[3] = { -0.99, 0.99, 0 };
	//float C[3] = { 0.99, 0.99, 0 };
	//float D[3] = { 0.99, -0.99, 0 };

	//mOrig = m;
	//SquaresDiamonds(m, A, B, C, D, cpuGeom, gpuGeom, colour);
	//gpuGeom.setVerts(cpuGeom.verts);
	//gpuGeom.setCols(cpuGeom.cols);
}

Fractals::Fractals(int m, float start[3], float end[3], CPU_Geometry& cpuGeom, GPU_Geometry& gpuGeom) {

	/*float start[3] = { -0.5, 0, 0 };
	float end[3] = { 0.5, 0, 0 };

	float a1[3] = { -sqrt(3) / 2, -0.5, 0 };
	float a2[3] = { 0, 1, 0 };

	float b1[3] = { 0, 1, 0 };
	float b2[3] = { sqrt(3) / 2, -0.5, 0 };

	float c1[3] = { -sqrt(3) / 2, -0.5, 0 };
	float c2[3] = { sqrt(3) / 2, -0.5, 0 };

	Koch(m, a1, a2, cpuGeom, gpuGeom);
	Koch(m, b1, b2, cpuGeom, gpuGeom);
	Koch(m, c2, c1, cpuGeom, gpuGeom);
	gpuGeom.setVerts(cpuGeom.verts);
	gpuGeom.setCols(cpuGeom.cols);*/
}

Fractals::Fractals(int m, CPU_Geometry& cpuGeom, GPU_Geometry& gpuGeom) {
	/*float scaler = 1;
	if (m > 0) {
		scaler = pow((float)m, 1.2);
	}
	
	cpuGeom.verts.push_back(glm::vec3(0, 0, 0));
	cpuGeom.verts.push_back(glm::vec3(0.2/scaler, -0.2/scaler, 0));
	cpuGeom.verts.push_back(glm::vec3(0.4/scaler, 0, 0));

	cpuGeom.cols.push_back(glm::vec3(0.f, 0.f, 0.f));
	cpuGeom.cols.push_back(glm::vec3(0.f, 0.f, 0.f));
	cpuGeom.cols.push_back(glm::vec3(0.f, 0.f, 0.f));

	float x1 = cpuGeom.verts[0][0];
	float y1 = cpuGeom.verts[0][1];

	Dragon(m, cpuGeom, gpuGeom);
	gpuGeom.setVerts(cpuGeom.verts);
	gpuGeom.setCols(cpuGeom.cols);*/
}


	void Fractals::Sierpinsky(float L[3], float T[3], float R[3], int m, CPU_Geometry& cpuGeom, GPU_Geometry& gpuGeom, glm::vec3 colour) {

		float A[3];
		float B[3];
		float C[3];

		float ax; float ay; float az;
		float bx; float by; float bz;
		float cx; float cy; float cz;
		float dx; float dy; float dz;
		float ex; float ey; float ez;
		float fx; float fy; float fz;

		for (int i = 0; i < 3; i++) {
			A[i] = L[i];
			B[i] = T[i];
			C[i] = R[i];
		}

		ax = A[0]; ay = A[1]; az = A[2];
		bx = B[0]; by = B[1]; bz = B[2];
		cx = C[0]; cy = C[1]; cz = C[2];

		cpuGeom.verts.push_back(glm::vec3(L[0], L[1], L[2]));
		cpuGeom.verts.push_back(glm::vec3(T[0], T[1], T[2]));
		cpuGeom.verts.push_back(glm::vec3(R[0], R[1], R[2]));

		cpuGeom.cols.push_back(colour);
		cpuGeom.cols.push_back(colour);
		cpuGeom.cols.push_back(colour);
	
		

		
		glm::vec3 c1(colour);
		glm::vec3 c2((colour[0]) / 3, (colour[1]) / 3, (colour[2]) / 3);
		glm::vec3 c3((colour[0]) * 2 / 3, (colour[1]) * 2 / 3, (colour[2 ]) * 2 / 3);

		if (cpuGeom.verts.size() == 3) {
			c1[0] = 1.f; c1[1] = 0.f;  c1[2] = 0.f;
			//c1(1.f, 0.f, 0.f);
			//glm::vec3 c2(0.f, 0.f, 1.f);
			//glm::vec3 c3(0.f, 1.f, 0.f);
			c2[0] = 0.f; c2[1] = 0.f;  c2[2] = 1.f;
			c3[0] = 0.f; c3[1] = 1.f;  c3[2] = 0.f;
		}
		

		if (m > 0) {
			dx = 0.5 * (ax + bx); dy = 0.5 * (ay + by); dz = 0.5 * (az + bz);
			float D[3] = { dx, dy, dz };

			ex = 0.5 * (bx + cx); ey = 0.5 * (by + cy); ez = 0.5 * (bz + cz);
			float E[3] = { ex, ey, ez };

			fx = 0.5 * (ax + cx); fy = 0.5 * (ay + cy); fz = 0.5 * (az + cz);
			float F[3] = { fx, fy, fz };

			/*cpuGeom.verts.push_back(glm::vec3(A[0], A[1], A[2]));
			cpuGeom.verts.push_back(glm::vec3(C[0], C[1], C[2]));
			cpuGeom.verts.push_back(glm::vec3(B[0], B[1], B[2]));*/

			

			cpuGeom.verts.push_back(glm::vec3(D[0], D[1], D[2]));
			cpuGeom.verts.push_back(glm::vec3(E[0], E[1], E[2]));
			cpuGeom.verts.push_back(glm::vec3(F[0], F[1], F[2]));

			
			cpuGeom.cols.push_back(glm::vec3(1.f, 1.f, 1.f));
			cpuGeom.cols.push_back(glm::vec3(1.f, 1.f, 1.f));
			cpuGeom.cols.push_back(glm::vec3(1.f, 1.f, 1.f));

			if (cpuGeom.verts.size() == 6) {
				Sierpinsky(D, B, E, m - 1, cpuGeom, gpuGeom, c2);
				Sierpinsky(A, D, F, m - 1, cpuGeom, gpuGeom, c1);
				Sierpinsky(F, E, C, m - 1, cpuGeom, gpuGeom, c3);
			}

			else if (c1[1] == c1[2]) {	// red
				Sierpinsky(D, B, E, m - 1, cpuGeom, gpuGeom, c1);
				Sierpinsky(A, D, F, m - 1, cpuGeom, gpuGeom, c2);
				Sierpinsky(F, E, C, m - 1, cpuGeom, gpuGeom, c3);
			}
			else if(c1[0] == c1[2]) {	// green
				Sierpinsky(D, B, E, m - 1, cpuGeom, gpuGeom, c3);
				Sierpinsky(A, D, F, m - 1, cpuGeom, gpuGeom, c1);
				Sierpinsky(F, E, C, m - 1, cpuGeom, gpuGeom, c2);
			}
			else {	// blue
				Sierpinsky(D, B, E, m - 1, cpuGeom, gpuGeom, c2);
				Sierpinsky(A, D, F, m - 1, cpuGeom, gpuGeom, c3);
				Sierpinsky(F, E, C, m - 1, cpuGeom, gpuGeom, c1);
			}
		}
	}

	void Fractals::SquaresDiamonds(int m, float A[3], float B[3], float C[3], float D[3], CPU_Geometry& cpuGeom, GPU_Geometry& gpuGeom, glm::vec3 colour) {
		cpuGeom.verts.push_back(glm::vec3(A[0], A[1], A[2]));
		cpuGeom.verts.push_back(glm::vec3(B[0], B[1], B[2]));
		cpuGeom.verts.push_back(glm::vec3(B[0], B[1], B[2]));
		cpuGeom.verts.push_back(glm::vec3(C[0], C[1], C[2]));
		cpuGeom.verts.push_back(glm::vec3(C[0], C[1], C[2]));
		cpuGeom.verts.push_back(glm::vec3(D[0], D[1], D[2]));
		cpuGeom.verts.push_back(glm::vec3(D[0], D[1], D[2]));
		cpuGeom.verts.push_back(glm::vec3(A[0], A[1], A[2]));

		cpuGeom.cols.push_back(colour);
		cpuGeom.cols.push_back(colour);
		cpuGeom.cols.push_back(colour);
		cpuGeom.cols.push_back(colour);
		cpuGeom.cols.push_back(colour);
		cpuGeom.cols.push_back(colour);
		cpuGeom.cols.push_back(colour);
		cpuGeom.cols.push_back(colour);

		if (m > 0) {
			float AB[3] = { (A[0] + B[0]) / 2, (A[1] + B[1]) / 2, (A[2] + B[2]) / 2 };
			float BC[3] = { (B[0] + C[0]) / 2, (B[1] + C[1]) / 2, (B[2] + C[2]) / 2 };
			float CD[3] = { (C[0] + D[0]) / 2, (C[1] + D[1]) / 2, (C[2] + D[2]) / 2 };
			float DA[3] = { (D[0] + A[0]) / 2, (D[1] + A[1]) / 2, (D[2] + A[2]) / 2 };

			float shade = (float(m - 1) / mOrig);

			if (colour[1] == colour[2]) {	// black
				colour[0] = 1 - shade;
				colour[1] = 1 - shade;
				colour[2] = 1.f;
			}
			else {	// blue
				
				colour[0] = 1 - shade;
				colour[1] = 1 - shade;
				colour[2] = 1 - shade;

			}

			SquaresDiamonds(m - 1, AB, BC, CD, DA, cpuGeom, gpuGeom, colour);
		}
		
	}

	void Fractals::Koch(int m, float start[3], float end[3], CPU_Geometry& cpuGeom, GPU_Geometry& gpuGeom) {
		cpuGeom.verts.push_back(glm::vec3(start[0], start[1], start[2]));
		cpuGeom.verts.push_back(glm::vec3(end[0], end[1], end[2]));

		cpuGeom.cols.push_back(glm::vec3(0.f, 0.f, 0.f));
		cpuGeom.cols.push_back(glm::vec3(0.f, 0.f, 0.f));

		if (m > 0) {
			//float mid[3] = { (start[0] + end[0]) / 2, (start[1] + end[1]) / 2 , 0 };
			//float mag = pow(end[0] - start[0], 2) - pow(end[1] - start[1], 2);
			//float dx = 0.5 * mag * sin(30 * M_PI / 180);
			//float dy = 0.5 * mag * tan(30 * M_PI / 180) * sin(30 * M_PI / 180);
			float vx1 = (end[0] - start[0]) / 3;
			float vy1 = (end[1] - start[1]) / 3;
	
			float vx2 = vx1 * cos(60 * M_PI / 180) - vy1 * sin(60 * M_PI / 180);
			float vy2 = vx1 * sin(60 * M_PI / 180) + vy1 * cos(60 * M_PI / 180);

			float x1 = start[0] + vx1;
			float y1 = start[1] + vy1;

			float x2 = x1 + vx2;
			float y2 = y1 + vy2;

			float x3 = x1 + vx1;
			float y3 = y1 + vy1;


			
			cpuGeom.verts.push_back(glm::vec3(x1, y1, 0));
			cpuGeom.verts.push_back(glm::vec3(x2, y2, 0));

			cpuGeom.cols.push_back(glm::vec3(0.f, 0.f, 0.f));
			cpuGeom.cols.push_back(glm::vec3(0.f, 0.f, 0.f));

			cpuGeom.verts.push_back(glm::vec3(x2, y2, 0));
			cpuGeom.verts.push_back(glm::vec3(x3, y3, 0));

			cpuGeom.cols.push_back(glm::vec3(0.f, 0.f, 0.f));
			cpuGeom.cols.push_back(glm::vec3(0.f, 0.f, 0.f));

			cpuGeom.verts.push_back(glm::vec3(x1, y1, 0));
			cpuGeom.verts.push_back(glm::vec3(x3, y3, 0));

			cpuGeom.cols.push_back(glm::vec3(1.f, 1.f, 1.f));
			cpuGeom.cols.push_back(glm::vec3(1.f, 1.f, 1.f));


			float start1[3] = { start[0], start[1], start[2] };
			float end1[3] = { x1, y1, 0 };

			float start2[3] = { x1, y1, 0 };
			float end2[3] = { x2, y2, 0 };

			float start3[3] = { x2, y2, 0 };
			float end3[3] = { x3, y3, 0 };

			float start4[3] = { x3, y3, 0 };
			float end4[3] = { end[0], end[1], end[2] };


			Koch(m - 1, start1, end1, cpuGeom, gpuGeom);
			Koch(m - 1, start2, end2, cpuGeom, gpuGeom);
			Koch(m - 1, start3, end3, cpuGeom, gpuGeom);
			Koch(m - 1, start4, end4, cpuGeom, gpuGeom);
			
		}

	}

	void Fractals::Dragon(int m, CPU_Geometry& cpuGeom, GPU_Geometry& gpuGeom) {
		
	/*	for (int i = 0; i < cpuGeom.verts.size(); i++) {
			float x2 = cpuGeom.verts[i][0];
			float y2 = cpuGeom.verts[i][1];
			float vx1 = x2 - cpuGeom.verts[0][0];
			float vy1 = y2 - cpuGeom.verts[0][0];
			float vx2 = vx1 * cos(-45 * M_PI / 180) - vy1 * sin(-45 * M_PI / 180);
			float vy2 = vx1 * sin(-45 * M_PI / 180) + vy1 * cos(-45 * M_PI / 180);
			cpuGeom.verts[i][0] = cpuGeom.verts[i][0] + vx2;
			cpuGeom.verts[i][1] = cpuGeom.verts[i][1] + vy2;
		}*/

		if (m > 0) {
			int sizeInd = cpuGeom.verts.size() - 1;

			for (int i = cpuGeom.verts.size() - 1; i >= 0; i--) {
				cpuGeom.cols[i][0] = 0.f;
				float x2 = cpuGeom.verts[i][0];
				float y2 = cpuGeom.verts[i][1];
				float vx1 = x2 - cpuGeom.verts[0][0];
				float vy1 = y2 - cpuGeom.verts[0][1];
				float vx2 = vx1 * cos(-45 * M_PI / 180) - vy1 * sin(-45 * M_PI / 180);
				float vy2 = vx1 * sin(-45 * M_PI / 180) + vy1 * cos(-45 * M_PI / 180);
				cpuGeom.verts[i][0] = cpuGeom.verts[0][0] + vx2;//cpuGeom.verts[i][0] + vx2;
				cpuGeom.verts[i][1] = cpuGeom.verts[0][1] + vy2;//cpuGeom.verts[i][1] + vy2;

				float x3 = cpuGeom.verts[i][0];
				float y3 = cpuGeom.verts[i][1];
				float vx3 = x3 - cpuGeom.verts[sizeInd][0];
				float vy3 = y3 - cpuGeom.verts[sizeInd][1];
				float vx4 = vx3 * cos(-90 * M_PI / 180) - vy3 * sin(-90 * M_PI / 180);
				float vy4 = vx3 * sin(-90 * M_PI / 180) + vy3 * cos(-90 * M_PI / 180);
				float x4 = cpuGeom.verts[sizeInd][0] + vx4;
				float y4 = cpuGeom.verts[sizeInd][1] + vy4;

				cpuGeom.verts.push_back(glm::vec3(x4, y4, 0));
				cpuGeom.cols.push_back(glm::vec3(1.f, 0.f, 0.f));
			}
			Dragon(m - 1, cpuGeom, gpuGeom);
		}

		
		
	}

	

