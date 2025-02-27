/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <cxxreact/JsArgumentHelpers.h>

#include "ReactSkia/utils/RnsLog.h"

#include "UiManagerModule.h"

// Reference : react-native/ReactCommon/cxxreact/SampleCxxModule.cpp

using namespace folly;

namespace facebook {
namespace xplat {
namespace uimanager {

dynamic Uimanager::getConstantsForViewManager(std::string viewManagerName) {
  if(viewManagerName == "RCTView") {
    auto nativeProps = folly::dynamic::object("onLayout", true)("pointerEvents", true)
#if defined(TARGET_OS_TV) && TARGET_OS_TV
      ("focusable", true)("isTVSelectable", true)
      ("hasTVPreferredFocus", true)("tvParallaxProperties", true)("nextFocusUp", true)
      ("nextFocusDown", true)("nextFocusLeft", true)("nextFocusRight", true)
#endif //TARGET_OS_TV
      ("overflow", true);

    auto bubblingEventTypes = folly::dynamic::object();
    auto directEventTypes = folly::dynamic::object("topLayout", folly::dynamic::object("registrationName", "onLayout"))(
      "topContentSizeChange", folly::dynamic::object("registrationName", "onContentSizeChange"))(
      "topSelectionChange", folly::dynamic::object("registrationName", "onSelectionChange"))(
      "topScroll",folly::dynamic::object("registrationName","onScroll"));

    auto registry = folly::dynamic::object(
        NATIVE_PROPS_KEY, std::move(nativeProps))(
        BUBBLING_EVENTS_KEY, std::move(bubblingEventTypes))(
        DIRECT_EVENTS_KEY, std::move(directEventTypes));
    return {std::move(registry)};
  } else if (viewManagerName == "RCTActivityIndicatorView") {
    auto nativeProps = folly::dynamic::object("color", "UIColor")("animating",true)("hidesWhenStopped",true)("size",true);
    auto registry = folly::dynamic::object(
        NATIVE_PROPS_KEY, std::move(nativeProps))(
        BASE_MODULE_NAME_KEY, "RCTView");
    return {std::move(registry)};
  } else if (viewManagerName == "RCTImageView") {
     auto nativeProps = folly::dynamic::object("blurRadius", true)(
      "defaultSrc", true)("fadeDuration", true)("headers", true)(
      "loadingIndicatorSrc", true)("onError", true)("onLoad", true)(
      "onLoadEnd", true)("onLoadStart", true)("onPartialLoad", true)(
      "onProgress", true)("progressiveRenderingEnabled", true)(
      "resizeMethod", true)("resizeMode", true)(
      "shouldNotifyLoadEvents", true)("source", true)("src", true)
      ("capInsets", "UIEdgeInsets") // NOTE(kudo): Trick to leverage ios type transform for UIEdgeInsets to insetsDiffer
      ("overlayColor", "UIColor")("tintColor", "UIColor") // NOTE(kudo): Trick to leverage ios type transform for UIColor to processColor
      ("defaultSource", "UIImage"); // NOTE(kudo): Trick to leverage ios type transform for UIImage to resolveAssetSource

    auto bubblingEventTypes = folly::dynamic::object();
    auto directEventTypes = folly::dynamic::object(
      "topLoadStart", folly::dynamic::object("registrationName", "onLoadStart"))(
      "topProgress", folly::dynamic::object("registrationName", "onProgress"))(
      "topError", folly::dynamic::object("registrationName", "onError"))(
      "topPartialLoad", folly::dynamic::object("registrationName", "onPartialLoad"))(
      "topLoad", folly::dynamic::object("registrationName", "onLoad"))(
      "topLoadEnd", folly::dynamic::object("registrationName", "onLoadEnd"));

    auto registry = folly::dynamic::object(
        NATIVE_PROPS_KEY, std::move(nativeProps))(
        BASE_MODULE_NAME_KEY, "RCTView")(
        BUBBLING_EVENTS_KEY, std::move(bubblingEventTypes))(
        DIRECT_EVENTS_KEY, std::move(directEventTypes));
    return {std::move(registry)};
  } else if (viewManagerName == "RCTSinglelineTextInputView") {
    auto nativeProps = folly::dynamic::object("allowFontScaling", true)("autoComplete",true)("autoCorrect",true)("autoFocus",true)(
      "blurOnSubmit",true)(
      "caretHidden",true)("clearButtonMode",true)("clearTextOnFocus",true)("contextMenuHidden",true)(
      "dataDetectorTypes",true)("defaultValue",true)("disableFullscreenUI",true)(
      "editable",true)("enablesReturnKeyAutomatically",true)(
      "importantForAutofil",true)("inlineImageLeft",true)("inlineImagePadding",true)("inputAccessoryViewID",true)(
      "keyboardAppearance",true)("keyboardType",true)(
      "maxFontSizeMultiplier",true)("maxLength",true)("multiline",true)(
      "numberOfLines",true)(
      "placeholder",true)("placeholderTextColor","UIColor")(  // Using of UIColor, since we are using platform type as iOS for app bundle , iOS type is been used.
      "text",true)(
      "returnKeyLabel",true)("returnKeyType",true)("rejectResponderTermination",true)(
      "scrollEnabled",true)("secureTextEntry",true)("selection",true)("selectionColor","UIColor")("selectTextOnFocus",true)("showSoftInputOnFocus",true)("spellCheck",true)(
      "textAlign",true)("textContentType",true)(
      "passwordRules",true)(
      "style",true)(
      "textBreakStrategy",true)(
      "underlineColorAndroid","UIColor")(
      "value",true);

    auto directEventTypes = folly::dynamic::object();

    auto bubblingEventTypes = folly::dynamic::object(
      "topBlur",
      folly::dynamic::object("phasedRegistrationNames", folly::dynamic::object("bubbled","onBlur")("captured", "onBlurCapture")))(
      "topChange",
      folly::dynamic::object("phasedRegistrationNames", folly::dynamic::object("bubbled","onChange")("captured", "onChangeCapture")))(
      "topEndEditing",
      folly::dynamic::object("phasedRegistrationNames", folly::dynamic::object("bubbled","onEndEditing")("captured", "onEndEditingCapture")))(
      "topFocus",
      folly::dynamic::object("phasedRegistrationNames", folly::dynamic::object("bubbled","onFocus")("captured", "onFocusCapture")))(
      "topKeyPress",
      folly::dynamic::object("phasedRegistrationNames", folly::dynamic::object("bubbled","onKeyPress")("captured", "onKeyPressCapture")))(
      "topSubmitEditing",
      folly::dynamic::object("phasedRegistrationNames", folly::dynamic::object("bubbled","onSubmitEditing")("captured", "onSubmitEditing")));

    auto registry = folly::dynamic::object(
        NATIVE_PROPS_KEY, std::move(nativeProps))(
        BASE_MODULE_NAME_KEY, "RCTView")(
        BUBBLING_EVENTS_KEY, std::move(bubblingEventTypes))(
        DIRECT_EVENTS_KEY, std::move(directEventTypes));
    return {std::move(registry)};
  } else if (viewManagerName == "RCTScrollContentView") { // Same as RCTView ?? May be add with (RCTView || RCTScrollContentView)
      auto nativeProps = folly::dynamic::object("onLayout", true);
      auto registry = folly::dynamic::object(
        NATIVE_PROPS_KEY, std::move(nativeProps))(
        BASE_MODULE_NAME_KEY, "RCTView");
      return {std::move(registry)};
  } else if (viewManagerName == "RCTScrollView") {
    auto nativeProps = folly::dynamic::object("alwaysBounceHorizontal", false)(
      "alwaysBounceVertical", false)("automaticallyAdjustContentInsets", false)(
      "bounces", true)("bouncesZoom", false)(
      "canCancelContentTouches", false)("centerContent", false)(
      "contentInset",true)("contentOffset",true)("contentInsetAdjustmentBehavior",false)(
      "decelerationRate", false)("directionalLockEnabled", false)("disableIntervalMomentum", false)(
      "endFillColor",true)(
      "fadingEdgeLength", true)(
      "indicatorStyle", true)(
      "keyboardDismissMode", false)(
      "maintainVisibleContentPosition", false)("maximumZoomScale", false)("minimumZoomScale", false)(
      "nestedScrollEnabled", false)(
      "onMomentumScrollBegin", false)("onMomentumScrollEnd", false)("onScroll", true)(
      "onScrollBeginDrag", false)("onScrollEndDrag", false)("onScrollToTop", false)("overScrollMode", false)(
      "pagingEnabled", true)("persistentScrollbar", true)("pinchGestureEnabled",false)(
      "scrollIndicatorInsets", true)("scrollEnabled", true)("scrollEventThrottle", true)(
      "scrollToOverflowEnabled", false)("scrollsToTop", false)("sendMomentumEvents", false)(
      "showsHorizontalScrollIndicator", true)("showsVerticalScrollIndicator", true)(
      "snapToAlignment", true)("snapToEnd", true)("snapToInterval", true)(
      "snapToOffsets", true)("snapToStart", true)(
      "zoomScale", true);
    auto bubblingEventTypes = folly::dynamic::object();
    auto directEventTypes = folly::dynamic::object();

    auto registry = folly::dynamic::object(
        NATIVE_PROPS_KEY, std::move(nativeProps))(
        BASE_MODULE_NAME_KEY, "RCTView")(
        BUBBLING_EVENTS_KEY, std::move(bubblingEventTypes))(
        DIRECT_EVENTS_KEY, std::move(directEventTypes));
    return {std::move(registry)};
  } else if (viewManagerName == "RCTSafeAreaView") {
    auto registry = folly::dynamic::object(
        NATIVE_PROPS_KEY, folly::dynamic::object())(
        BASE_MODULE_NAME_KEY, "RCTView")(
        BUBBLING_EVENTS_KEY, folly::dynamic::object())(
        DIRECT_EVENTS_KEY, folly::dynamic::object());
    return {std::move(registry)};
  } else {
    RNS_LOG_INFO("viewManager : " << viewManagerName << " not available in default list, check in thirdparty list");
  }

  // Reached here only if it doesnt find any view manager in default inbuilt-list
  return Uimanager::getConstantsForThirdpartyViewManager(viewManagerName);
}

void Uimanager::updateView(int viewTag, std::string viewManagerName, dynamic props, bool flushDisplay) {
  RSkComponentProvider* provider = viewManagerName.empty() ?
                                      componentViewRegistry_->GetProvider(viewTag) :
                                      componentViewRegistry_->GetProvider(viewManagerName.c_str());

  if(provider == nullptr) {
    RNS_LOG_ERROR("Unable to updateView,invalid provider for view tag (" << viewTag << ") name (" << viewManagerName << ") !!");
    return;
  }
  const ComponentDescriptor* componentDescriptor = componentViewRegistry_->getComponentDescriptor(provider->GetDescriptorProvider().handle);
  auto component = provider->GetComponent(viewTag);

  if((componentDescriptor != nullptr) && (component != nullptr)) {

    SharedProps oldProps = component->getComponentData().props;
    SharedProps newProps = componentDescriptor->cloneProps(oldProps,RawProps(props));

    if(flushDisplay) {
      component->layer()->client().notifyFlushBegin();
      RnsShell::LayerInvalidateMask invalidateMask = component->updateProps(newProps,false);
      component->drawAndSubmit(invalidateMask);
      component->layer()->client().notifyFlushRequired();
    } else {
      RnsShell::LayerInvalidateMask invalidateMask = component->updateProps(newProps,false);
      component->drawAndSubmit(invalidateMask);
    }
  } else {
    RNS_LOG_WARN("Unable to updateView, invalid componentDescriptor[" << componentDescriptor << "] or component[" << component << "], for " << viewManagerName << " tag (" << viewTag << ")");
  }
}

std::shared_ptr<RSkComponent> Uimanager::getComponent(int viewTag) {
  RSkComponentProvider* provider = componentViewRegistry_->GetProvider(viewTag);

  if(provider == nullptr) {
    RNS_LOG_ERROR("Unable to get provider for view tag (" << viewTag << ") !!");
    return nullptr;
  }
  return(provider->GetComponent(viewTag));
}

std::string Uimanager::viewNameForReactTag(int viewTag) {
  RSkComponentProvider* provider = componentViewRegistry_->GetProvider(viewTag);
  if(provider == nullptr) {
    RNS_LOG_ERROR("Unable to get viewName, invalid provider for tag (" << viewTag << ") !!");
    return "UnknownView";
  }
  return provider->GetDescriptorProvider().name;
}

// Module

UimanagerModule::UimanagerModule(std::unique_ptr<Uimanager> uimanager)
    : uimanager_(std::move(uimanager)) {}

std::string UimanagerModule::getName() {
  return "UIManager";
}

auto UimanagerModule::getConstants() -> std::map<std::string, folly::dynamic> {
  return {};
}

auto UimanagerModule::getMethods() -> std::vector<Method> {
  return {
      Method(
          "getConstantsForViewManager",
          [this] (dynamic args) -> dynamic {
            return(uimanager_->getConstantsForViewManager(jsArgAsString(args, 0)));
          },
          SyncTag),
      Method(
          "updateView",
          [this] (dynamic args) {
            uimanager_->updateView(jsArgAsInt(args, 0), jsArgAsString(args, 1), jsArgAsDynamic(args, 2));
          }),
  };
}

void UimanagerModule::updateViewForReactTag(int viewTag, std::string viewName, folly::dynamic newProps, bool flushDisplay) {
  // TODO schedule in MAIN thread if it is not aleady in main thread
  uimanager_->updateView(viewTag, std::string(), newProps, flushDisplay);
}

std::shared_ptr<RSkComponent> UimanagerModule::getComponentForReactTag(int viewTag) {
  return uimanager_->getComponent(viewTag);
}

std::string UimanagerModule::getViewNameForReactTag(int viewTag) {
  return uimanager_->viewNameForReactTag(viewTag);
}

std::unique_ptr<xplat::module::CxxModule> UimanagerModule::createModule(ComponentViewRegistry *componentViewRegistry) {
  return std::make_unique<facebook::xplat::uimanager::UimanagerModule>(
      std::make_unique<facebook::xplat::uimanager::Uimanager>(componentViewRegistry));
}

} // namespace uimanager
} // namespace xplat
} // namespace facebook
