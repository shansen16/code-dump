#version 330 core


in vec4 colour;
in vec4 position;
uniform vec2 u_resolution;

vec4 getCircle(vec2 position, vec4 colour, float size)
{
    float circle = sqrt(pow(position.x,2.0) + pow(position.y,2.0));
    circle = smoothstep(size, size+0.003, 1.0-circle);
    
    return colour * circle;
}


void main() {
    vec2 st = gl_FragCoord.xy/u_resolution;
    vec4 canvas = vec4(0.0);

    vec4 circle = getCircle(st - position.xy, colour, 0.9);
    
    canvas += circle;

    gl_FragColor = canvas;
}