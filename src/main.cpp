#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "stb_image.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <iostream>

#include "camera.h"
#include "mesh.h"
#include "model.h"
#include "shader_s.h"
#include "filesystem.h"
#include "vertex_data.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
GLuint setBuffers(const float* vertexData, size_t vertexDataSize, int vertexDim, GLuint& outVAO, GLuint& outVBO);
void drawImGuiElements();


// settings
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

const unsigned int IMGUI_WINDOW_WIDTH = 180;
const unsigned int IMGUI_WINDOW_HEIGHT = 300;

// camera
Camera camera(glm::vec3(0.0f, 1.0f, -5.0f));
float lastX = (float)SCR_WIDTH / 2.0;
float lastY = (float)SCR_HEIGHT / 2.0;

float camRotRadius = 4.0f; // rotation radius (adjustable via slider)
float camRotSpeed = 0.7f; // radians per second (adjustable via slider)
float camPos = 0.0f; // camera position around origin (0-1)

// global
float rotationRate = 0.7f;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;
// fps calculation
int frameCount = 0;
double lastFPSTime = 0.0;
double currentFPS = 0.0;


int main()
{
#pragma region setup
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Higher Dimensions", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // imgui setup
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
#pragma endregion

    glEnable(GL_DEPTH_TEST);
    stbi_set_flip_vertically_on_load(true);

    Shader* shader4D = new Shader("shaders/4d.v", "shaders/fragment.f");
    int vertexCount = 64;

    // cube VAO
    GLuint VAO_4D, VBO_4D;
    setBuffers(hypercubeVerts_4D, hypercubeVerts_4D_size, 4, VAO_4D, VBO_4D);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        frameCount++;
        double currentTime = glfwGetTime();
        if (currentTime - lastFPSTime >= 1.0) {  // Update every second
            currentFPS = frameCount / (currentTime - lastFPSTime);
            frameCount = 0;
            lastFPSTime = currentTime;
        }

        float angle = currentFrame * rotationRate;
        // 
        camera.Position.x = camRotRadius * cos(angle);
        camera.Position.z = camRotRadius * sin(angle);
        camera.LookAtTarget(glm::vec3(0.0f, 0.0f, 0.0f));

        // Activate shader
        shader4D->use();

        // 3D camera matrices
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

        // 4D rotation matrix (rotate in XW plane)
        glm::mat4 rotation4D = glm::mat4(1.0f);

        // for a rotation through ANY plane ij all you need is:
        // rotMatrix[i][i] = cos(angle)
        // rotMatrix[i][j] = -sin(angle)
        // rotMatrix[j][i] = sin(angle)
        // rotMatrix[j][j] = cos(angle)

        rotation4D[1][1] = cos(angle); 
        rotation4D[1][3] = -sin(angle);
        rotation4D[3][1] = sin(angle); 
        rotation4D[3][3] = cos(angle); 

        shader4D->setMat4("rotation4", rotation4D);
        shader4D->setMat4("view", view);
        shader4D->setMat4("projection", projection);

        // draw
        glBindVertexArray(VAO_4D);

        glLineWidth(4.5f);
        glDrawArrays(GL_LINES, 0, vertexCount);  

        glPointSize(12.0f);
        glDrawArrays(GL_POINTS, 0, vertexCount);  

        drawImGuiElements();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO_4D);
    glDeleteBuffers(1, &VBO_4D);
    delete shader4D;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}

GLuint setBuffers(const float* vertexData, size_t vertexDataSize, int vertexDim, GLuint& outVAO, GLuint& outVBO) {
    glGenVertexArrays(1, &outVAO);
    glGenBuffers(1, &outVBO);

    glBindVertexArray(outVAO);
    glBindBuffer(GL_ARRAY_BUFFER, outVBO);
    glBufferData(GL_ARRAY_BUFFER, vertexDataSize, vertexData, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0); // enable vertex attribute @ location 0
    glVertexAttribPointer(0, vertexDim, GL_FLOAT, GL_FALSE, vertexDim * sizeof(float), (void*)0);

    // unbind active vao
    glBindVertexArray(0);
    return outVAO;
}

void drawImGuiElements() {
    // imgui stuff
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::SetNextWindowSize(ImVec2(IMGUI_WINDOW_WIDTH, IMGUI_WINDOW_HEIGHT), ImGuiCond_Always);
    ImGui::SetNextWindowPos(ImVec2(SCR_WIDTH - IMGUI_WINDOW_WIDTH - 20, 20), ImGuiCond_Always);
    ImGui::Begin("ShaderDemos", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

    ImGui::Text("FPS: %.1f", currentFPS);
    ImGui::Spacing();

    // family
    ImGui::Text("Family");
    ImGui::Spacing();
    const char* shapesList[] = { "Hybercube", "Simplex", "Cross-Polytope" };
    int shapesIndex = 0;
    if (ImGui::Combo("##Object", &shapesIndex, shapesList, IM_ARRAYSIZE(shapesList)))
    {
        std::cout << "option was selected" << std::endl;
    }
    ImGui::Spacing();
    ImGui::Spacing();

    // dim
    ImGui::Text("Dimensions");
    ImGui::Spacing();
    const char* modelShaderNames[] = { "2", "3", "4", "5", "6", "7" };
    int currentModelShaderIndex = 0;
    if (ImGui::Combo("##Dimensions", &currentModelShaderIndex, modelShaderNames, IM_ARRAYSIZE(modelShaderNames)))
    {
        std::cout << "option was selected" << std::endl;
    }
    ImGui::Spacing();
    ImGui::Spacing();

    // Camera Zoom
    ImGui::Text("Camera Zoom");
    ImGui::Spacing();
    ImGui::SliderFloat("##Zoom", &camera.Zoom, 1.0f, 90.0f);
    ImGui::Spacing();
    ImGui::Spacing();

    // clean up
    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
