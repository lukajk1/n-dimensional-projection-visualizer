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


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
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

    // Define default rotation for 5D hypercube
    RotationPlane hypercube5D_rotations[] = {
        {1, 3, 0.5f},  // YW plane rotation at 0.5 rad/s
        {0, 4, 0.3f}   // XV plane rotation at 0.3 rad/s
    };

    // Allocate space for 5x5 identity matrix
    static float identity5D[25];

    // Create 5D hypercube object data
    NDimObjectData hypercube5D = {
        hypercubeVerts_5D,           // vertices
        hypercubeVerts_5D_size,      // vertexDataSize
        160,                         // vertexCount (5D hypercube has 32 vertices, 80 edges, 160 vertices for GL_LINES)
        5,                           // dimensions
        hypercube5D_rotations,       // defaultRotationPlanes
        2,                           // numRotationPlanes
        identity5D,                  // identityMatrix (will be initialized)
        0,                           // VAO (will be set by setupBuffers)
        0,                           // VBO (will be set by setupBuffers)
        nullptr,                     // shader (will be initialized by initShader)
        "5D Hypercube",              // name
        "shaders/5d.v",              // shaderVertPath
        "shaders/fragment.f"         // shaderFragPath
    };

    // Initialize the object
    hypercube5D.initIdentityMatrix();
    hypercube5D.setupBuffers();
    hypercube5D.initShader();

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
        hypercube5D.shader->use();

        // 3D camera matrices
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

        // Build rotation matrix using object's method
        // can't just assign an array to the return of the function since it has to be genericized and I don't want to deal with that
        float rotation5D[25];
        hypercube5D.buildRotationMatrix(rotation5D, currentFrame);

        hypercube5D.shader->setFloatArray("rotationMat", rotation5D, 25);
        hypercube5D.shader->setMat4("view", view);
        hypercube5D.shader->setMat4("projection", projection);

        // draw
        glBindVertexArray(hypercube5D.VAO);

        glLineWidth(4.5f);
        glDrawArrays(GL_LINES, 0, hypercube5D.vertexCount);

        glPointSize(12.0f);
        glDrawArrays(GL_POINTS, 0, hypercube5D.vertexCount);

        drawImGuiElements();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    hypercube5D.cleanup();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}

void drawImGuiElements() {
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
    int currentModelShaderIndex = 2;
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
