#version 150

// these come from the programmable pipeline
uniform mat4 modelViewProjectionMatrix;

uniform vec4 globalColor;

in vec4 position;
in vec2 texcoord;
in vec4 normal;
in vec4 color;

// texture coordinates are sent to fragment shader
out vec2 texCoordVarying;

void main()
{
    texCoordVarying = texcoord;
    
    gl_Position = modelViewProjectionMatrix * position;
}

