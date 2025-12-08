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
#include "ndim_object.h"
#include "hypercube_objects.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void setImGuiElements();


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

NDimObjectData* currentObject;
int shapesIndex = 0;
int currentDimensionIndex = 1;

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

    // Initialize all hypercube objects
    hypercube2D.initIdentityMatrix();
    hypercube2D.setupBuffers();
    hypercube2D.initShader();

    hypercube3D.initIdentityMatrix();
    hypercube3D.setupBuffers();
    hypercube3D.initShader();

    hypercube4D.initIdentityMatrix();
    hypercube4D.setupBuffers();
    hypercube4D.initShader();

    hypercube5D.initIdentityMatrix();
    hypercube5D.setupBuffers();
    hypercube5D.initShader();

    hypercube6D.initIdentityMatrix();
    hypercube6D.setupBuffers();
    hypercube6D.initShader();

    hypercube7D.initIdentityMatrix();
    hypercube7D.setupBuffers();
    hypercube7D.initShader();

    // Set initial object to 3D
    currentObject = &hypercube3D;

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
        /*camera.Position.x = camRotRadius * cos(angle);
        camera.Position.z = camRotRadius * sin(angle);*/
        camera.LookAtTarget(glm::vec3(0.0f, 0.0f, 0.0f));

        // imgui pass 
        setImGuiElements();

        // Activate shader
        currentObject->shader->use();

        // 3D camera matrices
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

        // Build rotation matrix using object's method
        // Use a static buffer large enough for any dimension we support (up to 7D = 49 floats)
        static float rotationMatrix[49];
        currentObject->buildRotationMatrix(rotationMatrix, currentFrame);

        currentObject->shader->setFloatArray("rotationMat", rotationMatrix, currentObject->matrixSize());
        currentObject->shader->setFloat("scale", currentObject->scale);
        currentObject->shader->setMat4("view", view);
        currentObject->shader->setMat4("projection", projection);

        // draw
        currentObject->draw();

        // draw imgui
        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    hypercube2D.cleanup();
    hypercube3D.cleanup();
    hypercube4D.cleanup();
    hypercube5D.cleanup();
    hypercube6D.cleanup();
    hypercube7D.cleanup();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}

void setImGuiElements() {
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
    const char* shapesList[] = { "Hypercube", "Hypersphere", "Simplex", "Cross-Polytope" };
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
    if (ImGui::Combo("##Dimensions", &currentDimensionIndex, modelShaderNames, IM_ARRAYSIZE(modelShaderNames)))
    {
        // Switch between objects based on selection
        if (currentDimensionIndex == 0) {  // 2D
            currentObject = &hypercube2D;
        }
        else if (currentDimensionIndex == 1) {  // 3D
            currentObject = &hypercube3D;
        }
        else if (currentDimensionIndex == 2) {  // 4D
            currentObject = &hypercube4D;
        }
        else if (currentDimensionIndex == 3) {  // 5D
            currentObject = &hypercube5D;
        }
        else if (currentDimensionIndex == 4) {  // 6D
            currentObject = &hypercube6D;
        }
        else if (currentDimensionIndex == 5) {  // 7D
            currentObject = &hypercube7D;
        }
        // Can add more dimensions here as they're implemented
    }
    ImGui::Spacing();
    ImGui::Spacing();

    // Camera Zoom
    ImGui::Text("Camera Zoom");
    ImGui::Spacing();
    ImGui::SliderFloat("##Zoom", &camera.Zoom, 1.0f, 90.0f);
    ImGui::Spacing();
    ImGui::Spacing();



}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
