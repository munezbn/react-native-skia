import React, {Component} from 'react';
import { View, AppRegistry } from 'react-native';
import {Svg, Circle, G, Text, Line, Rect, Use,Ellipse,Path,Stop,Defs,LinearGradient,Polygon,PolyLine} from 'react-native-svg';

export default class GExample extends Component {
  static title = 'G children props inherit';
  state = {
    fill: 'blue',
  };
  componentDidMount = () => {
    setTimeout(() => {
      if (!this._unmounted) {
        this.setState({
          fill: 'purple',
        });
      }
    }, 3000);
  };
  componentWillUnmount = () => {
    this._unmounted = true;
  };
  private _unmounted: any;
  render() {
    return (
      <Svg height="100" width="100">
        <G fill={this.state.fill} stroke="pink" strokeWidth="3" opacity='.5'>
          <Circle cx="25" cy="25" r="11" />
          <Circle cx="25" cy="75" r="11" stroke="red" />
        </G>
        <G fill="yellow" >
          <Circle cx="50" cy="50" r="11" fill="green" />
          <Circle cx="75" cy="25" r="11" stroke="red" />
          <Circle cx="75" cy="75" r="11" />
        </G>
      </Svg>
    );
  }
}




































