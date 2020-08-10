#version 410
#define PI 3.14159265359

uniform vec4 globalColor;


in vec4 gsColor;
in vec3 gsNormal;
in vec2 gsTexCoord;

out vec4 outputColor;

float func(float _x) {
    return 1.0 - pow(abs(sin(PI*_x/2.0)), 3.5);
}

float func2(float _x) {
    return pow(cos(PI*_x*0.5), 5.5);
}

float func3(float _x) {
    return 1.-pow(abs(_x), 3.5);
}

 
void main(){
    
    vec2 uv = gsTexCoord;
    
    uv *= 2.;
    float x = min(length(uv-1), 1);
    float pct = func2(x);
    
    vec3 col = vec3(1.);
    float alph = pct;
    alph = clamp(alph, 0,1) * 0.2;
    
    outputColor = vec4(col, alph);
    
}
