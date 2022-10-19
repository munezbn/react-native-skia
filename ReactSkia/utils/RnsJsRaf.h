
#include<iostream>

#include <jsi/JSIDynamic.h>
#include <jsi/instrumentation.h>

#include "ReactSkia/utils/RnsLog.h"

using namespace facebook::jsi;

namespace facebook {
namespace react {

class RnsJsRequestAnimation {
 public:
  RnsJsRequestAnimation(const std::function<void(double)>& callback);
  virtual ~RnsJsRequestAnimation() { };

  void start();
  void stop();

  static uint64_t nextUniqueId();

 private :
   bool isActive_{false};
   Value rafId_;
   std::string callbackName_;
   //HostFunctionType rafNativeCallback_;

  facebook::jsi::Value RnsRequestAnimationFrame();
  void RnsCancelAnimationFrame();
};


} // namespace react
} // namespace facebook

