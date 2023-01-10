/**
 * Sample React Native App
 * https://github.com/facebook/react-native
 *
 * @format
 * @flow strict-local
 */
import React, {
    Component
} from 'react';
import {
    Text,
    TextInput,
    View,
    AppRegistry,
    StyleSheet,
    TouchableOpacity,
    TouchableHighlight
} from 'react-native';
import { NativeModules } from "react-native";

let keys = [];
var gKey = 0;

function getObjKey() {
  gKey++;
  return gKey;
}

getconfig = async () => {
  NativeModules.ConfigProvider.getConfig(
      async (
        _error: any,
        config: any,
        localization: any,
        tvRatings: any,
        movieRatings: any,
        customStrings: any,
        versions: any,
        firstLaunchGuide: any,
        uiTheme: any,
        userAgreementStrings: any,
        railsLayout: any,
        isHevcSupported: any,
        adsConfig: any,
      ) => {
        console.log("config ", config.actionBarOptions);
        console.log("movieRatings ", movieRatings);
        console.log("versions ", versions);
        console.log("uiTheme", uiTheme);
        console.log("uiTheme", adsConfig);
  });
}
class SimpleViewApp extends Component {

  constructor(props) {
    super(props)
    this.state = {
        keys: []
    }
    getconfig();
  }
  logEvent1 = async () => {
    console.log("----------------calling logEvent1");
  }

  onPress = () => {
    console.log("onTouch---------------------")
    this.logEvent1();
  }

  componentDidMount() {
  }
  render(){
      return(
         <View style={styles.container}>
          <TouchableHighlight onPress={this.onPress}>
            <View style={styles.button}>
              <Text>Touch Here</Text>
            </View>
          </TouchableHighlight>
           <Text style={styles.text1}>TESTING OF @react-native-async-storage!!</Text>
           {this.state.keys.map((i)=>{let key= getObjKey();return (<Text key={key} style={styles.text2}>Obj-{key}: {i}</Text>)})}
         </View>
      );
  }
 };
 
 const styles = StyleSheet.create({
  container: {
    width: 500,
    height: 500,
    backgroundColor: "yellow",
    display: "flex",
    alignItems: 'center',
    justifyContent: 'center'
  },
  text1: {
    fontSize: 25,
    color: "red"
  },
  text2: {
    fontSize: 20,
    color: "blue"
  },
  button: {
    alignItems: "center",
    backgroundColor: "#DDDDDD",
    padding: 10
  },


 });
  
AppRegistry.registerComponent('SimpleViewApp', () => SimpleViewApp);
 

