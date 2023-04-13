import React, {Component} from 'react';
import {Svg, Circle} from 'react-native-svg';


class CirclePropsUpdate extends Component {
  static title = 'G children props inherit';
  state = {
    fill: 'yellow',
    strokeWidth :'0',
  };
  componentDidMount = () => {
    setTimeout(() => {
      if (!this._unmounted) {
        this.setState({
          fill: 'mediumpurple',
	  strokeWidth :'10',
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
      <Svg height="100" width="140">
        <Circle cx="50%" cy="50%" r="40%" fill="pink" stroke='red' strokeWidth={this.state.strokeWidth}
/>
      </Svg>

    );
  }
}


class CircleExample extends Component {
  static title = 'Circle';
  render() {
    return (
      <Svg height="100" width="140">
        <Circle cx="50%" cy="50%" r="40%" fill="pink" />
      </Svg>
    );
  }
}

class StrokeCircle extends Component {
  static title = 'Stroke Circle';
  render() {
    return (
      <Svg height="100" width="100">
        <Circle
          cx="50"
          cy="50"
          r="45"
          stroke="purple"
          strokeWidth="2.5"
          fill="none"
        />
      </Svg>
    );
  }
}

class StrokeOpacityCircle extends Component {
  static title = 'Circle with strokeOpacity';
  render() {
    return (
      <Svg height="100" width="100">
        <Circle
          cx="50"
          cy="50"
          r="40"
          stroke="purple"
          strokeOpacity="0.5"
          strokeWidth="10"
          fill="pink"
        />
      </Svg>
    );
  }
}

class PieCircle extends Component {
  static title = 'Draw a Pie shape with circle';
  render() {
    return (
      <Svg height="100" width="100">
        <Circle cx="50" cy="50" r="40" fill="#ddd" />
        <Circle
          origin="50, 50"
          cx="50"
          cy="50"
          r="20"
          stroke="#0074d9"
          strokeWidth="40"
          fill="none"
          strokeDasharray="80, 160"
        />
      </Svg>
    );
  }
}

const samples = [CirclePropsUpdate ,CircleExample, StrokeCircle, StrokeOpacityCircle, PieCircle];
export { samples};
