import React, { Component } from 'react';
import { Image } from 'react-native';



export default class ProgressiveImage extends Component {

  state = { showDefault: true, error: false };

  render() {

    const image = { uri: this.props.uri.uri };
    // const defaultImage = require('./images/home_content_default.png');
    const defaultImage = this.props.defaultSource;

    return (
      <>
        {
          (!this.state.error) &&
          <Image
            style={this.props.style}
            source={image}
            onLoadEnd={() => this.setState({ showDefault: false })}
            onError={() => this.setState({ error: true })}
            resizeMode={this.props.resizeMode} />
        }

        {
          (this.state.showDefault || this.state.error) &&
          <Image
            style={[this.props.style, { position: "absolute" }]}
            source={defaultImage}
            resizeMode={this.props.resizeMode}
          />
        }
      </>
    );
  }
};
