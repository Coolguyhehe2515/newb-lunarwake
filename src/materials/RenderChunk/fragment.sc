$input v_color0, v_color1, v_fog, v_refl, v_texcoord0, v_lightmapUV, v_extra, v_position, v_shadowDir

#include <bgfx_shader.sh>
#include <newb/main.sh>

uniform vec4 CameraPosition;

SAMPLER2D_AUTOREG(s_MatTexture);
SAMPLER2D_AUTOREG(s_SeasonsTexture);
SAMPLER2D_AUTOREG(s_LightMapTexture);

void main() {
  #if defined(DEPTH_ONLY_OPAQUE) || defined(DEPTH_ONLY) || defined(INSTANCING)
    gl_FragColor = vec4(1.0,1.0,1.0,1.0);
    return;
  #endif

  vec4 diffuse = texture2D(s_MatTexture, v_texcoord0);
  vec4 color = v_color0;

  #ifdef ALPHA_TEST
    if (diffuse.a < 0.6) {
      discard;
    }
  #endif

  #if defined(SEASONS) && (defined(OPAQUE) || defined(ALPHA_TEST))
    diffuse.rgb *= mix(vec3(1.0,1.0,1.0), texture2D(s_SeasonsTexture, v_color1.xy).rgb * 2.0, v_color1.z);
  #endif

  vec3 glow = nlGlow(s_MatTexture, v_texcoord0, v_extra.a);

  diffuse.rgb *= diffuse.rgb;

  #if defined(TRANSPARENT) && !(defined(SEASONS) || defined(RENDER_AS_BILLBOARDS))
    if (v_extra.b > 0.9) {
      diffuse.rgb = vec3_splat(1.0 - NL_WATER_TEX_OPACITY*(1.0 - diffuse.b*1.8));
      diffuse.a = color.a;
    }
  #else
    diffuse.a = 1.0;
  #endif

  diffuse.rgb *= color.rgb;
  diffuse.rgb += glow;

  if (v_extra.b > 0.9) {
    diffuse.rgb += v_refl.rgb*v_refl.a;
  } else if (v_refl.a > 0.0) {
    // reflective effect - only on xz plane
    float dy = abs(dFdy(v_extra.g));
    if (dy < 0.0002) {
      float mask = v_refl.a*(clamp(v_extra.r*10.0,8.2,8.8)-7.8);
      diffuse.rgb *= 1.0 - 0.6*mask;
      diffuse.rgb += v_refl.rgb*mask;
    }
  }

  #ifdef NL_PLAYER_SHADOW
    if (v_extra.b < 0.9 && v_shadowDir.z > 0.01) {
      float shDy = abs(dFdy(v_extra.g));
      if (shDy < 0.0002) {
        vec3 shGPos = v_position + CameraPosition.xyz;
        vec3 shFeet = CameraPosition.xyz;
        shFeet.y -= NL_PLAYER_EYE_HEIGHT;

        vec2 shRel = shGPos.xz - shFeet.xz;
        vec2 shFwd = v_shadowDir.xy;
        vec2 shRight = vec2(-shFwd.y, shFwd.x);

        float shLf = dot(shRel, shFwd);
        float shLr = dot(shRel, shRight);
        float shLen = v_shadowDir.z;

        if (shLf > -0.15 && shLf < shLen) {
          float shV = clamp(shLf/shLen, 0.0, 1.0);
          float shU = abs(shLr);

          float shMask = 0.0;
          if (shV < 0.22) {
            float legU = abs(shU - NL_PLAYER_SHADOW_LEG_GAP);
            shMask = step(legU, NL_PLAYER_SHADOW_LEG_WIDTH);
          } else if (shV < 0.75) {
            shMask = step(shU, NL_PLAYER_SHADOW_BODY_WIDTH);
          } else {
            shMask = step(shU, NL_PLAYER_SHADOW_HEAD_WIDTH);
          }

          float shFade = 1.0 - smoothstep(0.85, 1.0, shV);
          shFade *= smoothstep(-0.15, 0.0, shLf);
          diffuse.rgb *= 1.0 - shMask*shFade*NL_PLAYER_SHADOW_OPACITY;
        }
      }
    }
  #endif

  diffuse.rgb = mix(diffuse.rgb, v_fog.rgb, v_fog.a);

  diffuse.rgb = colorCorrection(diffuse.rgb);

  gl_FragColor = diffuse;
}
