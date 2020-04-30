/*
 * @author Ryan Benasutti, WPI
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include "okapi/api/chassis/model/threeEncoderSkidSteerModel.hpp"

namespace okapi {
ThreeEncoderSkidSteerModel::ThreeEncoderSkidSteerModel(
  std::shared_ptr<AbstractMotor> ileftSideMotor,
  std::shared_ptr<AbstractMotor> irightSideMotor,
  std::shared_ptr<ContinuousRotarySensor> ileftEnc,
  std::shared_ptr<ContinuousRotarySensor> irightEnc,
  std::shared_ptr<ContinuousRotarySensor> imiddleEnc,
  const double imaxVelocity,
  const double imaxVoltage)
  : SkidSteerModel(std::move(ileftSideMotor),
                   std::move(irightSideMotor),
                   std::move(ileftEnc),
                   std::move(irightEnc),
                   imaxVelocity,
                   imaxVoltage),
    middleSensor(std::move(imiddleEnc)) {
}

std::valarray<std::int32_t> ThreeEncoderSkidSteerModel::getSensorVals() const {
  // Return the middle sensor last so this is compatible with SkidSteerModel::getSensorVals()
  return std::valarray<std::int32_t>{static_cast<std::int32_t>(leftSensor->get()),
                                     static_cast<std::int32_t>(rightSensor->get()),
                                     static_cast<std::int32_t>(middleSensor->get())};
}

void ThreeEncoderSkidSteerModel::resetSensors() {
  SkidSteerModel::resetSensors();
  middleSensor->reset();
}
} // namespace okapi
