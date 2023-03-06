/**
 * Sample React Native App for react-native-svg library
 * https://github.com/magicismight/react-native-svg/tree/master/Example
 */
'use strict';

import React, {Component} from 'react';
import { AppRegistry} from 'react-native';
import {
  Dimensions,
  StyleSheet,
  View,
  Text,
  ScrollView,
} from 'react-native';

import textProps from './textProps'

const windowSize = Dimensions.get('window');

const getElements = () =>{

  var arr=[];
  var arr1=[];
  console.log(" textProps.features.length " + textProps.features.length);
  for(var j=0;j<textProps.features.length;j++) {
    arr.push(<View style={styles.container}>
                <View style={styles.innerContainer}>
                   <Text style={{fontSize:'18',fontWeight:'bold', textAlign:'center' ,color:'#fff'}}>{textProps.featureName[j]}</Text>
                   <View style={styles.viewWrapper}>
                     {textProps.features[j]}
                   </View>
                </View>
              </View>);
    }
    return arr;
}

class SvgTextTSpan extends Component {
  render() {
  return (
      <ScrollView>
        <View style={styles.top}>
          <Text style={{fontSize:'32',fontWeight:'bold',color:'black',textAlign:'center'}}>SVG Text & TSpan Elements Demo in RNS</Text>
            {getElements()}
        </View>
      </ScrollView>
    );
  }
}

const styles = StyleSheet.create({
  top: {
    marginTop: 10,
    flexDirection: 'column',
    alignContent:'center',
    justifyContent:'center',
    left:150,
    width:windowSize.width*.80,
    heigth:windowSize.height*.80,
    paddingBottom:30,
    paddingBottom:30,
  },
  container: {
   flexDirection: 'row',
    paddingTop:10,
    paddingBottom:10,
    alignContent:'space-around',
    justifyContent:'space-around',
    backgroundColor: "black",
    borderColor:'green',
    borderWidth:3,
  },
  innerContainer: {
    marginTop: 15,
    marginRight: 20,
    left:10,
    paddingBottom:10,
  },
  viewWrapper: {
    paddingTop: 10,
    paddingLeft: 5,
    paddingRight: 5,
    alignContent:'center',
    justifyContent:'center',
  }
});
AppRegistry.registerComponent('SimpleViewApp', () => SvgTextTSpan);
