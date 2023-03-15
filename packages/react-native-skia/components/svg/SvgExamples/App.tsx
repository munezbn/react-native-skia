
'use strict';

import React, {Component} from 'react';
import {
  Dimensions,
  StyleSheet,
  Text,
  View,
  TouchableOpacity,
  ScrollView
} from 'react-native';
import { AppRegistry} from 'react-native';
import * as examples from './examples';

const hairline = StyleSheet.hairlineWidth;
const windowSize = Dimensions.get('window');

const styles = StyleSheet.create({
  container: {
    flex: 1,
    paddingTop: 20,
    overflow: 'hidden',
    left:100,
    width:windowSize.width*.80,
    heigth:windowSize.height*.90,
  },
  contentContainer: {
    flexDirection: 'column',
  },
  verticalContainer: {
    flexDirection: 'row',
  },
  elements : {
    alignSelf: 'stretch',
    flexWrap: 'wrap',
    flexDirection: 'row',
    marginHorizontal: 10,
    alignContent:'space-around',
    justifyContent:'space-around',
  },
  welcome: {
    padding: 10,
    color: '#f60',
    fontSize: 18,
    fontWeight: 'bold',
  },
  link: {
    height: 40,
    width: Dimensions.get('window').width / 4 - 10,
    backgroundColor: 'mediumpurple'
  },
  title: {
    marginLeft: 10,
  },
  cell: {
    height: 40,
    flexDirection: 'row',
    borderTopWidth: hairline,
    borderTopColor: '#ccc',
    marginTop: -hairline,
    backgroundColor: 'transparent',
  },
  example: {
    paddingVertical: 25,
    alignSelf: 'stretch',
    alignItems: 'center',
    borderBottomWidth: hairline,
    borderBottomColor: '#ccc',
  },
  sampleTitle: {
    marginHorizontal: 15,
    fontSize: 16,
    color: '#666',
  },
});

const names: (keyof typeof examples)[] = [
  'Svg',
  'Stroking',
  'Rect',
  'Circle',
  'Ellipse',
  'Line',
  'Polygon',
  'Polyline',
  'Path',
  'Text',
  'G',
  'Gradients',
];

const initialState = {
  content: null,
};

export default class SvgExample extends Component {
  state: {
    content: React.ReactNode;
  } = initialState;

  show = (name: keyof typeof examples) => {
    let example = examples[name];
    if (example) {
      let samples = example.samples;
      console.log("Component : " + example.samples.title)
      this.setState({
        content: (
          <View style={styles.elements}>
            {samples.map((Sample, i) => (
              <View style={styles.example} key={`sample-${i}`}>
               <Text style={styles.sampleTitle}>{Sample.title}</Text>
               <Sample />
              </View>
            ))}
          </View>
        ),
      });
    }
  };


  getExamples = () => {
    return names.map(name => {
      let example = examples[name];
      return (
        <TouchableOpacity
          style={styles.link}
          underlayColor="#ccc"
          key={`example-${name}`}
          onPress={() => {
          this.show(name)}}>
          <View style={styles.cell}>
            <Text style={styles.title}>{name}</Text>
          </View>
        </TouchableOpacity>
      );
    });
  };

  render() {
    return (
      <View style={styles.container}>
        <Text style={styles.welcome}>SVG Demo for React Native Skia</Text>
        <View style={styles.verticalContainer}>
           <View style={styles.contentContainer}>{this.getExamples()}</View>
            <ScrollView>
              {this.state.content}
            </ScrollView>
        </View>
      </View>
    );
  }
}


AppRegistry.registerComponent('SimpleViewApp', () => SvgExample);