#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader_m.h"
#include "camera.h"
#include "model.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 7.0f, 25.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

//constant position of head
glm::vec3 pos(0.0, 4.78732, 0.0f);

//local position of head
glm::vec3 headPos(0.0,6.946,0.0f);
//local position of body
glm::vec3 bodyPos(0.0, 4.78732-1.0, 0.0f);;
//local position of left leg
glm::vec3 LlegPos(0.0, 3.35326, -0.29189f);;
//local position of right leg
glm::vec3 RlegPos(0.0, 3.35326, 0.34412f);;
//local position of left hand
glm::vec3 LhandPos(0.0, 5.57974, -0.81956f);;
//local position of right hand
glm::vec3 RhandPos(0.0, 5.57974, 0.85876f);;

//head transformation matrix initialization
glm::mat4 headMat(1.0);
//body transformation matrix initialization
glm::mat4 bodyMat(1.0);
//left leg  transformation matrix initialization
glm::mat4 LlegMat(1.0);
//right leg transformation matrix initialization
glm::mat4 RlegMat(1.0);
//left handtransformation matrix initialization
glm::mat4 LhandMat(1.0);
//rigth hand transformation matrix initialization
glm::mat4 RhandMat(1.0);




// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;
//animation timer
float animTimer;
void calculateTransformation() {
	//setting body matrix to identity
	bodyMat = glm::mat4(1.0);
	//position in x axis
	bodyPos.x = sin(glfwGetTime())*10.;
	//position in y axis
	bodyPos.z = cos(glfwGetTime())*10.;
	//translating body matrix with it's position
	bodyMat = glm::translate(bodyMat, bodyPos);
	double dArray[16] = { 0.0 };
	
	
	//rotating the body with timer angle in y axis (aka verticle axis)
	bodyMat = glm::rotate(bodyMat, (float)glfwGetTime(), glm:: vec3(0.0, 1.0, 0.0));
	const float* pSource = (const float*)glm::value_ptr(bodyMat);
	for (int i = 0; i < 16; ++i) {
		dArray[i] = pSource[i];

		//cout << dArray[i] << "\n";
	}
	//translating head matrix with it's position and respect to body matrix...so it moves with body
	headMat = glm::translate(bodyMat,  headPos-pos);
	 pSource = (const float*)glm::value_ptr(headMat);
	for (int i = 0; i < 16; ++i) {
		dArray[i] = pSource[i];

		//cout << dArray[i] << "\n";
	}
	//translating left leg matrix
	LlegMat = glm::translate(bodyMat, LlegPos - pos);
	//rotating left leg matrix
	LlegMat = glm::rotate(LlegMat,(float)sin(animTimer), glm::vec3(0.0, 0.0, 1.0));

	 pSource = (const float*)glm::value_ptr(LlegMat);
	for (int i = 0; i < 16; ++i) {
		dArray[i] = pSource[i];

		//cout << dArray[i] << "\n";
	}
	//translating right leg matrix
	//rotating right leg matrix
	RlegMat = glm::translate(bodyMat, RlegPos - pos);
	RlegMat = glm::rotate(RlegMat, (float)sin(animTimer -3.1415), glm::vec3(0.0, 0.0, 1.0));

	 pSource = (const float*)glm::value_ptr(RlegMat);
	for (int i = 0; i < 16; ++i) {
		dArray[i] = pSource[i];

		//cout << dArray[i] << "\n";
	}
	//translating left hand matrix
	//rotating right hand matrix
	LhandMat = glm::translate(bodyMat, LhandPos - pos);
	LhandMat = glm::rotate(LhandMat, (float)sin(animTimer - 3.1415), glm::vec3(0.0, 0.0, 1.0));
	 pSource = (const float*)glm::value_ptr(LhandMat);
	for (int i = 0; i < 16; ++i) {
		dArray[i] = pSource[i];

		//cout << dArray[i] << "\n";
	}
	//translating right hand matrix
	//rotating  right hand matrix
	RhandMat = glm::translate(bodyMat, RhandPos - pos);
	RhandMat = glm::rotate(RhandMat, (float)sin(animTimer), glm::vec3(0.0, 0.0, 1.0));

	 pSource = (const float*)glm::value_ptr(RhandMat);
	for (int i = 0; i < 16; ++i) {
		dArray[i] = pSource[i];

		//cout << dArray[i] << "\n";
	}
	

	animTimer += 0.1;
}
int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Animation", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile shaders
	// -------------------------
	Shader ourShader("tree.vert", "tree.frag"); //tree shader
	Shader terrainShader("model.vert", "model.frag"); //ground shader
	Shader AnimationShader("animation.vert", "animation.frag"); //all body parts shader
	// load models
	// -----------
	
	Model ourModel("model.obj");//tree 3d model
	Model terrain("terrain.obj");//ground 3d model
	Model head("head.obj");//head 3d model
	Model body("body.obj");//body 3d model
	Model Lleg("Lleg.obj");//left leg 3d model
	Model Rleg("Rleg.obj");//right leg 3d model
	Model Lhand("Lhand.obj");//left hand 3d model
	Model Rhand("Rhand.obj");//right hand 3d model
	
	int tex  = ourModel.LoadTexture("tree.png");//loading tree texture
	int tex1 = ourModel.LoadTexture("terrain.png");//loading ground texture

	// draw in wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	// -----------
	
	while (!glfwWindowShouldClose(window))
	{
		calculateTransformation();//calculating all transformation of the scene
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.5f, 0.5f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);//projection matrix
		glm::mat4 view = camera.GetViewMatrix();//camera matrix aka view matrix
		glm::mat4 treeModelMatrix = glm::mat4(1.0f);
		glm::mat4 terrainModelMatrix = glm::mat4(1.0f);
		//////////////////////////////////////////

		ourShader.use();//tree shader use
		ourShader.setMat4("projection", projection);//tree projection
		ourShader.setMat4("view", view);//tree view matrix
		treeModelMatrix = glm::translate(treeModelMatrix, glm::vec3(0.0f, 0.0, 0.0f));//tree transformation matrix
		ourShader.setMat4("model", treeModelMatrix);
		ourShader.setFloat("time", glfwGetTime());//sending timerr to tree for animation in shader
		glActiveTexture(GL_TEXTURE0 ); 
		glUniform1i(glGetUniformLocation(ourShader.ID, "tex"),0);//sending texture to tree texture
		
		glBindTexture(GL_TEXTURE_2D, tex);
		ourModel.Draw(ourShader);//drawing tree



		///////////////////////////////////////////////

		terrainShader.use();//terrain shader use
		terrainShader.setMat4("projection", projection);//terrain projection
		terrainShader.setMat4("view", view);//terrain camera matrix
		terrainShader.setMat4("model", terrainModelMatrix);//terrain model matrix or transformation matrix

		glActiveTexture(GL_TEXTURE0);
		glUniform1i(glGetUniformLocation(terrainShader.ID, "tex"), 0);//sending texture to terrain shader

		glBindTexture(GL_TEXTURE_2D, tex1);

		terrain.Draw(terrainShader);//drawing terrain


		/////////////////////////////////////////////


		AnimationShader.use();//animation shader use
		AnimationShader.setMat4("projection", projection);//animated body projection
		AnimationShader.setMat4("view", view);//animated view matrix
		AnimationShader.setMat4("model", bodyMat);//animated body transformation matrix
	
		body.Draw(AnimationShader);//drawing body
		/////////////////////////////////////////////
		AnimationShader.use();
		
		AnimationShader.setMat4("model", headMat);//animated head transformation matrix

		head.Draw(AnimationShader);//drawing head
		/////////////////////////////////////////////
		AnimationShader.use();
		
		AnimationShader.setMat4("model", LlegMat);//animated left leg transformation matrix

		Lleg.Draw(AnimationShader);//drawing left leg
		/////////////////////////////////////////////
		AnimationShader.use();
		
		AnimationShader.setMat4("model", RlegMat);//animated right leg transformation matrix

		Rleg.Draw(AnimationShader);//drawing right leg
		/////////////////////////////////////////////
		AnimationShader.use();
		
		AnimationShader.setMat4("model", RhandMat);//animated right hand transformation matrix

		Rhand.Draw(AnimationShader);//drawing right hand
		/////////////////////////////////////////////
		AnimationShader.use();

		AnimationShader.setMat4("model", LhandMat);//animated left hand transformation matrix

		Lhand.Draw(AnimationShader);//drawing left hand
		/////////////////////////////////////////////



		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	
	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}