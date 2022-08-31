/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @flow
 * @format
 */

'use strict';

import {NativeEventEmitter} from 'react-native';
import NativeRadioPlayer from './NativeRadioPlayerModule';

class RadioPlayer extends NativeEventEmitter {
  constructor() {
    super(NativeRadioPlayer);
  }

  tune() {
    NativeRadioPlayer.tune();
  }

  play() {
    NativeRadioPlayer.play();
  }

  stop() {
    NativeRadioPlayer.stop();
  }

  setVolume(level: number) {
    NativeRadioPlayer.setVolume(level);
  }

  mute(status: boolean) {
    NativeRadioPlayer.mute(status);
  }
}

module.exports = (new RadioPlayer(): RadioPlayer);
