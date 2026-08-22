#ifndef NL_CONFIG_H
#define NL_CONFIG_H

/*
  NEWB SHADER MAIN CONFIG
  This part contains base configuration options for the shader.

  TOGGLES
  - If [toggle] is mentioned, then
    options can be commented to disable (by adding '//')
  - eg: #define PLANTS_WAVE    -> this is ON
        //#define PLANTS_WAVE  -> this is OFF

  COLOR VALUES
  - Color format:
    vec3(red,green,blue)

  - 1.0 means 100%, 0.0 means 0%

  - eg:
    vec3(1.0,1.0,0.0) = yellow

  VALUES
  - Values must be decimal
  - eg. 32 is wrong, 32.0 is correct

  TYPES
  - Should be integer.
  - options to choose will be mentioned there

  Remember to rebuild the shader after making changes.
*/


/* =========================================================
   COLOR CORRECTION
   ========================================================= */

#define NL_TONEMAP_TYPE 3
#define NL_GAMMA 1.33

//#define NL_EXPOSURE 1.3
//#define NL_SATURATION 1.4
//#define NL_TINT

#define NL_TINT_LOW  vec3(0.3,0.5,1.4)
#define NL_TINT_HIGH vec3(1.4,0.7,0.3)


/* =========================================================
   LIGHTING
   ========================================================= */

#define NL_SUNLIGHT_INTENSITY   3.3
#define NL_TORCHLIGHT_INTENSITY 1.0
#define NL_SHADOW_INTENSITY     0.7
#define NL_MIN_LIGHTING_BOOST   1.5

//#define NL_BLINKING_TORCH

#define NL_CLOUD_SHADOW


/* =========================================================
   AMBIENT LIGHT
   ========================================================= */

#define NL_NETHER_AMBIENT vec3(3.0,2.16,1.89)
#define NL_END_AMBIENT    vec3(1.98,1.25,2.3)


/* =========================================================
   SUN / MOON LIGHT COLOR
   ========================================================= */

#define NL_DAWN_SUNLIGHT_COL    vec3(1.0,0.62,0.20)
#define NL_NOON_SUNLIGHT_COL    vec3(1.0,0.75,0.57)
#define NL_NIGHT_MOONLIGHT_COL  vec3(0.01,0.03,0.2)


/* =========================================================
   TORCH COLORS
   ========================================================= */

#define NL_OVERWORLD_TORCH_COL   vec3(1.0,0.482,0.0)
#define NL_UNDERWATER_TORCH_COL  vec3(1.0,0.52,0.18)
#define NL_NETHER_TORCH_COL      vec3(1.0,0.482,0.0)
#define NL_END_TORCH_COL         vec3(1.0,0.482,0.0)


/* =========================================================
   FOG
   ========================================================= */

#define NL_FOG 1.0
#define NL_MIST_DENSITY 0.18
#define NL_RAIN_MIST_OPACITY 0.12
#define NL_CLOUDY_FOG 0.1


/* =========================================================
   SKY
   ========================================================= */

#define NL_SKY_VOID_FACTOR     0.5
#define NL_SKY_VOID_DARKNESS   0.3
#define NL_SKY_RAIN_MIX_FACTOR 0.9


/* -------------------------
   DAWN / SUNRISE / SUNSET
   ------------------------- */

#define NL_DAWN_ZENITH_COL   vec3(0.42,0.20,0.12)
#define NL_DAWN_HORIZON_COL  vec3(1.35,0.55,0.16)
#define NL_DAWN_EDGE_COL     vec3(2.40,1.35,0.38)


/* -------------------------
   DAY
   ------------------------- */

#define NL_DAY_ZENITH_COL    vec3(0.3,0.9,2.0)
#define NL_DAY_HORIZON_COL   vec3(1.0,1.6,1.8)
#define NL_DAY_EDGE_COL      vec3(1.44,1.56,1.62)


/* -------------------------
   NIGHT
   ------------------------- */

#define NL_NIGHT_ZENITH_COL  vec3(0.14,0.14,0.14)
#define NL_NIGHT_HORIZON_COL vec3(0.10,0.10,0.10)
#define NL_NIGHT_EDGE_COL    vec3(0.06,0.06,0.06)


/* -------------------------
   RAIN
   ------------------------- */

#define NL_RAIN_ZENITH_COL   vec3(0.47,0.51,0.56)
#define NL_RAIN_HORIZON_COL  vec3(0.6,0.6,0.6)


/* -------------------------
   END
   ------------------------- */

#define NL_END_ZENITH_COL    vec3(0.08,0.001,0.1)
#define NL_END_HORIZON_COL   vec3(0.6,0.02,0.6)


/* =========================================================
   RAINBOW
   ========================================================= */

#define NL_RAINBOW

#define NL_RAINBOW_CLEAR 0.0
#define NL_RAINBOW_RAIN  0.4


/* =========================================================
   ORE GLOW
   ========================================================= */

#define NL_GLOW_TEX 2.3
#define NL_GLOW_SHIMMER 0.8
#define NL_GLOW_SHIMMER_SPEED 0.9

//#define NL_GLOW_LEAK 0.6


/* =========================================================
   WAVING
   ========================================================= */

#define NL_PLANTS_WAVE 0.05
#define NL_LANTERN_WAVE 0.16
#define NL_WAVE_SPEED 2.8

//#define NL_EXTRA_PLANTS_WAVE

#define NL_WAVE_RANGE 13.0


/* =========================================================
   WATER
   ========================================================= */

#define NL_WATER_TRANSPARENCY 0.9
#define NL_WATER_BUMP 0.09
#define NL_WATER_WAVE_SPEED 0.8
#define NL_WATER_TEX_OPACITY 0.3

#define NL_WATER_WAVE

//#define NL_WATER_REFL_MASK

#define NL_WATER_TINT vec3(0.52,0.9,0.45)


/* =========================================================
   UNDERWATER
   ========================================================= */

#define NL_UNDERWATER_BRIGHTNESS 0.8
#define NL_CAUSTIC_INTENSITY 1.9
#define NL_UNDERWATER_WAVE 0.1
#define NL_UNDERWATER_STREAKS 1.0

#define NL_UNDERWATER_TINT vec3(0.9,1.0,0.9)


/* =========================================================
   CLOUD TYPE
   ========================================================= */

/*
  0 = Vanilla
  1 = Soft
  2 = Rounded
  3 = Realistic
*/

#define NL_CLOUD_TYPE 0


/* =========================================================
   VANILLA CLOUD SETTINGS
   ========================================================= */

/*
  Make sure clouds.png is removed when using
  shader-rendered vanilla clouds.
*/

#define NL_CLOUD0_THICKNESS 2.1
#define NL_CLOUD0_RAIN_THICKNESS 4.0
#define NL_CLOUD0_OPACITY 0.9

#define NL_CLOUD0_MULTILAYER


/* =========================================================
   BOX CLOUD REFLECTION
   ========================================================= */

#define NL_CLOUDBOX_SCALE 0.02
#define NL_CLOUDBOX_SPEED 0.04
#define NL_CLOUDBOX_OCTAVES 3
#define NL_CLOUDBOX_THRESHOLD 0.6


/* =========================================================
   SOFT CLOUD SETTINGS
   ========================================================= */

#define NL_CLOUD1_SCALE vec2(0.016,0.022)
#define NL_CLOUD1_DEPTH 1.3
#define NL_CLOUD1_SPEED 0.04
#define NL_CLOUD1_DENSITY 0.54
#define NL_CLOUD1_OPACITY 0.9


/* =========================================================
   ROUNDED CLOUD SETTINGS
   ========================================================= */

#define NL_CLOUD2_THICKNESS 2.1
#define NL_CLOUD2_RAIN_THICKNESS 2.5
#define NL_CLOUD2_STEPS 5

#define NL_CLOUD2_SCALE vec2(0.033,0.033)
#define NL_CLOUD2_SHAPE vec2(0.5,0.4)
#define NL_CLOUD2_DENSITY 25.0
#define NL_CLOUD2_VELOCITY 0.8

//#define NL_CLOUD2_LAYER2

#define NL_CLOUD2_LAYER2_OFFSET 143.0
#define NL_CLOUD2_LAYER2_THICKNESS 2.5
#define NL_CLOUD2_LAYER2_RAIN_THICKNESS 3.0
#define NL_CLOUD2_LAYER2_STEPS 3

#define NL_CLOUD2_LAYER2_SCALE vec2(0.03,0.03)
#define NL_CLOUD2_LAYER2_SHAPE vec2(0.5,0.4)
#define NL_CLOUD2_LAYER2_DENSITY 25.0
#define NL_CLOUD2_LAYER2_VELOCITY 0.8


/* =========================================================
   REALISTIC CLOUD SETTINGS
   ========================================================= */

#define NL_CLOUD3_SCALE vec2(0.03,0.03)
#define NL_CLOUD3_SPEED 0.005
#define NL_CLOUD3_SHADOW 0.9
#define NL_CLOUD3_SHADOW_OFFSET 0.3


/* =========================================================
   AURORA
   ========================================================= */

#define NL_AURORA 1.2
#define NL_AURORA_VELOCITY 0.03
#define NL_AURORA_SCALE 0.04
#define NL_AURORA_WIDTH 0.18

#define NL_AURORA_COL1 vec3(0.1,1.0,0.0)
#define NL_AURORA_COL2 vec3(0.1,0.0,1.0)


/* =========================================================
   CLOUD / AURORA REFLECTION
   ========================================================= */

#define NL_CLOUD_AURORA_REFLECTION


/* =========================================================
   SHOOTING STAR
   ========================================================= */

#define NL_SHOOTING_STAR 1.0
#define NL_SHOOTING_STAR_PERIOD 6.0
#define NL_SHOOTING_STAR_DELAY 64.0


/* =========================================================
   GALAXY
   ========================================================= */

//#define NL_GALAXY_STARS 2.0

#define NL_GALAXY_VIBRANCE 0.7
#define NL_GALAXY_SPEED 0.03
#define NL_GALAXY_DAY_VISIBILITY 0.0


/* =========================================================
   CHUNK LOADING
   ========================================================= */

//#define NL_CHUNK_LOAD_ANIM 100.0


/* =========================================================
   SUN / MOON
   ========================================================= */

#define NL_SUN_SIZE  1.0
#define NL_SUN_SIZE_DAWN 1.0
#define NL_SUN_SIZE_DUSK 1.0
#define NL_MOON_SIZE 1.0
#define NL_MOON_SIZE_DAWN 1.0
#define NL_MOON_SIZE_DUSK 1.0

#define NL_SUN_PATH_YAW  15.0
#define NL_MOON_PATH_YAW 17.0

#define NL_SUN_PATH_TILT  31.0
#define NL_MOON_PATH_TILT -28.0

#define NL_SUN_TILT  45.0
#define NL_SUN_TILT_DAWN 45.0
#define NL_SUN_TILT_DUSK 45.0
#define NL_MOON_TILT 45.0
#define NL_MOON_TILT_DAWN 45.0
#define NL_MOON_TILT_DUSK 45.0

#define NL_DAWN_DUSK_RANGE 0.03 // 0.01 narrow window ~ 0.1 wide window


/* =========================================================
   PLAYER SHADOW
   ========================================================= */

#define NL_PLAYER_SHADOW // [toggle] blocky fake shadow under the local player

#define NL_PLAYER_EYE_HEIGHT 1.62        // camera height above feet, standing
#define NL_PLAYER_SHADOW_HEIGHT 1.8      // caster height, controls length vs sun angle
#define NL_PLAYER_SHADOW_MAX_LENGTH 6.0  // 2.0 short ~ 15.0 very long near sunset
#define NL_PLAYER_SHADOW_OPACITY 0.55    // 0.0 invisible ~ 1.0 pure black

#define NL_PLAYER_SHADOW_LEG_GAP    0.13
#define NL_PLAYER_SHADOW_LEG_WIDTH  0.12
#define NL_PLAYER_SHADOW_BODY_WIDTH 0.22
#define NL_PLAYER_SHADOW_HEAD_WIDTH 0.16


/* =========================================================
   GODRAYS
   ========================================================= */

//#define NL_GODRAY 0.3


/* =========================================================
   SKY REFLECTION / GROUND
   ========================================================= */

//#define NL_GROUND_REFL 0.4

#define NL_GROUND_RAIN_WETNESS 1.0
#define NL_GROUND_RAIN_PUDDLES 0.7


/* =========================================================
   ENTITY
   ========================================================= */

#define NL_ENTITY_BRIGHTNESS     0.65
#define NL_ENTITY_EDGE_HIGHLIGHT 0.41


/* =========================================================
   WEATHER PARTICLES
   ========================================================= */

#define NL_WEATHER_SPECK 0.6
#define NL_WEATHER_RAIN_SLANT 4.0
#define NL_WEATHER_PARTICLE_SIZE 1.0


/* =========================================================
   LAVA
   ========================================================= */

#define NL_LAVA_NOISE

//#define NL_LAVA_NOISE_BUMP 0.2

#define NL_LAVA_NOISE_SPEED 0.2


/*
  Only one subpack (Default) ships, so there's nothing to switch here
  anymore.

  If you want a lighter build for a weaker device, just comment
  out NL_FOG / NL_PLANTS_WAVE / NL_LANTERN_WAVE / NL_WATER_WAVE /
  NL_UNDERWATER_WAVE above directly and rebuild.
*/


#endif
