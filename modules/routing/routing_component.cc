/******************************************************************************
 * Copyright 2018 The Apollo Authors. All Rights Reserved.
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

#include "modules/routing/routing_component.h"

#include <utility>

#include "modules/common/adapters/adapter_gflags.h"
#include "modules/routing/common/routing_gflags.h"

DECLARE_string(flagfile);

namespace apollo {
namespace routing {


/**
 * Routing模块对应的配置文件
 * 
 * base_speed: 4.167
 * left_turn_penalty: 50.0
 * right_turn_penalty: 20.0
 * uturn_penalty: 100.0
 * change_penalty: 500.0
 * base_changing_length: 50.0
 * topic_config {
 *   routing_response_topic: "/apollo/routing_response"
 *   routing_response_history_topic: "/apollo/routing_response_history"
 * }
 * **/
bool RoutingComponent::Init() {
  RoutingConfig routing_conf;
  ACHECK(cyber::ComponentBase::GetProtoConfig(&routing_conf))
      << "Unable to load routing conf file: "
      << cyber::ComponentBase::ConfigFilePath();

  AINFO << "Config file: " << cyber::ComponentBase::ConfigFilePath()
        << " is loaded.";

  apollo::cyber::proto::RoleAttributes attr;
  attr.set_channel_name(routing_conf.topic_config().routing_response_topic());
  auto qos = attr.mutable_qos_profile();
  qos->set_history(apollo::cyber::proto::QosHistoryPolicy::HISTORY_KEEP_LAST);
  qos->set_reliability(
      apollo::cyber::proto::QosReliabilityPolicy::RELIABILITY_RELIABLE);
  qos->set_durability(
      apollo::cyber::proto::QosDurabilityPolicy::DURABILITY_TRANSIENT_LOCAL);
  // routing_response_topic: "/apollo/routing_response"    
  response_writer_ = node_->CreateWriter<RoutingResponse>(attr);

  apollo::cyber::proto::RoleAttributes attr_history;
  attr_history.set_channel_name(
      routing_conf.topic_config().routing_response_history_topic());
  auto qos_history = attr_history.mutable_qos_profile();
  qos_history->set_history(
      apollo::cyber::proto::QosHistoryPolicy::HISTORY_KEEP_LAST);
  qos_history->set_reliability(
      apollo::cyber::proto::QosReliabilityPolicy::RELIABILITY_RELIABLE);
  qos_history->set_durability(
      apollo::cyber::proto::QosDurabilityPolicy::DURABILITY_TRANSIENT_LOCAL);
  // routing_response_history_topic: "/apollo/routing_response_history"
  response_history_writer_ = node_->CreateWriter<RoutingResponse>(attr_history);

  std::weak_ptr<RoutingComponent> self =
      std::dynamic_pointer_cast<RoutingComponent>(shared_from_this());

  /**
   * DEFINE_uint32(routing_response_history_interval_ms, 1000,
   *           "ms, emit routing resposne for this time interval");
   * 
   * 周期性的发布历史RoutingResponse
   * **/    
  timer_.reset(new ::apollo::cyber::Timer(
      FLAGS_routing_response_history_interval_ms,
      [self, this]() {
        auto ptr = self.lock();
        if (ptr) {
          std::lock_guard<std::mutex> guard(this->mutex_);
          if (this->response_ != nullptr) {
            auto timestamp = apollo::cyber::Clock::NowInSeconds();
            response_->mutable_header()->set_timestamp_sec(timestamp);
            this->response_history_writer_->Write(*response_);
          }
        }
      },
      false));
  timer_->Start();

  return routing_.Init().ok() && routing_.Start().ok();
}

/**
 * channel: "/apollo/routing_request"
 * **/
bool RoutingComponent::Proc(const std::shared_ptr<RoutingRequest>& request) {
  auto response = std::make_shared<RoutingResponse>();
  
  if (!routing_.Process(request, response.get())) {
    return false;
  }

  common::util::FillHeader(node_->Name(), response.get());
  // routing_response_history_topic: "/apollo/routing_response_history"
  response_writer_->Write(response);

  // 根新历史RoutingResponse
  {
    std::lock_guard<std::mutex> guard(mutex_);
    response_ = std::move(response);
  }
  return true;
}

}  // namespace routing
}  // namespace apollo