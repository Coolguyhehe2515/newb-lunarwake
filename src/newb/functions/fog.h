#ifndef FOG_H
#define FOG_H

float nlRenderFogFade(float relativeDist, vec3 FOG_COLOR, vec2 FOG_CONTROL) {
  #ifdef NL_FOG
    float fade = smoothstep(FOG_CONTROL.x, FOG_CONTROL.y, relativeDist);

    // misty effect
    float density = NL_MIST_DENSITY*(19.0 - 18.0*FOG_COLOR.g);
    fade += (1.0-fade)*(0.3-0.3*exp(-relativeDist*relativeDist*density));

    return NL_FOG * fade;
  #else
    return 0.0;
  #endif
}

vec3 nlBiomeFogColor(float biomeId, vec3 baseColor, float rainFactor) {
  float baseId = biomeId >= 128.0 ? biomeId - 128.0 : biomeId;
  vec3 tint = baseColor;
  bool matched = true;

  if (baseId == 6.0) {
    tint = NL_SWAMP_FOG_COL;
  } else if (baseId == 21.0 || baseId == 22.0 || baseId == 23.0) {
    tint = NL_JUNGLE_FOG_COL;
  } else if (baseId == 2.0 || baseId == 17.0) {
    tint = NL_DESERT_FOG_COL;
  } else if (baseId == 37.0 || baseId == 38.0 || baseId == 39.0) {
    tint = NL_MESA_FOG_COL;
  } else if (baseId == 12.0 || baseId == 13.0) {
    tint = NL_SNOWY_FOG_COL;
  } else if (baseId == 14.0 || baseId == 15.0) {
    tint = NL_MUSHROOM_FOG_COL;
  } else if (baseId == 29.0) {
    tint = NL_DARKFOREST_FOG_COL;
  } else {
    matched = false;
  }

  if (!matched) return baseColor;
  float strength = NL_BIOME_FOG_STRENGTH*(1.0-0.5*rainFactor);
  return mix(baseColor, tint, strength);
}

float nlRenderGodRayIntensity(vec3 cPos, vec3 worldPos, float t, vec2 uv1, float relativeDist, vec3 FOG_COLOR) {
  // offset wPos (only works upto 16 blocks)
  vec3 offset = cPos - 16.0*fract(worldPos*0.0625);
  offset = abs(2.0*fract(offset*0.0625)-1.0);
  offset = offset*offset*(3.0-2.0*offset);
  //offset = 0.5 + 0.5*cos(offset*0.392699082);

  //vec3 ofPos = wPos+offset;
  vec3 nrmof = normalize(worldPos);

  float u = nrmof.z/length(nrmof.zy);
  float diff = dot(offset,vec3(0.1,0.2,1.0)) + 0.07*t;
  float mask = nrmof.x*nrmof.x;

  float vol = sin(7.0*u + 1.5*diff)*sin(3.0*u + diff);
  vol *= vol*mask*uv1.y*(1.0-mask*mask);
  vol *= relativeDist*relativeDist;

  // dawn/dusk mask
  vol *= clamp(3.0*(FOG_COLOR.r-FOG_COLOR.b), 0.0, 1.0);

  vol = smoothstep(0.0, 0.1, vol);
  return vol;
}

#endif
