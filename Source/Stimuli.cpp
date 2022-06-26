/**
 * @file Stimuli.cpp
 *
 * @brief Defines a base class for the implementation of all stimuli's generation.
 * @author	Ing. Antonio A. Iznaga Marín.
 * @date	11/06/2017
 */

#include "Stimuli.h"

namespace ASG
{
using namespace std;

Stimuli::Stimuli() : position_(0), samplingFrequency_(1.0f) {}

Stimuli::~Stimuli() {}

std::uint32_t Stimuli::getPosition() const {
	return position_;
}

bool Stimuli::setPosition(std::uint32_t position) {
	position_ = position;
	return true;
}

bool Stimuli::resetPosition() {
	return setPosition(0);
}

float32_t Stimuli::getSamplingFrequency() const {
	return samplingFrequency_;
}

bool Stimuli::setSamplingFrequency(std::float32_t samplingFrequency) {
	if (samplingFrequency <= 0.0f || isnan(samplingFrequency)) {
		return false;
	}
	samplingFrequency_ = samplingFrequency;
	return true;
}

std::uint32_t Stimuli::leastCommonMultiple(std::uint32_t numA, std::uint32_t numB) {
	uint32_t originalNumberA = numA;
	uint32_t originalNumberB = numB;
	uint32_t result = 0;

	for(;;)
	{
		if(numA == 0)
		{
			result = numB;
			break;
		}
		numB %= numA;
		if(numB == 0)
		{
			result = numA;
			break;
		}
		numA %= numB;
	}
	return (result) ? (originalNumberA / result * originalNumberB) : 0;
}
} /// end of ASG namespace
