/**
 * @file PureTone.h
 *
 * @brief Declares a class for the pure tone generation.
 * @author	Ing. Antonio A. Iznaga Marin.
 * @date 09/15/2016
 */

#ifndef ASG_LIB_PURETONE_H
#define ASG_LIB_PURETONE_H

#include "Stimuli.h"
#include "ASGMath.h"

namespace ASG {

/**
 * @brief The PureTone class defines and implements a single frequency tone generation.
 */
class PureTone : public Stimuli {
public:

    /**
     * @fn	PureTone::PureTone();
     *
     * @brief	PureTone empty constructor.
     */
    PureTone();

    /**
     * @fn	virtual PureTone::~PureTone();
     *
     * @brief	~PureTone virtual destructor.
     */
    virtual ~PureTone();

    /**
     * @fn	std::float32_t PureTone::getToneFrequency() const;
     *
     * @brief	getToneFrequency access method.
     * @return	The tone frequency of the generated stimulus.
     */
    std::float32_t getToneFrequency() const;

    /**
     * @fn	virtual bool PureTone::setToneFrequency(std::float32_t freq);
     *
     * @brief	setToneFrequency access method.
     * @param	freq: The frequency value in IEEE-754 format to be set for generating the stimulus.
     * @return	True if it succeeds, false if it fails. Failure will occur upon trying to set a negative frequency value.
     */
    virtual bool setToneFrequency(std::float32_t freq);

    /**
     * @fn	std::float32_t PureTone::getPhase() const;
     *
     * @brief	getPhase access method.
     * @return	The phase.
     */
    std::float32_t getPhase() const;

    /**
     * @fn	bool PureTone::setPhase(std::float32_t phase);
     *
     * @brief	Setter method for the phase parameter. This parameters allows to create different
     *          sinusoidal samples from the same mathematical function.
     * @param	phase:	The phase value in IEEE-754 format to be set for generating the stimulus.
     * @return	True is always returned.
     */
    bool setPhase(std::float32_t phase);

    /**
     * @fn std::size_t generate(std::float32_t *sampleBuffer, std::size_t size, std::int32_t &sync);
     *
     * @brief Concrete implementation for the Pure Tone Stimuli.
     * @param sampleBuffer A pointer to the output buffer to store generated samples.
     * @param size The amount os samples to generate.
     * @param sync An index based reference to signal which element of <ref>sampleBuffer</ref>
	 *          contains the synchronism mark sample.
     * @return The amount of samples that were successfully generated.
     */
    virtual std::size_t generate(std::float32_t *sampleBuffer, std::size_t size, std::int32_t &sync) E_DECLARE_OVERRIDE;

    /**
     * @fn bool configure(ASG::StimParameters *typeParameters, const std::uint16_t typeSize);
     *
     * @brief Configuration method. Each stimuli will be generated after being
	 * 			properly configured by type parameters.
     * @param typeParameters Data structure tailored for each stimuli to be generated.
     * @param typeSize Amount of bytes for data structure holding each parameter
	 * 					type.
     * @return True on success, false if it fails.
     */
    virtual bool configure(ASG::StimParameters *typeParameters, const std::uint16_t typeSize);

    /**
     * @fn	virtual std::float32_t PureTone::getPeriod_secs() const E_DECLARE_OVERRIDE;
     *
     * @brief Getter method for the signal (stimuli) period in seconds.
     * @return	The period in seconds.
     */
    virtual std::float32_t getPeriod_secs() const E_DECLARE_OVERRIDE;

    /**
     * @fn	void PureTone::setStepArgument();
     *
     * @brief	Sets step argument
     */
    void setStepArgument();

    /**
     * @fn	std::uint32_t PureTone::getPeriodSize_samples() const;
     *
     * @brief	Gets period size samples.
     * @return	The period size samples.
     */
    std::uint32_t getPeriodSize_samples() const;

    /**
     * @fn bool setPeriodeSize_samples(std::uint32_t periodeSize_samples);
     *
     * @brief Setter method for the amount of samples in a full period of the
     *          signal (Stimuli)
     * @param periodeSize_samples
     * @return True on success, false if it fails.
     */
    bool setPeriodeSize_samples(std::uint32_t periodeSize_samples);

protected:
    /**
     * @brief The frequency to generate the stimuli.
     */
    std::float32_t toneFrequency_;

    /**
     * @brief The phase to generate the stimuli.
     */
    std::float32_t  phase_;

private:
    /**
     * @brief Prevents object from being copied.
     */
    E_DISABLE_COPY(PureTone);

    /**
     * @brief	The step argument
     */
    std::float32_t stepArgument_;

    /**
     * @brief	The period size samples
     */
    std::uint32_t periodSize_samples_;
};
}///end of namespace
#endif //ASG_LIB_PURETONE_H
