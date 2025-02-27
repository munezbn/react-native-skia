
/**
 * This code was generated by [react-native-codegen](https://www.npmjs.com/package/react-native-codegen).
 *
 * Do not edit this file as changes may cause incorrect behavior and will be lost
 * once the code is regenerated.
 *
 * @generated by codegen project: GeneratePropsCpp.js
 */

#include <react/renderer/components/rncore/Props.h>
#include <react/renderer/components/image/conversions.h>
#include <react/renderer/core/propsConversions.h>

namespace facebook {
namespace react {

ActivityIndicatorViewProps::ActivityIndicatorViewProps(
    
    const ActivityIndicatorViewProps &sourceProps,
    const RawProps &rawProps): ViewProps( sourceProps, rawProps),

    hidesWhenStopped(convertRawProp( rawProps, "hidesWhenStopped", sourceProps.hidesWhenStopped, {false})),
    animating(convertRawProp( rawProps, "animating", sourceProps.animating, {false})),
    color(convertRawProp( rawProps, "color", sourceProps.color, {})),
    size(convertRawProp( rawProps, "size", sourceProps.size, {ActivityIndicatorViewSize::Small}))
      {}
DatePickerProps::DatePickerProps(
    
    const DatePickerProps &sourceProps,
    const RawProps &rawProps): ViewProps( sourceProps, rawProps),

    date(convertRawProp( rawProps, "date", sourceProps.date, {0.0})),
    initialDate(convertRawProp( rawProps, "initialDate", sourceProps.initialDate, {0.0})),
    locale(convertRawProp( rawProps, "locale", sourceProps.locale, {})),
    maximumDate(convertRawProp( rawProps, "maximumDate", sourceProps.maximumDate, {0.0})),
    minimumDate(convertRawProp( rawProps, "minimumDate", sourceProps.minimumDate, {0.0})),
    minuteInterval(convertRawProp( rawProps, "minuteInterval", sourceProps.minuteInterval, {DatePickerMinuteInterval::MinuteInterval1})),
    mode(convertRawProp( rawProps, "mode", sourceProps.mode, {DatePickerMode::Date})),
    timeZoneOffsetInMinutes(convertRawProp( rawProps, "timeZoneOffsetInMinutes", sourceProps.timeZoneOffsetInMinutes, {0.0})),
    pickerStyle(convertRawProp( rawProps, "pickerStyle", sourceProps.pickerStyle, {DatePickerPickerStyle::Spinner}))
      {}
RCTMaskedViewProps::RCTMaskedViewProps(
    
    const RCTMaskedViewProps &sourceProps,
    const RawProps &rawProps): ViewProps( sourceProps, rawProps)

    
      {}
RCTProgressViewProps::RCTProgressViewProps(
    
    const RCTProgressViewProps &sourceProps,
    const RawProps &rawProps): ViewProps( sourceProps, rawProps),

    progressViewStyle(convertRawProp( rawProps, "progressViewStyle", sourceProps.progressViewStyle, {RCTProgressViewProgressViewStyle::Default})),
    progress(convertRawProp( rawProps, "progress", sourceProps.progress, {0.0})),
    progressTintColor(convertRawProp( rawProps, "progressTintColor", sourceProps.progressTintColor, {})),
    trackTintColor(convertRawProp( rawProps, "trackTintColor", sourceProps.trackTintColor, {})),
    progressImage(convertRawProp( rawProps, "progressImage", sourceProps.progressImage, {})),
    trackImage(convertRawProp( rawProps, "trackImage", sourceProps.trackImage, {}))
      {}
PullToRefreshViewProps::PullToRefreshViewProps(
    
    const PullToRefreshViewProps &sourceProps,
    const RawProps &rawProps): ViewProps( sourceProps, rawProps),

    tintColor(convertRawProp( rawProps, "tintColor", sourceProps.tintColor, {})),
    titleColor(convertRawProp( rawProps, "titleColor", sourceProps.titleColor, {})),
    title(convertRawProp( rawProps, "title", sourceProps.title, {})),
    progressViewOffset(convertRawProp( rawProps, "progressViewOffset", sourceProps.progressViewOffset, {0.0})),
    refreshing(convertRawProp( rawProps, "refreshing", sourceProps.refreshing, {false}))
      {}
SafeAreaViewProps::SafeAreaViewProps(
    
    const SafeAreaViewProps &sourceProps,
    const RawProps &rawProps): ViewProps( sourceProps, rawProps)

    
      {}
SliderProps::SliderProps(
    
    const SliderProps &sourceProps,
    const RawProps &rawProps): ViewProps( sourceProps, rawProps),

    disabled(convertRawProp( rawProps, "disabled", sourceProps.disabled, {false})),
    enabled(convertRawProp( rawProps, "enabled", sourceProps.enabled, {true})),
    maximumTrackImage(convertRawProp( rawProps, "maximumTrackImage", sourceProps.maximumTrackImage, {})),
    maximumTrackTintColor(convertRawProp( rawProps, "maximumTrackTintColor", sourceProps.maximumTrackTintColor, {})),
    maximumValue(convertRawProp( rawProps, "maximumValue", sourceProps.maximumValue, {1.0})),
    minimumTrackImage(convertRawProp( rawProps, "minimumTrackImage", sourceProps.minimumTrackImage, {})),
    minimumTrackTintColor(convertRawProp( rawProps, "minimumTrackTintColor", sourceProps.minimumTrackTintColor, {})),
    minimumValue(convertRawProp( rawProps, "minimumValue", sourceProps.minimumValue, {0.0})),
    step(convertRawProp( rawProps, "step", sourceProps.step, {0.0})),
    testID(convertRawProp( rawProps, "testID", sourceProps.testID, {""})),
    thumbImage(convertRawProp( rawProps, "thumbImage", sourceProps.thumbImage, {})),
    thumbTintColor(convertRawProp( rawProps, "thumbTintColor", sourceProps.thumbTintColor, {})),
    trackImage(convertRawProp( rawProps, "trackImage", sourceProps.trackImage, {})),
    value(convertRawProp( rawProps, "value", sourceProps.value, {0.0}))
      {}
SwitchProps::SwitchProps(
    
    const SwitchProps &sourceProps,
    const RawProps &rawProps): ViewProps( sourceProps, rawProps),

    disabled(convertRawProp( rawProps, "disabled", sourceProps.disabled, {false})),
    value(convertRawProp( rawProps, "value", sourceProps.value, {false})),
    tintColor(convertRawProp( rawProps, "tintColor", sourceProps.tintColor, {})),
    onTintColor(convertRawProp( rawProps, "onTintColor", sourceProps.onTintColor, {})),
    thumbTintColor(convertRawProp( rawProps, "thumbTintColor", sourceProps.thumbTintColor, {})),
    thumbColor(convertRawProp( rawProps, "thumbColor", sourceProps.thumbColor, {})),
    trackColorForFalse(convertRawProp( rawProps, "trackColorForFalse", sourceProps.trackColorForFalse, {})),
    trackColorForTrue(convertRawProp( rawProps, "trackColorForTrue", sourceProps.trackColorForTrue, {}))
      {}
InputAccessoryProps::InputAccessoryProps(
    
    const InputAccessoryProps &sourceProps,
    const RawProps &rawProps): ViewProps( sourceProps, rawProps),

    backgroundColor(convertRawProp( rawProps, "backgroundColor", sourceProps.backgroundColor, {}))
      {}
UnimplementedNativeViewProps::UnimplementedNativeViewProps(
    
    const UnimplementedNativeViewProps &sourceProps,
    const RawProps &rawProps): ViewProps( sourceProps, rawProps),

    name(convertRawProp( rawProps, "name", sourceProps.name, {""}))
      {}
ModalHostViewProps::ModalHostViewProps(
    
    const ModalHostViewProps &sourceProps,
    const RawProps &rawProps): ViewProps( sourceProps, rawProps),

    animationType(convertRawProp( rawProps, "animationType", sourceProps.animationType, {ModalHostViewAnimationType::None})),
    presentationStyle(convertRawProp( rawProps, "presentationStyle", sourceProps.presentationStyle, {ModalHostViewPresentationStyle::FullScreen})),
    transparent(convertRawProp( rawProps, "transparent", sourceProps.transparent, {false})),
    statusBarTranslucent(convertRawProp( rawProps, "statusBarTranslucent", sourceProps.statusBarTranslucent, {false})),
    hardwareAccelerated(convertRawProp( rawProps, "hardwareAccelerated", sourceProps.hardwareAccelerated, {false})),
    visible(convertRawProp( rawProps, "visible", sourceProps.visible, {false})),
    animated(convertRawProp( rawProps, "animated", sourceProps.animated, {false})),
    supportedOrientations(convertRawProp( rawProps, "supportedOrientations", sourceProps.supportedOrientations, {static_cast<ModalHostViewSupportedOrientationsMask>(ModalHostViewSupportedOrientations::Portrait)})),
    identifier(convertRawProp( rawProps, "identifier", sourceProps.identifier, {0}))
      {}

} // namespace react
} // namespace facebook
