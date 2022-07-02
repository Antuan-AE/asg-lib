/**
 * @file StimParameters.h
 *
 * @brief Defines common Stimuli parameters.
 * @date 11/12/2017
 * @author <b>Ing. Antonio A. Iznaga Marin.</b>
 */

#ifndef INCLUDE_STIMULIPARAMETERS_H_
#define INCLUDE_STIMULIPARAMETERS_H_

#include "ASGConfig.h"

namespace ASG
{
/**
 * @brief Class for All stimuli common parameters
 */
class StimParameters
{
public:
	/**
	 * @brief Default empty constructor.
	 */
	StimParameters();

	/**
	 * @brief Stimuli specific parameter offset.
	 */
	static const std::uint8_t PAYLOAD_OFFSET = 8;

	/**
	 * @brief
	 */
	static const std::uint8_t TONE_FREQUENCIES_GROUP = 4;

	/**
	 * @brief Maximum number of modulated tones to be generated.
	 */
	static const std::uint8_t MIXED_TONES_MAXIMUM = 5;

private:
	/**
	 * @brief Prevents this object from being copied.
	 */
	E_DISABLE_COPY(StimParameters);
};
} ///end of ASG namespace
#endif /*INCLUDE_STIMULIPARAMETERS_H_*/
