#ifndef SOURCEFILES_MODEL_CORE_VALUES_HISTORY_H_
#define SOURCEFILES_MODEL_CORE_VALUES_HISTORY_H_

namespace CommunalCalculator::Core {

struct ValuesHistory {
  float coldWaterPrevious = 0.0;
  float coldWaterCurrent = 0.0;
  float hotWaterPrevious = 0.0;
  float hotWaterCurrent = 0.0;
  float electricityT1Previous = 0.0;
  float electricityT1Current = 0.0;
  float electricityT2Previous = 0.0;
  float electricityT2Current = 0.0;
  float electricityT3Previous = 0.0;
  float electricityT3Current = 0.0;
};

}  // namespace CommunalCalculator::Core

#endif  // SOURCEFILES_MODEL_CORE_VALUES_HISTORY_H_
