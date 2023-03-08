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

import examples from './examples'
const windowSize = Dimensions.get('window');

const getExamples = () =>{

  var appendedList=[];
  for(var i=0;i<examples.length;i++) {
    appendedList = appendedList.concat(examples[i].samples);
  }
  let data=appendedList.map((Samples)=>{
    return (<View style={styles.container}>
              <View style={styles.IconWithDescriptionContainer}>
                <Text style={{fontSize:'18',fontWeight:'bold', textAlign:'center' ,color:'#fff'}}>{Samples.title}</Text>
                  <View style={styles.IconContainer}>
                    <Samples />
                  </View>
                </View>
             </View>)
  });
  return data;
}

class SvgExamples extends Component {
  render() {
  return (
    <ScrollView>
      <View style={styles.SvgExamplesContainer}>
        <Text style={{fontSize:'32',fontWeight:'bold',color:'black',textAlign:'center'}}>SVG Elements Demo with RNS</Text>
            {getExamples()}
      </View>
    </ScrollView>
    );
  }
}

const styles = StyleSheet.create({
  SvgExamplesContainer: {
    marginTop: 10,
    flexDirection: 'column',
    alignContent:'center',
    justifyContent:'center',
    left:100,
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
  IconWithDescriptionContainer: {
    marginTop: 15,
    marginRight: 20,
    left:10,
    paddingBottom:10,
  },
  IconContainer: {
    paddingTop: 10,
    paddingLeft: 5,
    paddingRight: 5,
    alignContent:'center',
    justifyContent:'center',
  }
});
AppRegistry.registerComponent('SimpleViewApp', () => SvgExamples);
