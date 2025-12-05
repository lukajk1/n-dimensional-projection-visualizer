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
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

const unsigned int IMGUI_WINDOW_WIDTH = 180;
const unsigned int IMGUI_WINDOW_HEIGHT = 650;

// light
const glm::vec3 LIGHT_POSITION = glm::vec3(-1.0f, 1.0f, 1.0f);
const glm::vec3 LIGHT_SCALE = glm::vec3(.25f);

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = (float)SCR_WIDTH / 2.0;
float lastY = (float)SCR_HEIGHT / 2.0;
bool firstMouse = true;

float radius = 4.0f; // rotation radius (adjustable via slider)
float rotationRate = 0.035f; // radians per second (adjustable via slider)
float cameraPosition = 0.0f; // camera position around origin (0-1)
bool autoSpin = true; // toggle for automatic camera rotation

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "ShaderDemos", NULL, NULL);
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

    glEnable(GL_DEPTH_TEST);

    stbi_set_flip_vertically_on_load(true);
    Shader* cubeShader = new Shader("shaders/model.v", "shaders/model.f");

    // cube VAO
    unsigned int cubeVAO, cubeVBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, cubeVertices_size, &cubeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // Clear the screen
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // start camera per frame logic
        float angle;
        if (autoSpin)
        {
            // Auto-spin mode: use time-based rotation
            angle = currentFrame * rotationRate;
            cameraPosition = fmod(angle / (2.0f * 3.14159265f), 1.0f); // Update slider to match
        }
        else
        {
            // Manual mode: use slider position
            angle = cameraPosition * 2.0f * 3.14159265f; // Convert 0-1 to 0-2π
        }

        float camX = sin(angle) * radius;
        float camZ = cos(angle) * radius;

        // 1. Set the orbiting position
        camera.Position = glm::vec3(camX, 1.0f, camZ);

        // 2. Force the camera to look at the origin (0, 0, 0)
        // This calls the new LookAtTarget method which updates Yaw, Pitch, and Front vector.
        camera.LookAtTarget(glm::vec3(0.0f, 0.0f, 0.0f));

        // Setup common view and projection matrices
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

        // Activate shader
        cubeShader->use();

        // set matrix uniforms for model
        cubeShader->setMat4("projection", projection);
        cubeShader->setMat4("view", view);
        
        // set up matrix
        glm::mat4 modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.2f, 0.2f, 0.25f));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.7f, 0.7f, 0.7f));
        cubeShader->setMat4("model", modelMatrix);

        // Draw the cube
        glBindVertexArray(cubeVAO);
        glm::mat4 cubeModel = glm::mat4(1.0f);
        cubeShader->setMat4("model", cubeModel);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //ImGui_ImplOpenGL3_NewFrame();
        //ImGui_ImplGlfw_NewFrame();
        //ImGui::NewFrame();

        //// Shader Selection Window
        //ImGui::SetNextWindowSize(ImVec2(IMGUI_WINDOW_WIDTH, IMGUI_WINDOW_HEIGHT), ImGuiCond_Always);
        //ImGui::SetNextWindowPos(ImVec2(SCR_WIDTH - IMGUI_WINDOW_WIDTH - 20, 20), ImGuiCond_Always);
        //ImGui::Begin("ShaderDemos", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

        //// Model selection dropdown
        //ImGui::Text("Model");
        //ImGui::Spacing();
        //if (ImGui::Combo("##Model", &currentModelIndex, modelNames, IM_ARRAYSIZE(modelNames)))
        //{
        //    // Model selection changed, reload the model
        //    delete ourModel;
        //    ourModel = new Model(modelPaths[currentModelIndex]);
        //    std::cout << "Switched to model: " << modelNames[currentModelIndex] << std::endl;
        //}
        //ImGui::Spacing();
        //ImGui::Spacing();

        //// Model shader dropdown
        //int previousModelShaderIndex = currentModelShaderIndex;

        //ImGui::Text("Model Shader");
        //ImGui::Spacing();
        //if (ImGui::Combo("##ModelShader", &currentModelShaderIndex, modelShaderNames, IM_ARRAYSIZE(modelShaderNames)))
        //{
        //    // Shader selection changed, reload the shader
        //    delete modelShader;
        //    modelShader = new Shader("Shaders/model/model.v", modelShaderPaths[currentModelShaderIndex]);
        //    std::cout << "Switched to model shader: " << modelShaderNames[currentModelShaderIndex] << std::endl;
        //}
        //ImGui::Spacing();
        //ImGui::Spacing();
        //ImGui::End();

        //// imgui draw
        //ImGui::Render();
        //ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteBuffers(1, &cubeVBO);
    delete cubeShader;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
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
