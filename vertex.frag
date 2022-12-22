#version 330 core


in vec2 fragPos;
in vec4 aColour;
uniform vec2 u_resolution;

vec3 getCircle(vec2 position, vec3 colour, float size)
{
    float circle = sqrt(pow(position.x,2.0) + pow(position.y,2.0));
    circle = smoothstep(size, size+0.003, 1.0-circle);
    
    return colour * circle;
}


void main() {
    vec2 st = gl_FragCoord.xy/u_resolution;
    vec3 canvas = vec4(0.0);

    vec3 circle = getCircle(st - fragPos, aColour, 0.9);
    
    canvas += circle;

    gl_FragColor = vec4(canvas, 1.0);
}