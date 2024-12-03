// fragment_lit.glsl
uniform sampler2D diffuse;
uniform vec2 lightPosition;
uniform int spotlight;

varying vec2 texCoordVar;
varying vec2 varPosition;

float attenuate(float dist, float a, float b)
{
     return 1.0 / (1.0 + (a * dist) + (b * dist  * dist));
}

void main()
{
    if(spotlight == 1){
        // The brightness is directly based on the distance between the light source's
        // location and the pixel's location
        float brightness = attenuate(distance(lightPosition, varPosition), 1.0, 0.0);
        vec4 color = texture2D(diffuse, texCoordVar);
        gl_FragColor = vec4(color.rgb * brightness, color.a);
    }else{
        //Don't use spotlight use gray scale
        vec4 colour = texture2D(diffuse, texCoordVar);
        vec3 luminance = vec3(dot(vec3(0.2126, 0.7152, 0.0722), colour.rgb));
        gl_FragColor = vec4(luminance, colour.a);
    }
}
