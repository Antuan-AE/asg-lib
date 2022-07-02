/**
 * @file ASGConfig.h
 *
 * @brief Declares compiler specific macros used by the ASG API for ARM platform.
 * @author	Ing. Antonio A. Iznaga Marín.
 * @date	11/13/2017
 */
#ifndef ASGCONFIG
#define ASGCONFIG

#if defined(ARM_MATH_CM7) || defined(ARM_MATH_CM4) || defined(ARM_MATH_CM3) || \
	defined(ARM_MATH_CM0) || defined(ARM_MATH_CM0)
#include <arm_math.h>
#ifndef ARM_MATH
#define ARM_MATH
#endif
#undef PI
#endif

#if __cplusplus >= 201103L //c++11 support
#define E_COMPILER_NULLPTR
#define E_COMPILER_DEFAULT_MEMBERS
#define E_COMPILER_DELETE_MEMBERS
#define E_COMPILER_OVERRIDE_MEMBERS
#define E_COMPILER_FINAL_MEMBERS
#define E_COMPILER_CONSTEXPR_MEMBERS
#endif
#ifdef E_COMPILER_NULLPTR
# define E_NULLPTR         nullptr
#else
# define E_NULLPTR         NULL
#endif

#ifdef E_COMPILER_DEFAULT_MEMBERS
#  define E_DECLARE_DEFAULT = default
#else
#  define E_DECLARE_DEFAULT
#endif

#ifdef E_COMPILER_DELETE_MEMBERS
# define E_DECLARE_DELETE = delete
#else
# define E_DECLARE_DELETE
#endif

#ifdef E_COMPILER_OVERRIDE_MEMBERS
# define E_DECLARE_OVERRIDE override
#else
# define E_DECLARE_OVERRIDE
#endif

#ifdef E_COMPILER_FINAL_MEMBERS
# define E_DECLARE_FINAL final
#else
# define E_DECLARE_FINAL
#endif

#ifdef E_COMPILER_CONSTEXPR_MEMBERS
# define E_DECLARE_CONSTEXPR constexpr
#else
# define E_DECLARE_CONSTEXPR
#endif

#define E_DISABLE_COPY(Class) \
    Class(const Class &) E_DECLARE_DELETE;\
    Class &operator=(const Class &) E_DECLARE_DELETE

#endif /*ASGCONFIG*/
