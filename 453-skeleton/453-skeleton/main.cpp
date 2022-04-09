#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

#include "Geometry.h"
#include "GLDebug.h"
#include "Log.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include "Window.h"
#include "Fractals.h"


struct State {
	int m = 0;
	//int switcher = 0;
	bool operator==(State const& other) const {
		return m == other.m;// || switcher == other.switcher;
		//return switcher == other.switcher;
	}
};

//struct State2 {
//	int switcher = 0;
//	bool operator==(State2 const& other) const {
//		return switcher == other.switcher;
//		//return switcher == other.switcher;
//	}
//};

// EXAMPLE CALLBACKS
class MyCallbacks : public CallbackInterface {

public:
	MyCallbacks(ShaderProgram& shader) : shader(shader) {}

	virtual void keyCallback(int key, int scancode, int action, int mods) {

		if (action == GLFW_PRESS || action == GLFW_REPEAT) {
			if (key == GLFW_KEY_LEFT) {
				if (state.m > 0) {
					state.m--;
				}
			}
			if (key == GLFW_KEY_RIGHT) {
				if (state.m < 6) {
					state.m++;
				}
			}
			if (key == GLFW_KEY_UP) {
				state2.m = (state2.m + 1) % 4;
				//state2.m++;
			}
			if (key == GLFW_KEY_DOWN) {
				state2.m = (state2.m - 1) % 4;
				//state2.m--;
			}
		}
	}

	State getState() {
		return state;
	}

	State getState2() {
		return state2;
	}

private:
	ShaderProgram& shader;
	State state;
	State state2;
	//State2 state2;
};

class MyCallbacks2 : public CallbackInterface {

public:
	MyCallbacks2() {}

	virtual void keyCallback(int key, int scancode, int action, int mods) {
		if (key == GLFW_KEY_R && action == GLFW_PRESS) {
			std::cout << "called back" << std::endl;
		}
	}
};
// END EXAMPLES

int main() {
Log::debug("Starting main");

	// WINDOW
	glfwInit();
	Window window(1080, 1080, "CPSC 453"); // can set callbacks at construction if desired

	GLDebug::enable();

	// SHADERS
	ShaderProgram shader("shaders/test.vert", "shaders/test.frag");

	// CALLBACKS
	std::shared_ptr<MyCallbacks> callbacks = std::make_shared<MyCallbacks>(shader);
	window.setCallbacks(callbacks); // can also update callbacks to new ones

	// GEOMETRY
	CPU_Geometry cpuGeom;
	GPU_Geometry gpuGeom;

	// vertices
	/*float T[3] = { 0, 1, 0 };
	float L[3] = { -1, -1, 0 };
	float R[3] = { 1, -1, 0 };*/

	/*float A[3] = { -0.99, -0.99, 0 };
	float B[3] = { -0.99, 0.99, 0 };
	float C[3] = { 0.99, 0.99, 0 };
	float D[3] = { 0.99, -0.99, 0 };*/

	/*float start[3] = { -0.5, 0, 0 };
	float end[3] = { 0.5, 0, 0 };*/

	/*cpuGeom.verts.push_back(glm::vec3(L[0], L[1], L[2]));
	cpuGeom.verts.push_back(glm::vec3(R[0], R[1], R[2]));
	cpuGeom.verts.push_back(glm::vec3(T[0], T[1], T[2]));*/

	//int m = 5;
	//glm::vec3 baseColour(0.05f, 0.05f, 0.05f);
	//Fractals Sierpinski(L, T, R, m, cpuGeom, gpuGeom, baseColour);
	//glm::vec3 baseColour(0.05f, 0.05f, 0.05f);
	//Fractals Sierpinski(L, T, R, m, cpuGeom, gpuGeom, baseColour);
//	glm::vec3 baseColour(0.f, 0.f, 0.f);
	//Fractals SquaresDiamonds(m, A, B, C, D, cpuGeom, gpuGeom, baseColour);

	//Fractals Koch(m, end, start, cpuGeom, gpuGeom);
	State state;
	State state2;
	Fractals Switcher(state2.m, state.m, cpuGeom, gpuGeom);

	
	//Fractals Switcher(state2.m, state.m, cpuGeom, gpuGeom);
	//void 
	//if (m > 0) {
	//	float LT[3] = { 0, , 0 };
	//	float L[3] = { -1, -1, 0 };
	//	float R[3] = { 1, -1, 0 };


	//	cpuGeom.verts.push_back(glm::vec3(L[0], L[1], L[2]));
	//	cpuGeom.verts.push_back(glm::vec3(R[0], R[1], R[2]));
	//	cpuGeom.verts.push_back(glm::vec3(T[0], T[1], T[2]));
	//}


	// colours (these should be in linear space)
	/*cpuGeom.cols.push_back(glm::vec3(1.f, 0.f, 0.f));
	cpuGeom.cols.push_back(glm::vec3(0.f, 1.f, 0.f));
	cpuGeom.cols.push_back(glm::vec3(0.f, 0.f, 1.f));*/
	

	//gpuGeom.setVerts(cpuGeom.verts);
	//gpuGeom.setCols(cpuGeom.cols);

	

	// RENDER LOOP
	while (!window.shouldClose()) {
		glfwPollEvents();
		if (!(state == callbacks->getState())) {
			cpuGeom.verts.clear();
			cpuGeom.cols.clear();
		
			Fractals Switcher(callbacks->getState2().m, callbacks->getState().m, cpuGeom, gpuGeom);
			//Fractals Dragon(callbacks->getState().m, cpuGeom, gpuGeom);
		}
		if (!(state2 == callbacks->getState2())) {
			cpuGeom.verts.clear();
			cpuGeom.cols.clear();
			Fractals Switcher(callbacks->getState2().m, callbacks->getState().m, cpuGeom, gpuGeom);
			//Fractals Dragon(callbacks->getState().m, cpuGeom, gpuGeom);
		}

		shader.use();
		gpuGeom.bind();

		glEnable(GL_FRAMEBUFFER_SRGB);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(1, 1, 1, 1);

		if (callbacks->getState2().m == 0) {
			glDrawArrays(GL_TRIANGLES, 0, cpuGeom.verts.size());
		}
		else if (callbacks->getState2().m == 1) {
			glDrawArrays(GL_LINES, 0, cpuGeom.verts.size());
		}
		else if (callbacks->getState2().m == 2) {
			glDrawArrays(GL_LINES, 0, cpuGeom.verts.size());
		}
		else if (callbacks->getState2().m == 3) {
			glDrawArrays(GL_LINE_STRIP, 0, cpuGeom.verts.size());
		}
		//glDrawArrays(GL_TRIANGLES, 0, cpuGeom.verts.size());
		//glDrawArrays(GL_LINES, 0, cpuGeom.verts.size());
		//glDrawArrays(GL_LINE_STRIP, 0, cpuGeom.verts.size());
		glDisable(GL_FRAMEBUFFER_SRGB); // disable sRGB for things like imgui

		window.swapBuffers();
	}

	glfwTerminate();
	return 0;
}
