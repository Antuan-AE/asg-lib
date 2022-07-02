/**
 * @file Stimuli.h
 *
 * @brief Declares a base class for all stimuli's generation.
 * @author	Ing. Antonio A. Iznaga Marín.
 * @date	11/06/2017
 */
#ifndef STIMBASE_H
#define STIMBASE_H

#include "ASGMath.h"

/**
 * @brief Auditory Stimulator Generator API namespace.
 */
namespace ASG
{
	///Forward declaration for generated stimuli parameters class.
	class StimParameters;
/**
 * @brief Base class for stimuli generation.
 *
 * @remarks This class is an interface to be implemented by all generated
 * stimuli.
 */
class Stimuli
{
public:
	/**
	 * @fn Stimuli::Stimuli();
	 *
	 * @brief Stimuli constructor. This class is an interface for each
	 * stimuli to be generated or reproduced by the core APP.
	 */
	Stimuli();

	/**
	 * @fn virtual ~Stimuli();
	 *
	 * @brief virtual destructor
	 */
	virtual ~Stimuli();

	/**
	 * @fn virtual std::size_t generate(std::float32_t *sBuffer, std::size_t size,
	 * 									std::int32_t &sync) = 0;
	 *
	 * @brief Generation method. Each stimuli will generate its own based on this
	 * 			simple interface.
	 * @param [out] sBuffer: Buffer to store generated samples.
	 * @param size Amount of samples to be generated.
	 * @param [out] sync Index marking sample inside Buffer for synchronism mark.
	 * @return Amount of samples generated. Zero for error on generation method.
	 */
	virtual std::size_t generate(std::float32_t *sBuffer, std::size_t size,
								 std::int32_t &sync) = 0;

	/**
	 * @fn 	virtual std::size_t reproduce(const std::float32_t* const srcBuffer,
	 * 										std::float32_t *dstBuffer,
	 * 										std::size_t size, std::int32_t &sync) = 0;
	 *
	 * @brief Reproduction method. Some stimuli cannot be generated but instead
	 * 			will be reproduced from previuosly stored samples on memory using
	 * 			this common interfase.
	 * @param [in] srcBuffer: Buffer storing previously generated samples to be reproduced.
	 * @param [out] dstBuffer: Buffer to store samples to be reproduced after being properly
	 * 							normalized to target system.
	 * @param size	Amount of samples to be reproduced.
	 * @param [out] sync Index marking sample inside Buffer for sinchronism mark.
	 * @return Amount of samples reproduced. Zero for error.
	 */
	virtual std::size_t reproduce(const std::float32_t* const srcBuffer,
								  std::float32_t *dstBuffer,
								  std::size_t size, std::int32_t &sync) = 0;

	/**
	 * @fn bool configure(ASG::StimParameters *typeParameters,
	 * 						const std::uint16_t typeSize) = 0;
	 *
	 * @brief Configuration method. Each stimuli will be generated after being
	 * 			properly configured by type parameters.
	 * @param typeParameters Data structure tailored for each stimuli to be generated.
	 * @param typeSize Amount of bytes for data structure holding each parameter
	 * 					type.
	 * @return True on success, false if it fails.
	 */
	virtual bool configure(ASG::StimParameters *typeParameters,
						   const std::uint16_t typeSize) = 0;

	/**
	 * @fn bool configure(ASG::StimParameters *typeParameters,
	 * 						const std::uint16_t typeSize,
	 * 						const std::uint8_t earSide) = 0;
	 *
	 * @brief Overload configuration method. Some stimuli are generated with different
	 * 			configurations on each ear simultaneously.
	 * @param typeParameters Data structure tailored for each stimuli to be generated.
	 * @param typeSize Amount of bytes for data structure holding each parameter
	 * 					type.
	 * @param earSide Specify ear to configure.
	 * @return True on success, false if it fails.
	 */
	virtual bool configure(ASG::StimParameters *typeParameters,
						   const std::uint16_t typeSize,
						   const std::uint8_t earSide) = 0;

	/**
	 * @fn std::float32_t getPeriod_secs() const = 0;
	 *
	 * @brief Getter method for period of stimuli.
	 * @return Amount of seconds for a period of the stimuli.
	 */
	virtual std::float32_t getPeriod_secs() const = 0;

	/**
	 * @fn std::uint32_t getPosition() const;
	 *
	 * @brief Getter method for the index position of last
	 * 		generated sample. Next generation will start at
	 * 		position + 1.
	 * @return The Index of last generated sample.
	 */
	std::uint32_t getPosition() const;

	/**
	 * @fn bool setPosition(std::uint32_t position);
	 *
	 * @brief Setter method position
	 * @param position The index marking the position to start
	 * 			the next generation.
	 * @return True if success, false if it fails.
	 */
	virtual bool setPosition(std::uint32_t position);

	/**
	 * @fn bool resetPosition();
	 *
	 * @brief Set Index for position to zero.
	 * @return True if success, false if it fails.
	 */
	virtual bool resetPosition();

	/**
	 * @fn std::float32_t getSamplingFrequency() const;
	 *
	 * @brief Getter method to retrieve the stimuli sampling frequency.
	 * @return The Stimuli sampling frequency for generation.
	 */
	std::float32_t getSamplingFrequency() const;

	/**
	 * @fn bool setSamplingFrequency(std::float32_t samplingFrequency);
	 *
	 * @brief Setter method for sampling frecuency for stimuli generation.
	 * @param samplingFrequency IEEE-754 value to be set as sampling frecuency
	 * 			for stimuli generation.
	 * @return True on success, false if it fails (ie negative value)
	 */
	virtual bool setSamplingFrequency(std::float32_t samplingFrequency);

	/**
	 * @fn std::uint32_t leastCommonMultiple(std::uint32_t numberA,
	 * 										std::uint32_t numberB);
	 *
	 * @brief Calculates the least common multiple needed for generating frequencies.
	 * @param numA first integer parameter
	 * @param numB second integer parameter
	 * @return The least common multiple for the parameters.
	 */
	std::uint32_t leastCommonMultiple(std::uint32_t numA, std::uint32_t numB);

protected:
	/**
	 * @brief Last generated sample Index for next call.
	 * @remarks It holds the position index based for the last generated sample.
	 */
	std::uint32_t position_;

	/**
	 * @brief The sampling frequency for the generated stimuli.
	 */
	std::float32_t samplingFrequency_;

	/**
	 * @brief Constant for single value sample.
	 */
	static const std::size_t SINGLE_SAMPLE = 1;

private:
	/**
	 * @brief Prevents duplication of these object.
	 */
	E_DISABLE_COPY(Stimuli);

};
}///end of namespace
#endif /*STIMBASE_H*/
