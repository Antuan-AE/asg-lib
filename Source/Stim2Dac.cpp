/**
 * @file Stim2Dac.cpp
 *
 * @brief Implements generic converter adapter
 * @date 11/13/2017
 * @author <b>Ing. Antonio A. Iznaga Marin.</b>
 */
#include "Stim2Dac.h"
#include "Stimuli.h"

namespace ASG
{

using namespace std;

Stim2Dac::Stim2Dac(ASG::Stimuli *stimuli, uint16_t dacResolution) : stimuli_(stimuli) {
	setDacResolution(dacResolution);
}

Stimuli* Stim2Dac::getStimuli() const {
	return stimuli_;
}
void Stim2Dac::setStimuli(Stimuli* stimuli) {
	stimuli_ = stimuli;
}

std::size_t Stim2Dac::generate(uint32_t* sampleBuffer, size_t size, int32_t& sync) {
    if (sampleBuffer == E_NULLPTR || stimuli_ == E_NULLPTR ||
        dacResolution_ > 32 || size <= 1) {
        return 0;
    }

    size_t retval = 0;
    int32_t syncTmp = -1;
    float32_t tmpValue = 0.0f;
    bool isSyncFounded = false;

    for (size_t index = 0; index < size; index++) {
        retval = stimuli_->generate(&tmpValue, 1, syncTmp);
        // if for some reason the stim stops generating return
        if (retval == 0) {
            return index;
        }
        // from +-1, to 0 to dynamicrange-1, for example for 8bits signed is to 255 to 0
        sampleBuffer[index] = static_cast<uint32_t>(ASG::round(((tmpValue+1.0f)/2.0f  * (dynamicRange_ - 1))));

        //only account for the first sync mark found
        if (isSyncFounded == false) {
            if (syncTmp != -1) {
                sync = index;
                isSyncFounded = true;
            }
        }
    }
    return size;
}

std::size_t Stim2Dac::generate(int32_t *sampleBuffer, std::size_t size, int32_t& sync) {
    if (sampleBuffer == E_NULLPTR || dacResolution_ > 32) {
        return 0;
    }

    sync = -1;
    size_t retval = 0;
    int32_t syncTmp = -1;
    float32_t tmpValue = 0.0f;

    bool isSyncFounded = false;
    for (size_t index = 0; index < size; ++index) {
        retval = stimuli_->generate(&tmpValue, 1, syncTmp);
        // if for some reason the stim stops generating return
        if (retval == 0) {
            return index;
        }
        // from +-1 to +-dynamicrange/2, for example for 8bits signed is to +- 127
        sampleBuffer[index] = static_cast<int32_t>(tmpValue * dynamicRangeToScale_);

        //only account for the first sync mark found
        if (isSyncFounded == false) {
            if (syncTmp != -1) {
                sync = index;
                isSyncFounded = true;
            }
        }
    }
    return size;
}

std::size_t Stim2Dac::generate(uint16_t* sampleBuffer, size_t size, int32_t& sync) {
    if (sampleBuffer == E_NULLPTR || dacResolution_ > 16) {
        return 0;
    }
    size_t retval = 0;
    int32_t syncTmp = -1;
    float32_t tmpValue = 0.0f;

    bool isSyncFounded = false;
    for (size_t index = 0; index < size; ++index) {
        retval = stimuli_->generate(&tmpValue, 1, syncTmp);
        // if for some reason the stim stops generating return
        if (retval == 0) {
            return index;
        }
        // from +-1, to 0 to dynamicrange-1, for example for 8bits signed is to 255 to 0
        sampleBuffer[index] = static_cast<uint16_t>(round((tmpValue+1.0f)/2.0f  * (dynamicRange_ - 1)));

        //only account for the first sync mark found
        if (isSyncFounded == false) {
            if (syncTmp != -1) {
                sync = syncTmp;
                isSyncFounded = true;
            }
        }
    }
    return size;
}

std::size_t Stim2Dac::generate(int16_t* sampleBuffer, std::size_t size, int32_t& sync) {
    if (sampleBuffer == E_NULLPTR || dacResolution_ > 16) {
        return 0;
    }

    size_t retval = 0;
    int32_t syncTmp = -1;
    float32_t tmpValue = 0.0f;

    bool isSyncFounded = false;
    for (size_t index = 0; index < size; ++index) {
        retval = stimuli_->generate(&tmpValue, 1, syncTmp);
        // if for some reason the stim stops generating return
        if (retval == 0) {
            return index;
        }

        sampleBuffer[index] = static_cast<int16_t>(tmpValue * dynamicRangeToScale_);

        //only account for the first sync mark found
        if (isSyncFounded == false) {
            if (syncTmp != -1) {
                sync = syncTmp;
                isSyncFounded = true;
            }
        }
    }
    return size;
}

size_t Stim2Dac::generate(uint8_t* sampleBuffer, size_t size, int32_t& sync) {
    if (sampleBuffer == E_NULLPTR || dacResolution_ > 8) {
        return 0;
    }
    size_t retval = 0;
    int32_t syncTmp = -1;
    float32_t tmpValue = 0.0f;

    bool isSyncFounded = false;
    for (size_t index = 0; index < size; ++index) {
        retval = stimuli_->generate(&tmpValue, 1, syncTmp);

        if (retval == 0) {
            return index;
        }
        // from +-1, to 0 to dynamicrange-1, for example for 8bits signed is to 255 to 0
        sampleBuffer[index] = static_cast<uint8_t>(ASG::round((tmpValue+1.0f)/2.0f  * (dynamicRange_ - 1)));

        //only account for the first sync mark found
        if (isSyncFounded == false) {
            if (syncTmp != -1) {
                sync = syncTmp;
                isSyncFounded = true;
            }
        }
    }
    return size;
}

size_t Stim2Dac::generate(int8_t* sampleBuffer, size_t size, int32_t& sync) {
    if (sampleBuffer == E_NULLPTR || dacResolution_ > 8) {
        return 0;
    }

    size_t retval = 0;
    int32_t syncTmp = -1;
    float32_t tmpValue = 0.0f;

    bool isSyncFounded = false;
    for (size_t index = 0; index < size; ++index) {
        retval = stimuli_->generate(&tmpValue, 1, syncTmp);

        if (retval == 0) {
            return index;
        }

        sampleBuffer[index] = static_cast<int8_t>(tmpValue * dynamicRangeToScale_);

        //only account for the first sync mark found
        if (isSyncFounded == false) {
            if (syncTmp != -1) {
                sync = syncTmp;
                isSyncFounded = true;
            }
        }
    }
    return size;
}

std::uint16_t Stim2Dac::getDacResolution() const {
    return dacResolution_;
}

void Stim2Dac::setDacResolution(std::uint16_t dacResolution) {
    dacResolution_ = dacResolution;
    dynamicRange_ = ASG::pow(2, dacResolution);
    dynamicRangeToScale_ = (dynamicRange_ / 2) - 1;
}

std::uint32_t Stim2Dac::getScaleFactor() const {
    return dynamicRangeToScale_;
}

std::uint32_t Stim2Dac::getDynamicRange() const {
    return dynamicRange_;
}

}///end of namespace
