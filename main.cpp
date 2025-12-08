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
#include <map>
#include <utility>

#include "camera.h"
#include "mesh.h"
#include "model.h"
#include "shader_s.h"
#include "filesystem.h"
#include "vertex_data.h"
#include "ndim_object.h"
#include "hypercube_objects.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void setImGuiElements();


// settings
unsigned int SCR_WIDTH = 1280;
unsigned int SCR_HEIGHT = 720;

const unsigned int IMGUI_WINDOW_WIDTH = 180;
const unsigned int IMGUI_WINDOW_HEIGHT = 400;

// camera
Camera camera(glm::vec3(0.0f, 1.0f, -5.0f));
float lastX = (float)SCR_WIDTH / 2.0;
float lastY = (float)SCR_HEIGHT / 2.0;

float camRotRadius = 4.0f; // rotation radius (adjustable via slider)
float camRotSpeed = 0.7f; // radians per second (adjustable via slider)
float camPos = 0.0f; // camera position around origin (0-1)

// global
float rotationRate = 0.7f;
float EDGE_THICKNESS = 8.0f;
float VERTEX_SIZE = 14.0f;

// timing
float timeRatio = 1.0f;
float deltaTime = 0.0f;
float lastFrame = 0.0f;
// fps calculation
int frameCount = 0;
double lastFPSTime = 0.0;
double currentFPS = 0.0;

NDimObjectData* currentObject;
int shapesIndex = 0;
int currentDimensionIndex = 1;  // Dropdown index (0-6 maps to dimensions 2-8)

// Map to store objects by (shapeType, dimension) key
std::map<std::pair<int, int>, NDimObjectData*> objectMap;

// Helper function to update current object based on shape and dimension selection
void updateCurrentObject() {
    int actualDimension = currentDimensionIndex + 2;  // Convert dropdown index to actual dimension (0->2, 1->3, etc.)
    auto key = std::make_pair(shapesIndex, actualDimension);
    auto it = objectMap.find(key);
    if (it != objectMap.end()) {
        currentObject = it->second;
    } else {
        std::cout << "No object found for shape " << shapesIndex << ", dimension " << actualDimension << std::endl;
    }
}

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
    glfwSetScrollCallback(window, scroll_callback);
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
    hypercube2D.init();
    hypercube3D.init();
    hypercube4D.init();
    hypercube5D.init();
    hypercube6D.init();
    hypercube7D.init();
    hypercube8D.init();

    simplex3D.init();

    // Populate object map with (shapeType, dimension) -> object
    // Shape types: 0 = Hypercube, 1 = Hypersphere, 2 = Simplex, 3 = Cross-Polytope
    objectMap[{0, 2}] = &hypercube2D;
    objectMap[{0, 3}] = &hypercube3D;
    objectMap[{0, 4}] = &hypercube4D;
    objectMap[{0, 5}] = &hypercube5D;
    objectMap[{0, 6}] = &hypercube6D;
    objectMap[{0, 7}] = &hypercube7D;
    objectMap[{0, 8}] = &hypercube8D;
    objectMap[{2, 3}] = &simplex3D;

    // Set initial object to 3D hypercube
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

        float angle = currentFrame * rotationRate * timeRatio;
        camera.Position.x = camRotRadius * cos(angle);
        camera.Position.z = camRotRadius * sin(angle);
        camera.LookAtTarget(glm::vec3(0.0f, 0.0f, 0.0f));

        // imgui pass 
        setImGuiElements();

        // Activate shader
        currentObject->shader->use();

        // 3D camera matrices
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

        // Build rotation matrix using object's method
        // Use a static buffer large enough for any dimension we support (up to 8D = 64 floats)
        static float rotationMatrix[64];
        currentObject->buildRotationMatrix(rotationMatrix, currentFrame * timeRatio);

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
    hypercube8D.cleanup();
    simplex3D.cleanup();

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
        updateCurrentObject();
    }
    ImGui::Spacing();
    ImGui::Spacing();

    // dim
    ImGui::Text("Dimensions");
    ImGui::Spacing();
    const char* modelShaderNames[] = { "2", "3", "4", "5", "6", "7", "8" };
    if (ImGui::Combo("##Dimensions", &currentDimensionIndex, modelShaderNames, IM_ARRAYSIZE(modelShaderNames)))
    {
        updateCurrentObject();
    }
    ImGui::Spacing();
    ImGui::Spacing();

    // Time Speed
    ImGui::Text("Time Speed");
    ImGui::Spacing();
    ImGui::SliderFloat("##TimeRatio", &timeRatio, 0.0f, 2.0f, "%.1f");
    ImGui::Spacing();
    ImGui::Spacing();

    // Camera Zoom
    ImGui::Text("Camera Zoom");
    ImGui::Spacing();
    float inverseZoom = (91.0f - camera.Zoom) / 10.0f;  // Invert the range and scale to 1-9
    if (ImGui::SliderFloat("##Zoom", &inverseZoom, 1.0f, 9.0f, "%.1f")) {
        camera.Zoom = 91.0f - inverseZoom * 10.0f;  // Convert back to actual zoom
    }
    ImGui::Spacing();
    ImGui::Spacing();

    // Edge Thickness
    ImGui::Text("Edge Thickness");
    ImGui::Spacing();
    ImGui::SliderFloat("##EdgeThickness", &EDGE_THICKNESS, 0.1f, 30.0f, "%.1f px");
    ImGui::Spacing();
    ImGui::Spacing();

    // Vertex Size
    ImGui::Text("Vertex Size");
    ImGui::Spacing();
    ImGui::SliderFloat("##VertexSize", &VERTEX_SIZE, 0.1f, 30.0f, "%.1f px");
    ImGui::Spacing();
    ImGui::Spacing();

}


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    // Adjust camera zoom based on scroll direction
    // yoffset > 0 means scroll up (zoom in), yoffset < 0 means scroll down (zoom out)
    camera.Zoom -= (float)yoffset * 3.0f;

    // Clamp zoom to valid range (1-90, which maps to slider display of 9-1)
    if (camera.Zoom < 1.0f)
        camera.Zoom = 1.0f;
    if (camera.Zoom > 90.0f)
        camera.Zoom = 90.0f;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);

    // Update global screen dimensions
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
}
