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


class SvgViewImage extends Component {
  static title =
    'Image with SVG Elements';
  render() {
    return (
      <Svg
        height="100"
        width="100"
        style={{borderWidth:2,borderColor:'green'}}
        preserveAspectRatio="none">
        <Rect x="0" y="0" width="100" height="100" fill="red" />
        <Circle cx="50" cy="50" r="30" fill="yellow" />
        <Circle cx="40" cy="40" r="4" fill="black" />
        <Circle cx="60" cy="40" r="4" fill="black" />
        <Path d="M 40 60 A 10 10 0 0 0 60 60" stroke="black" strokeWidth='2' />
      </Svg>
    );
  }
}

class SvgViewbox extends Component {
  static title =
    'SVG with `viewBox="40 20 100 40"`';
  render() {
    return (
      <Svg
        height="100"
        width="100"
        viewBox="40 20 100 40"
        style={{borderWidth:2,borderColor:'green'}}
        preserveAspectRatio="none">
        <Rect x="0" y="0" width="100" height="100" fill="red" />
        <Circle cx="50" cy="50" r="30" fill="yellow" />
        <Circle cx="40" cy="40" r="4" fill="black" />
        <Circle cx="60" cy="40" r="4" fill="black" />
        <Path d="M 40 60 A 10 10 0 0 0 60 60" stroke="black" />
      </Svg>
    );
  }
}

class SvgViewBox1 extends Component {
  static title = 'More ViewBox Example  `viewBox="-16 -16 544 544" `';
  render() {
    return (
      <Svg
        width="130"
        height="130"
        fill="blue"
        stroke="red"
        color="green"
        viewBox="-16 -16 544 544"
      >
      <Path
        d="M318.37,85.45L422.53,190.11,158.89,455,54.79,350.38ZM501.56,60.2L455.11,13.53a45.93,45.93,0,0,0-65.11,0L345.51,58.24,449.66,162.9l51.9-52.15A35.8,35.8,0,0,0,501.56,60.2ZM0.29,497.49a11.88,11.88,0,0,0,14.34,14.17l116.06-28.28L26.59,378.72Z"
        strokeWidth="32"
      />
      <Path d="M0,0L512,512" stroke="currentColor" strokeWidth="32" />
     </Svg>
    );
  }
}


const samples = [
  SvgViewImage,
  SvgViewbox,
  SvgViewBox1
];

export { samples};
