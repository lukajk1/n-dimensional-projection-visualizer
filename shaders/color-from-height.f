#version 330 core

in vec3 fragColor;
in vec3 fragPos;

out vec4 FragColor;

void main() {
    //FragColor = vec4(fragColor, 1.0);
	float height = fragPos.y + .7;
	FragColor = vec4(height, height, height, 1.0);
}