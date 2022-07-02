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

/**
 * @brief sin_f32 "Cross plataform" sine function
 * @param x radian value
 * @return The value of the sine
 */
inline std::float32_t sin(std::float32_t x) {
#ifdef ARM_MATH
    return arm_sin_f32(x);
#else
    return std::sin(x);
#endif
}

/**
 * @brief cos_f32 "Cross plataform" cosine function
 * @param x radian value
 * @return The value of the sine
 */
inline std::float32_t cos(std::float32_t x) {
#ifdef ARM_MATH
    return arm_cos_f32(x);
#else
    return std::cos(x);
#endif
}

/**
 * @brief sqrt_f32 "Cross plataform" square root function
 * @param x Value
 * @return Square root of x
 */
inline std::float32_t sqrt(std::float32_t x) {
#ifdef ARM_MATH
    std::float32_t result;
    arm_sqrt_f32(x, &result);
    return result;
#else
    return std::sqrt(x);
#endif
}

/**
 * @brief abs_f32 "Cross platform" absolute value function
 * @param x Value
 * return |x| --> absolute value of x
 */
inline std::float32_t abs(std::float32_t x) {
#ifdef ARM_MATH
    std::float32_t result;
    arm_abs_f32(&x, &result, 1);
    return result;
#else
    return std::abs(x);
#endif
}

/**
 * @brief round_f32 Custom round fuction, for some reason std::round() doesn't work right
 * @param x
 * @return rounded int32 value
 */
inline std::int32_t round(std::float32_t x) {
    return static_cast<std::int32_t>(std::ceil(x - 0.5f));
}

/**
 * @brief exp
 * Simple wrapper for the std::exp() function
 * @param x
 * @return e^x
 */
inline std::float32_t exp(std::float32_t x) {
    return std::exp(x);
}

/**
 * @brief pow
 * @param base
 * @param exp
 * @return
 */
inline std::float32_t pow(std::float32_t base, std::float32_t exp) {
    return std::pow(base, exp);
}

/**
 * @brief pow
 * @param base
 * @param exp
 * @return
 */
inline std::uint32_t pow(std::int32_t base, std::int32_t exp) {
    return ASG::round(std::pow(static_cast<std::float32_t>(base), exp));
}

/**
 * @brief normalizeRadian
 * Wrapps radian value to its equivalent beetwen 0 and 2*PI
 * @param radian
 * @return wrapped value
 */
inline std::float32_t normalizeRadian(std::float32_t radian) {
    return std::fmod(radian, 2*ASG::PI);
}

/**
 * @brief clic_rad Radian based square wave like function, compute the value in
 *      the desired position (from 0 to 2PI) of a single clic wave form that is
 *      centered in PI.
 * @param radian Then angle of the vector in radian
 * @param pulseWitdh_rad Pulse With of the pulse in radian, ,must be beetwen 0 and 2*PI
 * @param pulseAmplitude Amplitud of the pulse
 * @param offsetFromPI_rad Offset of the wave form (from 0 to PI)
 * @return The value of the waveform in that position
 */
inline std::float32_t clic_rad(std::float32_t radianIndex,
                               std::float32_t pulseAmplitude,
                               bool &syncMark,
                               std::float32_t radianStep = 0.0f,
                               std::float32_t pulseHalfWitdh_rad = ASG::PI / 2.0f,
                               std::float32_t offsetFromPI_rad = 0.0f) {
    assert(pulseHalfWitdh_rad >= 0 && pulseHalfWitdh_rad <= ASG::PI);
    assert(offsetFromPI_rad >= 0 && offsetFromPI_rad <= ASG::DOUBLE_PI);
    radianIndex = normalizeRadian(radianIndex);
    std::float32_t pulseStart = ASG::PI + offsetFromPI_rad - pulseHalfWitdh_rad;
    std::float32_t pulseStop = ASG::PI + offsetFromPI_rad + pulseHalfWitdh_rad;

    std::float32_t retVal = 0.0f;
    if ((radianIndex >= pulseStart) && (radianIndex <= pulseStop)) {
        retVal = pulseAmplitude;
        if(radianIndex <= (pulseStart + radianStep)) {
            syncMark = true;
        }
    } else {
        retVal = 0.0;
        syncMark = false;
    }
    return retVal;
}

/**
 * @brief samples2radian In a periodic signal converts from samples to radian (0 - 2*PI)
 * @param sample
 * @param period_secs
 * @param samplingFreq
 * @return
 */
inline std::float32_t samples2radian(std::size_t sample, std::float32_t period_secs, std::float32_t samplingFreq) {
    assert(period_secs > 0.0f);
    assert(samplingFreq > 0.0f);
    return sample * 2 * ASG::PI / (samplingFreq * period_secs);
}

/**
 * @brief seconds2radian In a periodic signal converts from seconds to radian (0 - 2*PI)
 * @param time_secs
 * @param period_secs
 * @return
 */
inline std::float32_t seconds2radian(std::float32_t time_secs, std::float32_t period_secs) {
    assert(period_secs > 0.0f);
    return time_secs * 2 * ASG::PI / period_secs;
}

/**
 * @brief radian2seconds
 * In a periodic signal converts from radian to seconds
 * @param radian
 * @param period_secs
 * @return
 */
inline std::float32_t radian2seconds(std::float32_t radian, std::float32_t period_secs) {
    assert(period_secs > 0.0f);
    assert(radian > 0.0f);
    return radian * period_secs / (2 * ASG::PI);
}

/**
 * @brief radian2samples In a periodic signal converts from radian to samples
 * @param radian
 * @param period_secs
 * @param samplingFreq
 * @return
 */
inline std::size_t radian2samples(std::float32_t radian, std::float32_t period_secs, std::float32_t samplingFreq) {
    assert(period_secs > 0.0f);
    assert(samplingFreq > 0.0f);
    return ASG::round(radian * samplingFreq * period_secs / (ASG::DOUBLE_PI));
}

/**
 * @brief radian2samples In a periodic signal converts from radian to samples
 * @param radian
 * @param period_secs
 * @param samplingFreq
 * @return
 */
inline std::size_t seconds2samples(std::float32_t seconds, std::float32_t samplingFreq) {
    assert(seconds > 0.0f);
    assert(samplingFreq > 0.0f);
    return static_cast<std::size_t>(round(seconds * samplingFreq));
}

/**
 * @brief vectorMultiplication
 * "Cross platform" vector multiplication. It multiplies two sources vectors and stores
 * result i destination vector. The size of the three vectors must be the same.
 * @param sourceVector1
 * @param sourceVector2
 * @param destinationVector
 * @param vectorSize
 */
inline void vectorMultiplication(std::float32_t *sourceVector1, std::float32_t *sourceVector2,
                                 std::float32_t *destinationVector, std::size_t vectorSize) {
#ifdef ARM_MATH
    return arm_mult_f32(sourceVector1, sourceVector2, destinationVector, vectorSize);
#else
    for(std::size_t index = 0; index < vectorSize; index++) {
        destinationVector[index] = sourceVector1[index] * sourceVector2[index];
    }
    return;
#endif
}

/**
 * @brief vectorOffset
 * "Cross platform" vector offset adds a value (offset) to all members a the source
 * vector and stores it at destination vector. Both vectors must have the same length.
 * @param sourceVector
 * @param offset
 * @param destinationVector
 * @param vectorSize
 */
inline void vectorOffset(std::float32_t *sourceVector, std::float32_t offset,
                         std::float32_t *destinationVector, std::size_t vectorSize) {
#ifdef ARM_MATH
    return arm_offset_f32(sourceVector, offset, destinationVector, vectorSize);
#else
    for(std::size_t index = 0; index < vectorSize; index++) {
        destinationVector[index] = sourceVector[index] + offset;
    }
    return;
#endif
}

/**
 * @brief vectorScale
 * "Cross platform" vector scale multiplies a value (scale) to all members a the source
 * vector and stores it at destination vector. Both vectors must have the same length.
 * @param sourceVector
 * @param scale
 * @param destinationVector
 * @param vectorSize
 */
inline void vectorScale(std::float32_t *sourceVector, std::float32_t scale,
                        std::float32_t *destinationVector, std::size_t vectorSize) {
#ifdef ARM_MATH
    return arm_scale_f32(sourceVector, scale, destinationVector, vectorSize);
#else
    for(std::size_t index = 0; index < vectorSize; index++) {
        destinationVector[index] = sourceVector[index] * scale;
    }
    return;
#endif
}

/**
 * @brief vectorMaximum
 * "Cross platform" vector maximum finds the maximum "positive" value of a source vector
 * and returns it in resultRef reference value. Vector size must be suplied.
 * @param sourceVector
 * @param vectorSize
 * @param resultRef
 */
inline void vectorMaximum(std::float32_t *sourceVector, std::size_t vectorSize,
                          std::float32_t &resultRef) {
#ifdef ARM_MATH
    std::size_t index = 0;
return arm_max_f32(sourceVector, vectorSize, &resultRef, &index);
#else
    std::float32_t max = 0.0f;
    for(std::size_t loop = 0; loop < vectorSize; loop++) {
        max = (max > sourceVector[loop]) ? max : sourceVector[loop];
    }
    resultRef = max;
#endif
}

}/// end of ASG namespace
#endif /*ASGMATH*/
