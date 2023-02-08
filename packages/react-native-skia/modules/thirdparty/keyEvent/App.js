import React, { useState, useEffect } from 'react';
import { View, AppRegistry, Image, Text,TextInput, TVEventHandler, TouchableOpacity, StyleSheet,ScrollView,Pressable} from 'react-native';
import KeyEvent from 'react-native-keyevent';
console.log('TVEventHandler: ', TVEventHandler);


const FocusableComponent = (props) =>  {
   let [state, setState] = useState({imgscale: 1,bw:0});
   const onPress = () => {}

   const onBlur = (e) => {
       console.log("onBlur---------" )
       setState({ imgscale: 1, bw:0});
   }

   const onFocus = (e) => {
       console.log("onFocus---------" )
       setState({ imgscale: 1.2 , bw:2});
   }

   
  return (
    <Pressable isTVSelectable='true' onBlur={onBlur} onFocus={onFocus} style={styles.elementView} >
    <Image style={{transform:[{scale: state.imgscale}],width:300,height:160,marginLeft:30,marginTop:16}} 
     source={{url:"https://reactnative.dev/img/tiny_logo.png"}}>
    </Image>
    </Pressable>
    );
}


// let textkey;
// let tvKey;
class SimpleViewApp extends React.Component {
  constructor(props) {
    super(props);

    this._tvEventHandler = null;
    this.state = {
      bgColor: '#FFFFFF',
      tiBgColor:"black",
      textkey: "",
      tvKey:""
    }

  }
  _reactnativeKeyevent(){
    // if you want to react to keyDown
    KeyEvent.onKeyDownListener((keyEvent) => {
      console.log(`onKeyDown keyCode: ${keyEvent.keyCode}`);
      console.log(`Action: ${keyEvent.action}`);
      console.log(`Key: ${keyEvent.pressedKey}`);
      this.setState({textkey: keyEvent.pressedKey});
    });

    // if you want to react to keyUp
    KeyEvent.onKeyUpListener((keyEvent) => {
      console.log(`onKeyUp keyCode: ${keyEvent.keyCode}`);
      console.log(`Action: ${keyEvent.action}`);
      console.log(`Key: ${keyEvent.pressedKey}`);
      this.setState({textkey: keyEvent.pressedKey});
    });

    // if you want to react to keyMultiple
    KeyEvent.onKeyMultipleListener((keyEvent) => {
      console.log(`onKeyMultiple keyCode: ${keyEvent.keyCode}`);
      console.log(`Action: ${keyEvent.action}`);
      console.log(`Characters: ${keyEvent.characters}`);
    });
  }
  _enableTVEventHandler() {
    let that = this;
    this._tvEventHandler = new TVEventHandler();
    console.log('APP: TVEventHandler ',this._tvEventHandler);
    this._tvEventHandler.enable(this, function(cmp, evt) {
      console.log('APP: TV Key event received: ', evt);
      that.setState({tvKey : evt.eventType});
      if (evt && evt.eventType === 'right') {
        that.setState({bgColor: '#FF0000'})
      } else if(evt && evt.eventType === 'up') {
        that.setState({bgColor: '#00FF00'})
      } else if(evt && evt.eventType === 'left') {
        that.setState({bgColor: '#0000FF'})
      } else if(evt && evt.eventType === 'down') {
        that.setState({bgColor: '#00FFFF'})
      } else if(evt && evt.eventType === 'select') {
        that.setState({bgColor: '#FFFF00'})
      }
    });
  }

  _disableTVEventHandler() {
    if (this._tvEventHandler) {
      this._tvEventHandler.disable();
      delete this._tvEventHandler;
    }
  }

  componentDidMount() {
    this._enableTVEventHandler();
    this._reactnativeKeyevent();
  }

  componentWillUnmount() {
    this._disableTVEventHandler();
        // if you are listening to keyDown
    KeyEvent.removeKeyDownListener();

     // if you are listening to keyUp
    KeyEvent.removeKeyUpListener();

     // if you are listening to keyMultiple
    KeyEvent.removeKeyMultipleListener();
  }

  addItems(){
      var n =4;
       var arr = [];
       for (var i=0; i<n; i++){
          arr.push(<FocusableComponent count={i}></FocusableComponent>);
       }
       return arr;
  }
  
  render() {
    console.log('bgColor: ', this.state.bgColor);
    return (
    <View
      style={{ flex: 1,
               flexDirection: 'column',
               justifyContent: 'center',
               alignItems: 'center',
               backgroundColor: this.state.bgColor }}
      onLayout={() => console.log('onLayout')}>
      <Text style={{fontSize:20}}>
         react native Key event {this.state.textkey}
       </Text>
       <Text style={{fontSize:20}}>
         TVevent handler event {this.state.tvKey}
       </Text>
      
      <TextInput
       style={{borderColor:this.state.tiBgColor,
                height: 50,
                width:200,
                margin: 5,
                borderWidth: 5,
                padding: 5  ,}}
       onFocus={()=>{ this.setState({tiBgColor: '#00FF00'})}}
       onBlur={()=>{this.setState({tiBgColor: '#000000'})}}
       
      />
       <ScrollView style={styles.horizontalScrollView} horizontal={true}>
             {this.addItems()}
        </ScrollView>
    </View>
    );
  }
}

const styles = StyleSheet.create({

  horizontalScrollView: {
       margin : 5,
    },

elementView: {
       width : 360, // Thumbnail image size 
       height : 192,
       shadowColor: 'black',
    }
});

AppRegistry.registerComponent('SimpleViewApp', () => SimpleViewApp);