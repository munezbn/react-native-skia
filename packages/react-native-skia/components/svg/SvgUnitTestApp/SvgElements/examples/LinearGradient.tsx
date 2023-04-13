import React, {Component} from 'react';
import {View} from 'react-native';
import {
  Svg,
  Circle,
  Ellipse,
  Text,
  Rect,
  Defs,
  LinearGradient,
  RadialGradient,
  Stop,
} from 'react-native-svg';

class LinearGradientHorizontalBug extends Component {
  static title =
    'Horizontal linear gradient from transparent yellow to red';
  render() {
    return (
      <Svg height="150" width="300">
        <Ellipse cx="150" cy="75" rx="85" ry="55" fill="url(#grad-1-bug)" />
        <Defs>
          <LinearGradient
            id="grad-1-bug"
            x1="65"
            y1="0"
            x2="235"
            y2="0"
            gradientUnits="userSpaceOnUse">
            <Stop offset="0" stopColor="rgb(255,255,0)" stopOpacity="0" />
            <Stop offset="1" stopColor="red" stopOpacity="1"/>
          </LinearGradient>
        </Defs>
      </Svg>
    );
  }
}

class LinearGradientRotated extends Component {
  static title =
    'Rotated linear gradient from yellow to red';
  render() {
    return (
      <Svg height="150" width="300">
        <Defs>
          <LinearGradient id="grad-2" x1={0} y1={0} x2="0%" y2="100%">
            <Stop offset="0%" stopColor="rgb(255,255,0)" stopOpacity="0" />
            <Stop offset="100%" stopColor="red" stopOpacity="1" />
          </LinearGradient>
        </Defs>
        <Ellipse cx="150" cy="75" rx="85" ry="55" fill="url(#grad-2)" />
      </Svg>
    );
  }
}

class GradientUnits extends Component {
  static title = 'gradientUnits "OnObjectBoundingBox" vs "userSpaceOnUse" ';
  render() {
    return (
      <View
        style={{
          width: 220,
          height: 150,
          flexDirection: 'row',
          justifyContent: 'space-around',
        }}>
        <Svg height="150" width="90">
          <Defs>
            <LinearGradient id="defaultUnits" x1="0%" y1="0%" x2="0%" y2="100%">
              <Stop offset="0%" stopColor="#000" stopOpacity="1" />
              <Stop offset="100%" stopColor="#ff0" stopOpacity="1" />
            </LinearGradient>
          </Defs>
          <Rect
            fill="url(#defaultUnits)"
            x="10"
            y="10"
            width="70"
            height="70"
            rx="10"
            ry="10"
          />
        </Svg>
        <Svg height="150" width="90">
          <Defs>
            <LinearGradient
              id="userSpaceOnUse"
              x1="0%"
              y1="0%"
              x2="0%"
              y2="100%"
              gradientUnits="userSpaceOnUse">
              <Stop offset="0%" stopColor="#000" stopOpacity="1" />
              <Stop offset="100%" stopColor="#ff0" stopOpacity="1" />
            </LinearGradient>
          </Defs>
          <Rect
            fill="url(#userSpaceOnUse)"
            x="10"
            y="10"
            width="70"
            height="70"
            rx="10"
            ry="10"
          />
        </Svg>
      </View>
    );
  }
}

class LinearGradientPercent extends Component {
  static title = 'Define a linear gradient in percent unit';
  render() {
    return (
      <Svg height="150" width="300">
        <Defs>
          <LinearGradient id="grad-3" x1="0%" y1="0%" x2="100%" y2="0%">
            <Stop offset="0%" stopColor="rgb(255,255,0)" stopOpacity="0" />
            <Stop offset="100%" stopColor="red" stopOpacity="1" />
          </LinearGradient>
        </Defs>
        <Text x="25" y="70" fill="#333">
          x1=0%
        </Text>
        <Text x="235" y="70" fill="#333">
          x2=100%
        </Text>
        <Ellipse cx="150" cy="75" rx="85" ry="55" fill="url(#grad-3)" />
      </Svg>
    );
  }
}

const icon = (
  <Svg height="30" width="30" viewBox="0 0 20 20">
    <Defs>
      <LinearGradient id="icon-grad" x1="0" y1="0" x2="0" y2="100%">
        <Stop offset="0" stopColor="blue" stopOpacity="1" />
        <Stop offset="100%" stopColor="red" stopOpacity="1" />
      </LinearGradient>
    </Defs>
      <LinearGradient id="icon-grad" x1="0" y1="0" x2="0" y2="100%">
        <Stop offset="0" stopColor="blue" stopOpacity="1" />
        <Stop offset="100%" stopColor="red" stopOpacity="1" />
      </LinearGradient>
    <Circle cx="10" cy="10" r="10" fill="url(#icon-grad)" />
  </Svg>
);

const samples = [
  LinearGradientHorizontalBug,
  LinearGradientRotated,
  GradientUnits,
  LinearGradientPercent
];

export {icon, samples};
