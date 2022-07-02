/**
 * @file Stim2Dac.h
 *
 * @brief Adapter from Stimuli generator to Digital to Analog Converter.
 * @date 11/13/2017
 * @author <b>Ing. Antonio A. Iznaga Marin.</b>
 */

#ifndef ASG_LIB_STIMDAC_H
#define ASG_LIB_STIMDAC_H

#include "ASGMath.h"

namespace ASG
{
/// Forward declaration for @ref Stimuli class.
class Stimuli;

/**
 * @brief ASG DAC Converter Adapter class.
 */
class Stim2Dac
{
public:
	/**
	 * @brief Constructor for adapter class.
	 * @param stimuli Pointer to specific stimuli to generate.
	 * @param dacResolution Amount of bits for DAC converter.
	 */
	Stim2Dac(Stimuli *stimuli = E_NULLPTR, std::uint16_t dacResolution = 24);

	/**
	 * @brief Getter method for generated stimuli
	 * @return A pointer to the stimuli being generated.
	 */
	Stimuli* getStimuli() const;

	/**
	 * @brief Setter method for Stimuli.
	 * @param getStim A pointer to the stimuli that will be generated.
	 */
	void setStimuli(Stimuli* stimuli);

	/**
	 * @brief Generation method for 32 bits unsigned samples.
	 * @param sampleBuffer A pointer to the output buffer to store generated samples.
	 * @param size The amount os samples to generate.
	 * @param sync An index based reference to signal which element of <ref>sampleBuffer</ref>
	 *          contains the synchronism mark sample.
	 * @return The amount of samples that were successfully generated.
	 */
	std::size_t generate(std::uint32_t *sampleBuffer, std::size_t size,
	                     std::int32_t &sync);

    /**
     * @brief Generation method for 32 bits signed samples.
     * @param sampleBuffer A pointer to the output buffer to store generated samples.
     * @param size The amount os samples to generate.
     * @param sync An index based reference to signal which element of <ref>sampleBuffer</ref>
	 *          contains the synchronism mark sample.
     * @return The amount of samples that were successfully generated.
     */
    std::size_t generate(std::int32_t *sampleBuffer, std::size_t size,
                         std::int32_t &sync);

    /**
	 * @brief Generation method for 16 bits unsigned samples.
	 * @param sampleBuffer A pointer to the output buffer to store generated samples.
	 * @param size The amount os samples to generate.
	 * @param sync An index based reference to signal which element of <ref>sampleBuffer</ref>
	 *          contains the synchronism mark sample.
	 * @return The amount of samples that were successfully generated.
	 */
	std::size_t generate(std::uint16_t *sampleBuffer, std::size_t size,
	                     std::int32_t &sync);

    /**
     * @brief Generation method for 16 bits signed samples.
     * @param sampleBuffer A pointer to the output buffer to store generated samples.
     * @param size The amount os samples to generate.
     * @param sync An index based reference to signal which element of <ref>sampleBuffer</ref>
	 *          contains the synchronism mark sample.
     * @return The amount of samples that were successfully generated.
     */
    std::size_t generate(std::int16_t *sampleBuffer, std::size_t size,
                         std::int32_t &sync);

	/**
	 * @brief Generation method for 8 bits unsigned samples.
	 * @param sampleBuffer A pointer to the output buffer to store generated samples.
	 * @param size The amount os samples to generate.
	 * @param sync An index based reference to signal which element of <ref>sampleBuffer</ref>
	 *          contains the synchronism mark sample.
	 * @return The amount of samples that were successfully generated.
	 */
	std::size_t generate(std::uint8_t *sampleBuffer, std::size_t size,
	                     std::int32_t &sync);

	/**
	 * @brief Generation method for 8 bits signed samples.
	 * @param sampleBuffer A pointer to the output buffer to store generated samples.
	 * @param size The amount os samples to generate.
	 * @param sync An index based reference to signal which element of <ref>sampleBuffer</ref>
	 *          contains the synchronism mark sample.
	 * @return The amount of samples that were successfully generated.
	 */
	std::size_t generate(std::int8_t *sampleBuffer, std::size_t size,
	                     std::int32_t &sync);

	/**
	 * @brief Reproduction method for previously generated samples.
	 * @param srcBuffer A pointer to the buffer storing the samples to reproduced.
	 * @param dstBuffer A pointer to the buffer to store the samples ready for reproduction.
	 * @param size The amount os samples to reproduced.
	 * @param sync An index based reference to signal which element of <ref>dstBuffer</ref>
	 *          contains the synchronism mark sample.
	 * @return The amount of samples that were successfully reproduced.
	 */
	std::size_t reproduce(const std::float32_t* const srcBuffer, std::int32_t *dstBuffer,
						  std::size_t size, std::int32_t &sync);

	/**
	 * @brief Getter method for scale factor
	 * @return The scale factor for DAC converter
	 */
	std::uint32_t getScaleFactor() const;

	/**
	 * @brief Getter method for DAC dynamic range
	 * @return The dynamic range for DAC converter
	 */
	std::uint32_t getDynamicRange() const;

	/**
	 * @brief Getter method for DAC resolution
	 * @return The DAC converter resolution in bits.
	 */
	std::uint16_t getDacResolution() const;

	/**
	 * @brief Setter method for DAC resolution in bits.
	 * @param dacResolution amount of bits (hardware setting) for DAC converter
	 */
	void setDacResolution(std::uint16_t dacResolution);

private:
	/**
	 * @brief A pointer to any stimuli to generate.
	 */
	Stimuli *stimuli_;

	/**
	 * @brief The DAC resolution
	 */
	std::uint16_t dacResolution_;

	/**
	 * @brief	The dynamic range
	 */
	std::uint32_t dynamicRange_;

	/**
	 * @brief	The dynamic range to scale
	 */
	std::uint32_t dynamicRangeToScale_;

	/**
	 * @brief Prevents the copy of the object.
	 */
	E_DISABLE_COPY(Stim2Dac);
};
} /// end of ASG namespace
#endif //ASG_LIB_STIMDAC_H
