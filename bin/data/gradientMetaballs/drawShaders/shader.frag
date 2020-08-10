#version 150

#define PI 3.14159265359

// this comes from the vertex shader
in vec2 texCoordVarying;

// this is the output of the fragment shader
out vec4 outputColor;

uniform vec4 globalColor;
uniform vec2 u_resolution;
uniform float u_time;
uniform sampler2DRect tex0;

uniform float u_threshold = 1.;

void main() {
    
    vec2 uv = texCoordVarying.xy;
    
    float pct = texture(tex0, uv).r;
    pct = step(u_threshold, pct);
    
    vec3 col = vec3(0);
    
    col += pct;
    
    
    outputColor = vec4(col*globalColor.rgb, pct);
    
}













