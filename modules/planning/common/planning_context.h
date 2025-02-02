/******************************************************************************
 * Copyright 2017 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

/**
 * @file
 */

#pragma once

#include "cyber/common/macros.h"
#include "modules/planning/proto/planning_status.pb.h"

/**
 * @brief PlanningContext is the runtime context in planning. It is
 * persistent across multiple frames.
 */
namespace apollo {
namespace planning {

class PlanningContext {
 public:
  PlanningContext() = default;

  void Clear();
  void Init();

  /*
   * please put all status info inside PlanningStatus for easy maintenance.
   * do NOT create new struct at this level.
   * */

  const PlanningStatus& planning_status() const { return planning_status_; }
  PlanningStatus* mutable_planning_status() { return &planning_status_; }

 private:

  /**
   * modules/planning/proto/planning_status.proto
   * 
   * message PlanningStatus {
   * optional BareIntersectionStatus bare_intersection = 1;
   * optional ChangeLaneStatus change_lane = 2;
   * optional CreepDeciderStatus creep_decider = 3;
   * optional CrosswalkStatus crosswalk = 4;
   * optional DestinationStatus destination = 5;
   * optional EmergencyStopStatus emergency_stop = 6;
   * optional OpenSpaceStatus open_space = 7;
   * optional ParkAndGoStatus park_and_go = 8;
   * optional PathDeciderStatus path_decider = 9;
   * optional PullOverStatus pull_over = 10;
   * optional ReroutingStatus rerouting = 11;
   * optional ScenarioStatus scenario = 12;
   * optional SpeedDeciderStatus speed_decider = 13;
   * optional StopSignStatus stop_sign = 14;
   * optional TrafficLightStatus traffic_light = 15;
   * optional YieldSignStatus yield_sign = 16;
   * }
   * 
   * 
   * message ReroutingStatus {
   * optional double last_rerouting_time = 1;
   * optional bool need_rerouting = 2 [default = false];
   * optional apollo.routing.RoutingRequest routing_request = 3;
   * }
   * **/
  PlanningStatus planning_status_;
};

}  // namespace planning
}  // namespace apollo
