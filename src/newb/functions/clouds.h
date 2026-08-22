#ifndef CLOUDS_H
#define CLOUDS_H

#include "detection.h"
#include "noise.h"
#include "sky.h"


// ==========================================================
// SIMPLE CLOUDS
// ==========================================================

float cloudNoise2D(vec2 p, highp float t, float rain) {
  t *= NL_CLOUD1_SPEED;
  p += t;
  p.y += 3.0 * sin(0.3 * p.x + 0.1 * t);

  vec2 p0 = floor(p);
  vec2 u = p - p0;
  u *= u * (3.0 - 2.0 * u);

  vec2 v = 1.0 - u;

  float n = mix(
    mix(
      rand(p0),
      rand(p0 + vec2(1.0, 0.0)),
      u.x
    ),
    mix(
      rand(p0 + vec2(0.0, 1.0)),
      rand(p0 + vec2(1.0, 1.0)),
      u.x
    ),
    u.y
  );

  n *=
    0.5 +
    0.5 *
    sin(p.x * 0.6 - 0.5 * t) *
    sin(p.y * 0.6 + 0.8 * t);

  n = min(n * (1.0 + rain), 1.0);

  return n * n;
}


vec4 renderCloudsSimple(
  nl_skycolor skycol,
  vec3 pos,
  highp float t,
  float rain
) {
  pos.xz *= NL_CLOUD1_SCALE;

  float d =
    cloudNoise2D(
      pos.xz,
      t,
      rain
    );

  vec4 col =
    vec4(
      skycol.horizonEdge +
      skycol.zenith,
      smoothstep(
        0.1,
        0.6,
        d
      )
    );

  col.rgb +=
    1.5 *
    dot(
      col.rgb,
      vec3(0.3, 0.4, 0.3)
    ) *
    smoothstep(
      0.6,
      0.2,
      d
    ) *
    col.a;

  col.rgb *=
    1.0 -
    0.8 *
    rain;

  return col;
}


// ==========================================================
// ROUNDED CLOUDS
// ==========================================================

float cloudDf(
  vec3 pos,
  float rain,
  vec2 boxiness
) {
  boxiness *= 0.999;

  vec2 p0 =
    floor(pos.xz);

  vec2 u =
    max(
      (
        pos.xz -
        p0 -
        boxiness.x
      ) /
      (
        1.0 -
        boxiness.x
      ),
      0.0
    );

  u *=
    u *
    (
      3.0 -
      2.0 * u
    );

  vec4 r =
    vec4(
      rand(p0),
      rand(p0 + vec2(1.0, 0.0)),
      rand(p0 + vec2(1.0, 1.0)),
      rand(p0 + vec2(0.0, 1.0))
    );

  r =
    smoothstep(
      0.1001 + 0.2 * rain,
      0.1 + 0.2 * rain * rain,
      r
    );

  float n =
    mix(
      mix(r.x, r.y, u.x),
      mix(r.w, r.z, u.x),
      u.y
    );

  n *=
    1.0 -
    1.5 *
    smoothstep(
      boxiness.y,
      2.0 - boxiness.y,
      2.0 * abs(pos.y - 0.5)
    );

  n =
    max(
      1.25 *
      (n - 0.2),
      0.0
    );

  n *=
    n *
    (
      3.0 -
      2.0 * n
    );

  return n;
}


vec4 renderCloudsRounded(
  vec3 vDir,
  vec3 vPos,
  float rain,
  float time,
  vec3 horizonCol,
  vec3 zenithCol,
  const int steps,
  const float thickness,
  const float thickness_rain,
  const float speed,
  const vec2 scale,
  const float density,
  const vec2 boxiness
) {
  float height =
    7.0 *
    mix(
      thickness,
      thickness_rain,
      rain
    );

  float stepsf =
    float(steps);

  vec3 deltaP;

  deltaP.y = 1.0;

  deltaP.xz =
    height *
    scale *
    vDir.xz /
    (
      0.02 +
      0.98 *
      abs(vDir.y)
    );

  vec3 pos;

  pos.y = 0.0;

  pos.xz =
    scale *
    (
      vPos.xz +
      vec2(1.0, 0.5) *
      (
        time *
        speed
      )
    );

  pos += deltaP;

  deltaP /=
    -stepsf;

  vec2 d =
    vec2(
      0.0,
      1.0
    );

  for (int i = 1; i <= steps; i++) {

    float m =
      cloudDf(
        pos,
        rain,
        boxiness
      );

    d.x += m;

    d.y =
      mix(
        d.y,
        pos.y,
        m
      );

    pos +=
      deltaP;
  }

  d.x *=
    smoothstep(
      0.03,
      0.1,
      d.x
    );

  d.x /=
    (
      stepsf /
      density
    ) +
    d.x;

  if (vPos.y < 0.0) {
    d.y =
      1.0 -
      d.y;
  }

  vec4 col =
    vec4(
      zenithCol +
      horizonCol,
      d.x
    );

  col.rgb +=
    dot(
      col.rgb,
      vec3(0.3, 0.4, 0.3)
    ) *
    d.y *
    d.y;

  col.rgb *=
    1.0 -
    0.8 *
    rain;

  return col;
}


// ==========================================================
// REALISTIC / VORONOI CLOUDS
// ==========================================================

float cloudsNoiseVr(
  vec2 p,
  float t
) {
  float n =
    fastVoronoi2(
      p + t,
      1.8
    );

  n *=
    fastVoronoi2(
      3.0 * p + t,
      1.5
    );

  n *=
    fastVoronoi2(
      9.0 * p + t,
      0.4
    );

  n *=
    fastVoronoi2(
      27.0 * p + t,
      0.1
    );

  return n * n;
}


vec4 renderClouds(
  vec2 p,
  float t,
  float rain,
  vec3 horizonCol,
  vec3 zenithCol,
  const vec2 scale,
  const float velocity,
  const float shadow
) {
  p *= scale;

  t *= velocity;

  float a =
    cloudsNoiseVr(
      p,
      t
    );

  float b =
    cloudsNoiseVr(
      p +
      NL_CLOUD3_SHADOW_OFFSET *
      scale,
      t
    );

  p =
    1.4 *
    p.yx +
    vec2(
      7.8,
      9.2
    );

  t *= 0.5;

  float c =
    cloudsNoiseVr(
      p,
      t
    );

  float d =
    cloudsNoiseVr(
      p +
      NL_CLOUD3_SHADOW_OFFSET *
      scale,
      t
    );

  vec2 tr =
    vec2(
      0.6,
      0.7
    ) -
    0.12 *
    rain;

  a =
    smoothstep(
      tr.x,
      tr.y,
      a
    );

  c =
    smoothstep(
      tr.x,
      tr.y,
      c
    );

  b *=
    smoothstep(
      0.2,
      0.8,
      b
    );

  d *=
    smoothstep(
      0.2,
      0.8,
      d
    );

  vec4 col;

  col.a =
    a +
    c *
    (
      1.0 -
      a
    );

  col.rgb =
    horizonCol +
    horizonCol.ggg;

  col.rgb =
    mix(
      col.rgb,
      0.5 *
      (
        zenithCol +
        zenithCol.ggg
      ),
      shadow *
      mix(
        b,
        d,
        c
      )
    );

  col.rgb *=
    1.0 -
    0.7 *
    rain;

  return col;
}


// ==========================================================
// LUNARWAKE CLOUDS
// Lightweight volumetric cloud system
// ==========================================================

float lunarWakeNoise(
  vec2 p
) {
  vec2 i =
    floor(p);

  vec2 f =
    fract(p);

  f *=
    f *
    (
      3.0 -
      2.0 * f
    );

  float a =
    rand(i);

  float b =
    rand(
      i +
      vec2(
        1.0,
        0.0
      )
    );

  float c =
    rand(
      i +
      vec2(
        0.0,
        1.0
      )
    );

  float d =
    rand(
      i +
      vec2(
        1.0,
        1.0
      )
    );

  return mix(
    mix(a, b, f.x),
    mix(c, d, f.x),
    f.y
  );
}


float lunarWakeFBM(
  vec2 p
) {
  float n = 0.0;

  n +=
    lunarWakeNoise(
      p
    ) *
    0.55;

  p *= 2.03;

  n +=
    lunarWakeNoise(
      p
    ) *
    0.27;

  p *= 2.07;

  n +=
    lunarWakeNoise(
      p
    ) *
    0.13;

  p *= 2.11;

  n +=
    lunarWakeNoise(
      p
    ) *
    0.05;

  return n;
}


float lunarWakeDensity(
  vec3 pos,
  float rain
) {
  vec2 p =
    pos.xz *
    NL_CLOUD4_SCALE;

  float base =
    lunarWakeFBM(
      p
    );

  float detail =
    lunarWakeNoise(
      p *
      2.7
    );

  float shape =
    mix(
      base,
      base * 0.72 +
      detail * 0.28,
      0.45
    );

  float threshold =
    NL_CLOUD4_THRESHOLD -
    0.08 *
    rain;

  float density =
    smoothstep(
      threshold -
      NL_CLOUD4_SOFTNESS,
      threshold +
      NL_CLOUD4_SOFTNESS,
      shape
    );

  // Soft vertical cloud profile.
  float vertical =
    1.0 -
    abs(
      pos.y
    );

  vertical =
    smoothstep(
      0.0,
      0.35,
      vertical
    );

  density *=
    vertical;

  return density;
}


vec4 renderCloudsLunarWake(
  vec3 skycol,
  vec3 pos,
  float time,
  float rain
) {
  // Cloud movement.
  vec3 rayPos =
    pos;

  rayPos.xz +=
    vec2(
      time *
      NL_CLOUD4_SPEED,
      time *
      NL_CLOUD4_SPEED *
      0.63
    );

  // Keep the volume compact.
  rayPos.xz *=
    0.055;

  // Small vertical volume.
  rayPos.y *=
    0.22;

  const int STEPS = 8;

  vec3 rayStep =
    vec3(
      0.0,
      0.12,
      0.0
    );

  float densitySum =
    0.0;

  float lightSum =
    0.0;

  vec3 samplePos =
    rayPos;

  for (int i = 0; i < STEPS; i++) {

    float d =
      lunarWakeDensity(
        samplePos,
        rain
      );

    densitySum +=
      d *
      (
        1.0 -
        densitySum
      );

    // Cheap internal lighting.
    float light =
      0.55 +
      0.45 *
      smoothstep(
        -0.4,
        0.8,
        samplePos.y
      );

    lightSum +=
      d *
      light;

    samplePos +=
      rayStep;
  }

  float opacity =
    densitySum *
    NL_CLOUD4_DENSITY *
    NL_CLOUD4_OPACITY;

  opacity =
    clamp(
      opacity,
      0.0,
      1.0
    );

  float lighting =
    0.0;

  if (densitySum > 0.0001) {
    lighting =
      lightSum /
      (
        densitySum *
        float(STEPS)
      );
  }

  vec3 cloudColor =
    skycol *
    NL_CLOUD4_BRIGHTNESS;

  // Slightly brighten the cloud tops.
  cloudColor *=
    0.78 +
    0.22 *
    lighting;

  // Cheap rain darkening.
  cloudColor *=
    1.0 -
    0.25 *
    rain;

  // Saturation control.
  float luminance =
    dot(
      cloudColor,
      vec3(
        0.299,
        0.587,
        0.114
      )
    );

  cloudColor =
    mix(
      vec3_splat(luminance),
      cloudColor,
      NL_CLOUD4_SATURATION
    );

  return vec4(
    cloudColor,
    opacity
  );
}


// ==========================================================
// AURORA
// ==========================================================

#ifdef NL_AURORA

vec4 renderAurora(
  vec3 p,
  float t,
  float rain,
  vec3 FOG_COLOR
) {
  t *=
    NL_AURORA_VELOCITY;

  p.xz *=
    NL_AURORA_SCALE;

  p.xz +=
    0.05 *
    sin(
      p.x * 4.0 +
      20.0 * t
    );

  float d0 =
    sin(
      p.x * 0.1 +
      t +
      sin(
        p.z * 0.2
      )
    );

  float d1 =
    sin(
      p.z * 0.1 -
      t +
      sin(
        p.x * 0.2
      )
    );

  float d2 =
    sin(
      p.z * 0.1 +
      1.0 *
      sin(
        d0 +
        d1 * 2.0
      ) +
      d1 * 2.0 +
      d0
    );

  d0 *= d0;
  d1 *= d1;
  d2 *= d2;

  d2 =
    d0 /
    (
      1.0 +
      d2 /
      NL_AURORA_WIDTH
    );

  float mask =
    (
      1.0 -
      0.8 * rain
    ) *
    max(
      1.0 -
      4.0 *
      max(
        FOG_COLOR.b,
        FOG_COLOR.g
      ),
      0.0
    );

  return
    vec4(
      NL_AURORA *
      mix(
        NL_AURORA_COL1,
        NL_AURORA_COL2,
        d1
      ),
      1.0
    ) *
    d2 *
    mask;
}

#endif


// ==========================================================
// CLOUD / AURORA REFLECTION
// ==========================================================

vec4 nlCloudAuroraReflection(
  nl_skycolor skycol,
  nl_environment env,
  vec3 viewDir,
  vec3 wPos,
  vec3 CAMERA_POS,
  highp float t
) {
  vec2 cloudPos =
    wPos.xz;

  cloudPos +=
    (
      187.0 -
      (
        wPos.y +
        CAMERA_POS.y
      )
    ) *
    viewDir.xz /
    viewDir.y;

  float fade =
    clamp(
      2.0 -
      0.005 *
      length(
        cloudPos
      ),
      0.0,
      1.0
    );

  cloudPos +=
    CAMERA_POS.xz;

  vec4 refl =
    vec4_splat(
      0.0
    );

  #ifdef NL_AURORA

    vec4 aurora =
      renderAurora(
        cloudPos.xyy,
        t,
        env.rainFactor,
        env.fogCol
      );

    aurora.a *=
      fade;

    refl =
      vec4(
        2.0 *
        aurora.rgb *
        aurora.a,
        aurora.a
      );

  #endif

  #if NL_CLOUD_TYPE == 1

    vec4 clouds =
      renderCloudsSimple(
        skycol,
        cloudPos.xyy,
        t,
        env.rainFactor
      );

    clouds.a *=
      fade;

    refl =
      vec4(
        mix(
          refl.rgb,
          clouds.rgb,
          clouds.a
        ),
        min(
          refl.a +
          clouds.a,
          1.0
        )
      );

  #endif

  return refl;
}


#endif
