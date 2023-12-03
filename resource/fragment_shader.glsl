uniform float time;
uniform float max_time;

const float pi = 3.1415926535897932384626433832795;

float easeInSine(float x)
{
    return 1.0 - cos((x * pi) / 2.0);
}

float rand(vec2 co){
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}

void main()
{
    vec2 coord = gl_TexCoord[0].xy;
    float cur_time = time;

    if (cur_time > max_time) {
		cur_time = 0.0;
    }

    if (rand(coord) < 0.001) {
        gl_FragColor = vec4(gl_Color.xyz, 1);
    } else {
        gl_FragColor = vec4(gl_Color.xyz, easeInSine(coord.y) * ((max_time - cur_time)));
    }
}
