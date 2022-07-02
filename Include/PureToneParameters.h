/**
 * @file PureToneParameters.h
 *
 * @brief Defines the parameter for the Pure Tone stimuli.
 * @date 11/12/2017
 * @author <b>Ing. Antonio A. Iznaga Marin.</b>
 */

#ifndef ASG_LIB_PURETONEPARAMETERS_H
#define ASG_LIB_PURETONEPARAMETERS_H

#include "StimuliParameters.h"
#include "ASGMath.h"

namespace ASG {
///Sets Data Alignment to one byte
#pragma pack(push, 1)
/**
 * @brief Defines the parameters for the Pure tone Stimuli generation.
 */
class PureToneParameters : public StimParameters {
public:
    /**
     * @brief Default empty constructor.
     */
    PureToneParameters() : frequency(10.0f) {
    }
    /**
     * @brief The frequency for the generated stimuli.
     */
    std::float32_t frequency;
private:
    /**
     * @brief Prevent object from being copied.
     */
    E_DISABLE_COPY(PureToneParameters);
};
#pragma pack(pop)
}///end of namespace
#endif //ASG_LIB_PURETONEPARAMETERS_H
