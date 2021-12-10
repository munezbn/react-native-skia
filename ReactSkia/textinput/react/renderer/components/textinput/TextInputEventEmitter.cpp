/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "TextInputEventEmitter.h"

namespace facebook {
namespace react {

static jsi::Value textInputMetricsPayload(
    jsi::Runtime &runtime,
    TextInputMetrics const &textInputMetrics) {
  auto payload = jsi::Object(runtime);

  payload.setProperty(
      runtime,
      "text",
      jsi::String::createFromUtf8(runtime, textInputMetrics.text));

  payload.setProperty(runtime, "eventCount", textInputMetrics.eventCount);
  {
    auto contentSize = jsi::Object(runtime);
    contentSize.setProperty(
        runtime, "width", textInputMetrics.contentSize.width);
    contentSize.setProperty(
        runtime, "height", textInputMetrics.contentSize.height);
    payload.setProperty(runtime, "contentSize", contentSize);
  }
  {
     auto layoutEvent = jsi::Object(runtime);
     layoutEvent.setProperty(
        runtime, "width", textInputMetrics.contentSize.width);
    layoutEvent.setProperty(
        runtime, "height", textInputMetrics.contentSize.height);
    layoutEvent.setProperty(
        runtime, "x", textInputMetrics.contentOffset.x);
    layoutEvent.setProperty(
        runtime, "y", textInputMetrics.contentOffset.y);
    payload.setProperty(runtime, "LayoutEvent", layoutEvent);
  }
  {
    auto selection = jsi::Object(runtime);
    selection.setProperty(
        runtime, "start", textInputMetrics.selectionRange.location);
    selection.setProperty(
        runtime,
        "end",
        textInputMetrics.selectionRange.location +
            textInputMetrics.selectionRange.length);
    payload.setProperty(runtime, "selection", selection);
  }

  return payload;
};

static jsi::Value keyPressMetricsPayload(
    jsi::Runtime &runtime,
    KeyPressMetrics const &keyPressMetrics) {
  auto payload = jsi::Object(runtime);
  payload.setProperty(runtime, "eventCount", keyPressMetrics.eventCount);

  std::string key;
  if (keyPressMetrics.text == "back") {
    key = "Backspace";
  } else {
    if (keyPressMetrics.text == "select") {
      key = "Enter";
    } else if (keyPressMetrics.text == "tab") {
      key = "Tab";
    } else {
      key = keyPressMetrics.text.front();
    }
  }
  payload.setProperty(
      runtime, "key", jsi::String::createFromUtf8(runtime, key));
  return payload;
};

void TextInputEventEmitter::onFocus(
    TextInputMetrics const &textInputMetrics) const {
  dispatchTextInputEvent("focus", textInputMetrics);
}

void TextInputEventEmitter::onBlur(
    TextInputMetrics const &textInputMetrics) const {
  dispatchTextInputEvent("blur", textInputMetrics);
}

void TextInputEventEmitter::onChange(
    TextInputMetrics const &textInputMetrics) const {
  dispatchTextInputEvent("change", textInputMetrics);
}

void TextInputEventEmitter::onChangeText(
    TextInputMetrics const &textInputMetrics) const {
  dispatchTextInputEvent("changeText", textInputMetrics);
}

void TextInputEventEmitter::onContentSizeChange(
    TextInputMetrics const &textInputMetrics) const {
  dispatchTextInputEvent("contentSizeChange", textInputMetrics);
}

void TextInputEventEmitter::onSelectionChange(
    TextInputMetrics const &textInputMetrics) const {
  dispatchTextInputEvent("selectionChange", textInputMetrics);
}

void TextInputEventEmitter::onEndEditing(
    TextInputMetrics const &textInputMetrics) const {
  dispatchTextInputEvent("endEditing", textInputMetrics);
}

void TextInputEventEmitter::onSubmitEditing(
    TextInputMetrics const &textInputMetrics) const {
  dispatchTextInputEvent("submitEditing", textInputMetrics);
}

void TextInputEventEmitter::onKeyPress(
    KeyPressMetrics const &keyPressMetrics) const {
  dispatchEvent(
      "keyPress",
      [keyPressMetrics](jsi::Runtime &runtime) {
        return keyPressMetricsPayload(runtime, keyPressMetrics);
      },
      EventPriority::AsynchronousBatched);
}

void TextInputEventEmitter::dispatchTextInputEvent(
    std::string const &name,
    TextInputMetrics const &textInputMetrics,
    EventPriority priority) const {
  dispatchEvent(
      name,
      [textInputMetrics](jsi::Runtime &runtime) {
        return textInputMetricsPayload(runtime, textInputMetrics);
      },
      priority);
}

} // namespace react
} // namespace facebook
