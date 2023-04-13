import React, {Component} from 'react';
import {StyleSheet, View, Image} from 'react-native';
import {Svg, Circle, G, Path, Line, Rect} from 'react-native-svg';

const styles = StyleSheet.create({
  container: {
    flex: 1,
    height: 100,
    width: 200,
  },
  svg: {
    flex: 1,
    alignSelf: 'stretch',

  },
  boxView:{
    flexDirection:'row',
    paddingHorizontal:50
  }
});


class SvgOpacity extends Component {
  static title = 'SVG with `opacity` prop';
  render() {
    return (
      <View style={styles.boxView}>
      <Svg height="100" width="100">
        <Circle
          cx="50"
          cy="50"
          r="45"
          stroke="blue"
          strokeWidth="2.5"
          fill="green"
        />
        <Rect
          x="15"
          y="15"
          width="70"
          height="70"
          stroke="red"
          strokeWidth="2"
          fill="yellow"
        />
      </Svg>

      <Svg height="100" width="100" opacity="0.2">
        <Circle
          cx="50"
          cy="50"
          r="45"
          stroke="blue"
          strokeWidth="2.5"
          fill="green"
        />
        <Rect
          x="15"
          y="15"
          width="70"
          height="70"
          stroke="red"
          strokeWidth="2"
          fill="yellow"
        />
      </Svg>
      </View>
    );
  }
}

const samples = [
  SvgOpacity,
];

export { samples};
