#version 330 core

layout(location = 0) in vec4 position;

uniform mat4 rotation4;
uniform mat4 view;
uniform mat4 projection;

out vec3 fragColor;
out vec3 fragPos;

void main() {
    // 1. Apply 4D rotation
    vec4 rotated4D = rotation4 * position;
    
    // 2. Project from 4D to 3D (Perspective/W-Clipping)
    float distance = 3.0;
    float w = rotated4D.w;
    
    // Check for division by zero or clipping plane (optional guard)
    if (distance + w < 0.001) {
        gl_Position = vec4(0.0); // Clip if too close/behind the 4D camera
        fragColor = vec3(0.0);
        return;
    }
    
    // Perform 4D -> 3D Projection
    vec3 projected3D_World = rotated4D.xyz / (distance + w);
    
    // 3. Apply the 3D View (Camera) Transformation
    // Moves and rotates the 3D world relative to the camera
    vec4 projected3D_View = view * vec4(projected3D_World, 1.0);

    // 4. Apply the final 3D Projection to screen space
    gl_Position = projection * projected3D_View;
	fragPos = projected3D_World;
    
    // Color based on the 4th dimension (w)
    fragColor = vec3(0.5 + 0.5 * w);
}
// world > view > projection