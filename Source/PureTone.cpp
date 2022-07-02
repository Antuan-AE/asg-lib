/**
 * @file Source\PureTone.cpp
 *
 * @brief Defines a class for the implementation of pure tone generation.
 * @author	Ing. Antonio A. Iznaga Marin.
 * @date	9/12/2017
 */

#include "PureTone.h"
#include "PureToneParameters.h"

namespace ASG
{
using namespace std;

PureTone::PureTone() :	toneFrequency_(500.0f), phase_(0.0f), stepArgument_(0.0f),
                        periodSize_samples_(0) {
}
PureTone::~PureTone() {

}

bool PureTone::setToneFrequency(float32_t freq) {
    if ((freq <= MIN_GENERATABLE_FREQUENCY ) ||
        (freq >= MAX_GENERATABLE_FREQUENCY)  ||
        (isnan(freq)))
    {
        return false;
    }
    toneFrequency_ = freq;
    setStepArgument();
    ///TODO implement round correction for all frequencies...
    periodSize_samples_ = seconds2samples(getPeriod_secs(), getSamplingFrequency());
    return true;
}

float32_t PureTone::getToneFrequency() const {
    return toneFrequency_;
}

std::float32_t PureTone::getPhase() const {
    return phase_;
}

bool PureTone::setPhase(float32_t phase) {
    phase_ = normalizeRadian(phase);
    return true;
}

bool PureTone::configure(ASG::StimParameters *typeParameters, const std::uint16_t typeSize) {
    if (typeParameters == E_NULLPTR)
        return false;
    ASG::PureToneParameters *param_ = reinterpret_cast<ASG::PureToneParameters*>(typeParameters);
    std::float32_t value = param_->frequency;
    return  this->setToneFrequency(value);
}

size_t PureTone::generate(float32_t *sampleBuffer, std::size_t size, std::int32_t &sync) {
    if (sampleBuffer == NULL || size == 0 ||
        getToneFrequency() == 0.0f || getSamplingFrequency() == 0.0f) {
        return 0;
    }
    bool syncFound = false;
    sync = -1;

    for (size_t index = 0; index < size; index++) {
        sampleBuffer[index] = sin((stepArgument_ * static_cast<float32_t>(getPosition() + index)) + getPhase());

        if (!syncFound) {
            /* true if current position + index is a signal period*/
            if(((getPosition() + index) % periodSize_samples_) == 0) {
                sync = index;
                syncFound = true;
            }
        }
    }

    if((getPosition() + size) >= periodSize_samples_) {
        /*wrap position to the first period of the signal*/
        setPosition((getPosition() + size) % periodSize_samples_);
    } else {
        setPosition(getPosition() + size);
    }
    return size;
}

float32_t PureTone::getPeriod_secs() const {
    return (1.0f / getToneFrequency());
}

void PureTone::setStepArgument() {
    stepArgument_ = ASG::DOUBLE_PI * getToneFrequency() / getSamplingFrequency();
}

uint32_t PureTone::getPeriodSize_samples() const {
    return periodSize_samples_;
}

bool PureTone::setPeriodeSize_samples(std::uint32_t periodeSize_samples) {
    if (periodeSize_samples == 0) {
        return false;
    }
    periodSize_samples_ = periodeSize_samples;
    return true;
}

}///end of namespace
