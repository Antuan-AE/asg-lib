/**
 * @file ASGMath.h
 *
 * @brief Defines all ASG mathematics types and global functions.
 * @author	Ing. Antonio A. Iznaga Marín.
 * @date	11/13/2017
 */
#ifndef ASGMATH
#define ASGMATH

#include <cstdint>
#include <assert.h>
#include <cmath>

#include "ASGConfig.h"

/**
 * @brief Expansion for std namespace to include IEEE-754 binary floating
 * 		point value types.
 */
namespace std
{
#ifndef float32_t
	/**
	 * @brief IEEE-754 single precision binary floating point value typedef.
	 */
	typedef float float32_t;
#endif

#ifndef float64_t
	/**
	 * @brief IEEE-754 double precision binary floating point value typedef.
	 */
	typedef double float64_t;
#endif

#ifndef q31_t
	/**
	 * @brief 32-bit fractional data type in 1.31 format.
	 */
	typedef int32_t q31_t;
#endif

#ifndef q23_t
	/**
	 * @brief 32-bit fractional data type in 1.23 format.
	 */
	typedef int32_t q23_t;
#endif
}/// end of std namespace extension.

namespace ASG
{
	/**
	 * @brief FLOAT32_TOLERANCE: For setting IEEE-754 single precision (32 bits)
	 * 			to 6 digits minimal precision.
	 */
	const std::float32_t FLOAT32_TOLERANCE = 0.000001f;

	/**
	 * @brief PI: Mathematical constant for sinusoidal stimuli generation.
	 * @remarks Value for pi in radians.
	 */
	const std::float32_t PI = 3.14159265358979f;

	/**
	 * @brief HALF_PI: Mathematical constant for sinusoidal stimuli generation.
	 * @remarks Value for half pi in radians.
	 */
	const std::float32_t HALF_PI = 1.5707963267949f;

	/**
	 * @brief DOUBLE_PI: Mathematical constant for sinusoidal stimuli generation.
	 * @remarks Value for double of pi in radians.
	 */
	const std::float32_t DOUBLE_PI = 6.28318530717959f;

	/**
	 * @brief E: Mathematical constant for exponential and logarithmic
	 * 			stimuli generation.
	 * @remarks Value for Euler constant.
	 */
	const std::float32_t E = 2.7182818284590452354f;

	/**
	 * @brief MIN_GENERATABLE_FREQUENCY: Minimum frequency value of generatable
	 * 			sinusoidal stimuli.
	 * @remarks For practical purposes, value is set to 10 Hz due tones lower than
	 * 			20 Hz cannot be heard.
	 */
	const std::float32_t MIN_GENERATABLE_FREQUENCY = 10.0f;

	/**
	 * @brief MAX_GENERATABLE_FREQUENCY: Maximum frequency value of generatable
	 * 			sinusoidal stimuli.
	 * @remarks For practical purposes, value is set to 20 kHz due tones above
	 * 			that cannot be heard.
	 */
	const std::float32_t MAX_GENERATABLE_FREQUENCY = 20000.0f;

}/// end of ASG namespace
#endif /*ASGMATH*/
