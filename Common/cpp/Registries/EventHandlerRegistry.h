#pragma once

#include <jsi/jsi.h>
#include <map>
#include <memory>
#include <mutex>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

using namespace facebook;

namespace reanimated {

class WorkletEventHandler;

class EventHandlerRegistry {
  std::map<
      std::string,
      std::unordered_map<unsigned long, std::shared_ptr<WorkletEventHandler>>>
      eventMappings;
  std::map<unsigned long, std::shared_ptr<WorkletEventHandler>> eventHandlers;
  std::mutex instanceMutex;

 public:
  void registerEventHandler(std::shared_ptr<WorkletEventHandler> eventHandler);
  void unregisterEventHandler(unsigned long id);

#ifdef RCT_NEW_ARCH_ENABLED
  void processEvent(
      jsi::Runtime &rt,
      double eventTimestamp,
      std::string eventName,
      jsi::Value &eventPayload);
#else
  void processEvent(
      jsi::Runtime &rt,
      double eventTimestamp,
      std::string eventName,
      std::string eventPayload);
#endif

  bool isAnyHandlerWaitingForEvent(std::string eventName);
};

} // namespace reanimated
