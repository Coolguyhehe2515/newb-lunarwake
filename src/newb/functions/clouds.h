$input v_color0

#if NL_CLOUD_TYPE >= 2
  $input v_color1, v_color2, v_fogColor
#endif

#include <newb/config.h>

#include <bgfx_shader.sh>
#include <newb/main.sh>

uniform vec4 CameraPosition;

void main() {

  #if NL_CLOUD_TYPE == 0 || NL_CLOUD_TYPE == 1

    gl_FragColor = v_color0;

  #elif NL_CLOUD_TYPE == 2

    vec3 vDir = normalize(v_color0.xyz);

    vec3 cloudPos = v_color0.xyz;
    cloudPos.xz += CameraPosition.xz;

    /*
      Lunarwake rounded clouds.

      Keep these values local instead of using
      NL_CLOUD_PARAMS() so the shader does not
      depend on missing NL_CLOUD2_* defines.
    */

    const int CLOUD_STEPS = 16;
    const float CLOUD_THICKNESS = 1.0;
    const float CLOUD_RAIN_THICKNESS = 1.0;
    const float CLOUD_SPEED = 1.0;
    const vec2 CLOUD_SCALE = vec2(0.08);
    const float CLOUD_DENSITY = 1.0;
    const vec2 CLOUD_BOXINESS = vec2(0.35);

    vec4 color = renderCloudsRounded(
      vDir,
      cloudPos,
      v_color1.w,
      v_color2.w,
      v_color2.rgb,
      v_color1.rgb,
      CLOUD_STEPS,
      CLOUD_THICKNESS,
      CLOUD_RAIN_THICKNESS,
      CLOUD_SPEED,
      CLOUD_SCALE,
      CLOUD_DENSITY,
      CLOUD_BOXINESS
    );

    #ifdef NL_AURORA

      color += renderAurora(
        cloudPos,
        v_color2.w,
        v_color1.a,
        v_fogColor
      ) * (1.0 - 0.95 * color.a);

    #endif

    color.a *= v_color0.a;

    color.rgb = colorCorrection(color.rgb);

    gl_FragColor = color;

  #elif NL_CLOUD_TYPE == 3

    vec3 vDir = normalize(v_color0.xyz);

    vDir.xz *= 0.3 + v_color0.w;

    vec2 p = vDir.xz /
      (0.015 + 0.035 * abs(vDir.y));

    p += 0.035 * CameraPosition.xz;

    vec4 color = renderClouds(
      p,
      v_color2.w,
      v_color1.w,
      v_color2.rgb,
      v_color1.rgb,
      NL_CLOUD3_SCALE,
      NL_CLOUD3_SPEED,
      NL_CLOUD3_SHADOW
    );

    #ifdef NL_AURORA

      p.xy *= 34.7;

      color += renderAurora(
        p.xyy,
        v_color2.w,
        v_color1.w,
        v_fogColor
      ) * (1.0 - 0.95 * color.a);

    #endif

    color.a *= smoothstep(
      0.0,
      0.7,
      vDir.y
    );

    color.rgb = colorCorrection(color.rgb);

    gl_FragColor = color;

  #elif NL_CLOUD_TYPE >= 4

    gl_FragColor = v_color0;

  #endif
}
