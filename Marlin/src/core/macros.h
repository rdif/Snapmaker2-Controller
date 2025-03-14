/**
 * Marlin 3D Printer Firmware
 * Copyright (C) 2019 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (C) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include "minmax.h"

#define NUM_AXIS 5
#define X_TO_E 5 // XYZBE
#define XYZ  3
#define XN 4 // XYZB

#define _AXIS(A) (A##_AXIS)

#define _XMIN_ 100
#define _YMIN_ 200
#define _ZMIN_ 300
#define _XMAX_ 101
#define _YMAX_ 201
#define _ZMAX_ 301

#define _FORCE_INLINE_ __attribute__((__always_inline__)) __inline__
#define  FORCE_INLINE  __attribute__((always_inline)) inline
#define _UNUSED      __attribute__((unused))
#define _O0          __attribute__((optimize("O0")))
#define _Os          __attribute__((optimize("Os")))
#define _O1          __attribute__((optimize("O1")))
#define _O2          __attribute__((optimize("O2")))
#define _O3          __attribute__((optimize("O3")))

// Clock speed factors
#if !defined(CYCLES_PER_MICROSECOND) && !(defined(__GD32F1__) || defined(__STM32F1__))
  #define CYCLES_PER_MICROSECOND (F_CPU / 1000000UL) // 16 or 20 on AVR
#endif

// Nanoseconds per cycle
#define NANOSECONDS_PER_CYCLE (1000000000.0 / F_CPU)

// Remove compiler warning on an unused variable
#define UNUSED(X) (void)X

// Macros to make a string from a macro
#define STRINGIFY_(M) #M
#define STRINGIFY(M) STRINGIFY_(M)

#define A(CODE) " " CODE "\n\t"
#define L(CODE) CODE ":\n\t"

// Macros for bit masks
#undef _BV
#define _BV(n) (1<<(n))
#define TEST(n,b) !!((n)&_BV(b))
#define SBI(n,b) (n |= _BV(b))
#define CBI(n,b) (n &= ~_BV(b))
#define SET_BIT_TO(N,B,TF) do{ if (TF) SBI(N,B); else CBI(N,B); }while(0)

#define _BV32(b) (1UL << (b))
#define TEST32(n,b) !!((n)&_BV32(b))
#define SBI32(n,b) (n |= _BV32(b))
#define CBI32(n,b) (n &= ~_BV32(b))

// Macros for maths shortcuts
#undef M_PI
#define M_PI 3.14159265358979323846f

#define RADIANS(d) ((d)*float(M_PI)/180.0f)
#define DEGREES(r) ((r)*180.0f/float(M_PI))
#define HYPOT2(x,y) (sq(x)+sq(y))

#define CIRCLE_AREA(R) (float(M_PI) * sq(float(R)))
#define CIRCLE_CIRC(R) (2 * float(M_PI) * float(R))

#define SIGN(a) ((a>0)-(a<0))
#define IS_POWER_OF_2(x) ((x) && !((x) & ((x) - 1)))

// Macros to constrain values
#ifdef __cplusplus

  // C++11 solution that is standards compliant.
  template <class V, class N> static inline constexpr void NOLESS(V& v, const N n) {
    if (v < n) v = n;
  }
  template <class V, class N> static inline constexpr void NOMORE(V& v, const N n) {
    if (v > n) v = n;
  }
  template <class V, class N1, class N2> static inline constexpr void LIMIT(V& v, const N1 n1, const N2 n2) {
    if (v < n1) v = n1;
    else if (v > n2) v = n2;
  }

#else

  // Using GCC extensions, but Travis GCC version does not like it and gives
  //  "error: statement-expressions are not allowed outside functions nor in template-argument lists"
  #define NOLESS(v, n) \
    do { \
      __typeof__(n) _n = (n); \
      if (v < _n) v = _n; \
    } while(0)

  #define NOMORE(v, n) \
    do { \
      __typeof__(n) _n = (n); \
      if (v > _n) v = _n; \
    } while(0)

  #define LIMIT(v, n1, n2) \
    do { \
      __typeof__(n1) _n1 = (n1); \
      __typeof__(n2) _n2 = (n2); \
      if (v < _n1) v = _n1; \
      else if (v > _n2) v = _n2; \
    } while(0)

#endif

// Macros to chain up to 12 conditions
#define _DO_1(W,C,A)       (_##W##_1(A))
#define _DO_2(W,C,A,B)     (_##W##_1(A) C _##W##_1(B))
#define _DO_3(W,C,A,V...)  (_##W##_1(A) C _DO_2(W,C,V))
#define _DO_4(W,C,A,V...)  (_##W##_1(A) C _DO_3(W,C,V))
#define _DO_5(W,C,A,V...)  (_##W##_1(A) C _DO_4(W,C,V))
#define _DO_6(W,C,A,V...)  (_##W##_1(A) C _DO_5(W,C,V))
#define _DO_7(W,C,A,V...)  (_##W##_1(A) C _DO_6(W,C,V))
#define _DO_8(W,C,A,V...)  (_##W##_1(A) C _DO_7(W,C,V))
#define _DO_9(W,C,A,V...)  (_##W##_1(A) C _DO_8(W,C,V))
#define _DO_10(W,C,A,V...) (_##W##_1(A) C _DO_9(W,C,V))
#define _DO_11(W,C,A,V...) (_##W##_1(A) C _DO_10(W,C,V))
#define _DO_12(W,C,A,V...) (_##W##_1(A) C _DO_11(W,C,V))
#define __DO_N(W,C,N,V...) _DO_##N(W,C,V)
#define _DO_N(W,C,N,V...)  __DO_N(W,C,N,V)
#define DO(W,C,V...)       _DO_N(W,C,NUM_ARGS(V),V)

// Macros to support option testing
#define _CAT(a,V...) a##V
#define SWITCH_ENABLED_false 0
#define SWITCH_ENABLED_true  1
#define SWITCH_ENABLED_0     0
#define SWITCH_ENABLED_1     1
#define SWITCH_ENABLED_0x0   0
#define SWITCH_ENABLED_0x1   1
#define SWITCH_ENABLED_      1
#define _ENA_1(O)           _CAT(SWITCH_ENABLED_, O)
#define _DIS_1(O)           !_ENA_1(O)
#define ENABLED(V...)       DO(ENA,&&,V)
#define DISABLED(V...)      DO(DIS,&&,V)

#define ANY(V...)          !DISABLED(V)
#define NONE(V...)          DISABLED(V)
#define ALL(V...)           ENABLED(V)
#define BOTH(V1,V2)         ALL(V1,V2)
#define EITHER(V1,V2)       ANY(V1,V2)

// Macros to support pins/buttons exist testing
#define _PINEX_1(PN)        (defined(PN##_PIN) && PN##_PIN >= 0)
#define PIN_EXISTS(V...)    DO(PINEX,&&,V)
#define ANY_PIN(V...)       DO(PINEX,||,V)

#define _BTNEX_1(BN)        (defined(BTN_##BN) && BTN_##BN >= 0)
#define BUTTON_EXISTS(V...) DO(BTNEX,&&,V)
#define ANY_BUTTON(V...)    DO(BTNEX,||,V)

#define WITHIN(N,L,H)       ((N) >= (L) && (N) <= (H))
#define NUMERIC(a)          WITHIN(a, '0', '9')
#define DECIMAL(a)          (NUMERIC(a) || a == '.')
#define NUMERIC_SIGNED(a)   (NUMERIC(a) || (a) == '-' || (a) == '+')
#define DECIMAL_SIGNED(a)   (DECIMAL(a) || (a) == '-' || (a) == '+')
#define COUNT(a)            (sizeof(a)/sizeof(*a))
#define ZERO(a)             memset(a,0,sizeof(a))
#define COPY(a,b) do{ \
    static_assert(sizeof(a[0]) == sizeof(b[0]), "COPY: '" STRINGIFY(a) "' and '" STRINGIFY(b) "' types (sizes) don't match!"); \
    memcpy(&a[0],&b[0],MIN(sizeof(a),sizeof(b))); \
  }while(0)

// Macros for initializing arrays
#define ARRAY_6(v1, v2, v3, v4, v5, v6, ...) { v1, v2, v3, v4, v5, v6 }
#define ARRAY_5(v1, v2, v3, v4, v5, ...)     { v1, v2, v3, v4, v5 }
#define ARRAY_4(v1, v2, v3, v4, ...)         { v1, v2, v3, v4 }
#define ARRAY_3(v1, v2, v3, ...)             { v1, v2, v3 }
#define ARRAY_2(v1, v2, ...)                 { v1, v2 }
#define ARRAY_1(v1, ...)                     { v1 }

#define _ARRAY_N(N,V...) ARRAY_##N(V)
#define ARRAY_N(N,V...) _ARRAY_N(N,V)

// Macros for adding
#define INC_0 1
#define INC_1 2
#define INC_2 3
#define INC_3 4
#define INC_4 5
#define INC_5 6
#define INC_6 7
#define INC_7 8
#define INC_8 9
#define INCREMENT_(n) INC_##n
#define INCREMENT(n) INCREMENT_(n)

// Macros for subtracting
#define DEC_1 0
#define DEC_2 1
#define DEC_3 2
#define DEC_4 3
#define DEC_5 4
#define DEC_6 5
#define DEC_7 6
#define DEC_8 7
#define DEC_9 8
#define DECREMENT_(n) DEC_##n
#define DECREMENT(n) DECREMENT_(n)

#define MMM_TO_MMS(MM_M) ((MM_M)/60.0f)
#define MMS_TO_MMM(MM_S) ((MM_S)*60.0f)

#define NOOP (void(0))

#define CEILING(x,y) (((x) + (y) - 1) / (y))

#undef ABS
#ifdef __cplusplus
  template <class T> static inline constexpr const T ABS(const T v) { return v >= 0 ? v : -v; }
#else
  #define ABS(a) ({__typeof__(a) _a = (a); _a >= 0 ? _a : -_a;})
#endif

#define UNEAR_ZERO(x) ((x) < 0.000001f)
#define NEAR_ZERO(x) WITHIN(x, -0.000001f, 0.000001f)
#define NEAR(x,y) NEAR_ZERO((x)-(y))

#define RECIPROCAL(x) (NEAR_ZERO(x) ? 0 : (1 / float(x)))
#define FIXFLOAT(f) (f + (f < 0 ? -0.00005f : 0.00005f))

//
// Maths macros that can be overridden by HAL
//
#define ATAN2(y, x) atan2f(y, x)
#define POW(x, y)   powf(x, y)
#define SQRT(x)     sqrtf(x)
#define RSQRT(x)    (1 / sqrtf(x))
#define CEIL(x)     ceilf(x)
#define FLOOR(x)    floorf(x)
#define LROUND(x)   lroundf(x)
#define FMOD(x, y)  fmodf(x, y)
#define HYPOT(x,y)  SQRT(HYPOT2(x,y))

#ifdef TARGET_LPC1768
  #define I2C_ADDRESS(A) ((A) << 1)
#else
  #define I2C_ADDRESS(A) A
#endif

//Machine type defines,ExecuterManager use this
#define MACHINE_TYPE_UNDEFINE     0
#define MACHINE_TYPE_3DPRINT      1
#define MACHINE_TYPE_CNC          2
#define MACHINE_TYPE_LASER        3
#define MACHINE_TYPE_LASER_10W    4
#define MACHINE_TYPE_DUALEXTRUDER 5
#define MACHINE_TYPE_LASER_20W    6
#define MACHINE_TYPE_LASER_40W    7

//Machine size define
#define MACHINE_SIZE_UNKNOW 0
#define MACHINE_SIZE_S      1
#define MACHINE_SIZE_M      2
#define MACHINE_SIZE_L      3

//Machine Status defines,StatuaControl use this
#define STAT_IDLE           0
#define STAT_RUNNING        1
#define STAT_PAUSE          2
#define STAT_RUNNING_ONLINE 3
#define STAT_PAUSE_ONLINE   4

//FLASH定义占用空间大小
#define FLASH_SIZE      (1024*1024)
#define BOOT_CODE_SIZE	(32*1024)
#define BOOT_PARA_SIZE	(4*1024)
#define MARLIN_POWERPANIC_SIZE  (6*1024)
#define MARLIN_EEPROM_SIZE (4*1024)
#define UPDATE_CONTENT_INFO_SIZE (2*1024)
#define MARLIN_CODE_SIZE	((FLASH_SIZE - BOOT_CODE_SIZE - BOOT_PARA_SIZE - MARLIN_EEPROM_SIZE - MARLIN_POWERPANIC_SIZE - UPDATE_CONTENT_INFO_SIZE) / 2)

//起始地址必须为2048倍数
#define FLASH_BOOT_PARA	          (0x8000000 + BOOT_CODE_SIZE)
#define FLASH_MARLIN_POWERPANIC   (FLASH_BOOT_PARA + BOOT_PARA_SIZE)
#define FLASH_MARLIN_EEPROM       (FLASH_MARLIN_POWERPANIC + MARLIN_POWERPANIC_SIZE)
#define FLASH_MARLIN	            (FLASH_MARLIN_EEPROM + MARLIN_EEPROM_SIZE)
#define FLASH_UPDATE_CONTENT_INFO (FLASH_MARLIN + MARLIN_CODE_SIZE)
#define FLASH_UPDATE_CONTENT      (FLASH_UPDATE_CONTENT_INFO + UPDATE_CONTENT_INFO_SIZE)

