
// gl_Color
// gl_FragColor
// gl_TexCoord[0].xy

// function easeInSine(x: number): number {
//   return 1 - Math.cos((x * Math.PI) / 2);
// }

uniform float time;
uniform float max_time;

const float pi = 3.1415926535897932384626433832795;

float easeInSine(float x)
{
    return 1.0 - cos((x * pi) / 2.0);
}

void main()
{
    vec2 coord = gl_TexCoord[0].xy;
    float cur_time = time;

    if (cur_time > max_time) {
        // cur_time = cur_time - (cur_time +  max_time);
		cur_time = 0.0;
    }

    gl_FragColor = vec4(gl_Color.xyz, easeInSine(coord.y) * (6.0*(max_time - cur_time)));
}
