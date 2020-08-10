#version 410

// these are from the programmable pipeline system
uniform mat4 modelViewProjectionMatrix;

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color; //attributeとしてvboMeshに格納されないと入力が来ない
layout (location = 2) in vec3 normal; //attributeとしてvboMeshに格納されないと入力が来ない
in float pointsize;


out vec4 vPosition;
out vec4 vColor;
out vec3 vNormal;
out float vScale;

void main()
{
    
    //--------------------varing変数
    vNormal = normal;
    vPosition = position;
    vColor = color;
    vScale = pointsize;
    
}
