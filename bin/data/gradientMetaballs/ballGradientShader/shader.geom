#version 410


layout( points ) in;
layout( triangle_strip, max_vertices = 4 ) out;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelViewMatrix;

in float vScale[];
in vec4 vPosition[];
in vec4 vColor[];
in vec3 vNormal[];

out vec4 gsColor;
out vec3 gsNormal;
out vec4 gsPos;
out vec2 gsTexCoord;


void main() {
    vec4 center = vPosition[0];
    float scale = vScale[0];
    
    vec4 corners[4];
    
    center = vec4(center.xyz, 1.);
    corners[0] = center + vec4( -0.5, -0.5, 0, 0) * scale;
    corners[1] = center + vec4( -0.5,  0.5, 0, 0) * scale;
    corners[2] = center + vec4(  0.5, -0.5, 0, 0) * scale;
    corners[3] = center + vec4(  0.5,  0.5, 0, 0) * scale;
    corners[0] = modelViewProjectionMatrix * corners[0];
    corners[1] = modelViewProjectionMatrix * corners[1];
    corners[2] = modelViewProjectionMatrix * corners[2];
    corners[3] = modelViewProjectionMatrix * corners[3];
    
    vec2 texcoords[4];
    texcoords[0] = vec2(0, 0);
    texcoords[1] = vec2(1, 0);
    texcoords[2] = vec2(0, 1);
    texcoords[3] = vec2(1, 1);
    
    
    //---------------------------頂点値の設定
    gl_Position = corners[0];
    gsColor = vColor[0];
    gsTexCoord = texcoords[0];
    EmitVertex();
    
    gl_Position = corners[1];
    gsColor = vColor[0];
    gsTexCoord = texcoords[1];
    EmitVertex();

    gl_Position = corners[2];
    gsColor = vColor[0];
    gsTexCoord = texcoords[2];
    EmitVertex();
    
    gl_Position = corners[3];
    gsColor = vColor[0];
    gsTexCoord = texcoords[3];
    EmitVertex();

    EndPrimitive();
}
