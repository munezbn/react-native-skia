import React, { useEffect,useState } from 'react';
import KeyEvent from 'react-native-keyevent';
import ReactNative, {
  SafeAreaView,
  StyleSheet,
  ScrollView,
  Platform,
  View,
  Text,
  TouchableOpacity,
  useTVEventHandler,
  TVEventHandler,
  TextInput,
  Image,
  AppRegistry
} from 'react-native';

 

import {
  Header,
  LearnMoreLinks,
  Colors,
  DebugInstructions,
  ReloadInstructions,
} from 'react-native/Libraries/NewAppScreen';



const StatusBar = Platform.isTV ? View : ReactNative.StatusBar;

 

const SimpleViewApp: () => React$Node = () => {
const [lastEventType, setLastEventType] = React.useState('');
const [text, setText] = React.useState('Hello');

useEffect(()=>{

        KeyEvent.onKeyDownListener((keyEvent) => {
          console.log(`react-native-keyevent: $$$$$$$$$$$$$$$$$$$$`);
          console.log(`react-native-keyevent: onKeyDown keyCode: ${keyEvent.keyCode}`);
          console.log(`react-native-keyevent: Action: ${keyEvent.action}`);
          console.log(`react-native-keyevent: Key: ${keyEvent.pressedKey}`);
          console.log(`react-native-keyevent: $$$$$$$$$$$$$$$$$$$`);
        });

        // if you want to react to keyUp
        KeyEvent.onKeyUpListener((keyEvent) => {
          console.log(`react-native-keyevent: ******************`);
          console.log(`react-native-keyevent: onKeyUp keyCode: ${keyEvent.keyCode}`);
          console.log(`react-native-keyevent: Action: ${keyEvent.action}`);
          console.log(`react-native-keyevent: Key: ${keyEvent.pressedKey}`);
          console.log(`react-native-keyevent: ******************`);
        });

        // if you want to react to keyMultiple
        KeyEvent.onKeyMultipleListener((keyEvent) => {
          console.log(`react-native-keyevent: ******************`);
          console.log(`react-native-keyevent: onKeyMultiple keyCode: ${keyEvent.keyCode}`);
          console.log(`react-native-keyevent: Action: ${keyEvent.action}`);
          console.log(`react-native-keyevent: Characters: ${keyEvent.characters}`);
          console.log(`react-native-keyevent: ******************`);
        });
        
        

});
useEffect(()=>{
  let _tvEventHandler = new TVEventHandler();
  _tvEventHandler.enable(this, function(cmp, evt) {
      console.log('APP: TV Key event received: ', evt.eventType);
    })
});
 
const onChange1 = (ne) => {
    enter("onChange1");
    //iterate(ne)
    //iterate(ne.nativeEvent)
    exit("onChange1")
  }
const  onChangeText1 = (string) => {
    enter("onChangeText1" + ": " + string);
    exit("onChangeText1")
  }

const  onKeyPress1 = (ne) => {
    enter("onKeyPress1" + ": " + ne.key)
    //iterate(ne)
    exit("onKeyPress1")
  }
const  onEndEditing1=()=>{
    enter("onEndEditing1")
    exit("onEndEditing1")
  }
  /* working in ios - called 3 times initially with widht/height changes */
const  onContentSizeChange1 = (ne)=>{
    enter("onContentSizeChange1")
    //iterate(ne.nativeEvent.contentSize) // providing the text width on every enter of character
    exit("onContentSizeChange1")
  }
const  onFocus1 = () => {
    enter("onFocus1")
    exit("onFocus1")
  }
const  onBlur1 = () => {
    enter("onBlur1")
    exit("onBlur1")
  }
  /* works both in ios and web. The cursor position where the change can be made. on web multi selection works but not on ios */
const  onSelectionChange1 = (ne) => {
    enter("onSelectionChange1")
    //iterate(ne.nativeEvent.selection)
    exit("onSelectionChange1")
  }
  /* working in ios and web  -- But - IOS provides properties correctly but web only provides text -- need to confirm -- onEndEditing does not provide props but this function provides properties */
const  onSubmitEditing1 = (ne) =>{
    enter("onSubmitEditing1")
    //iterate(ne.nativeEvent)
    exit("onSubmitEditing1")
  }
    /* not working in both web and ios */
const  onPressIn1=()=>{
    enter("onPressIn1")
    exit("onPressIn1")
  }
  /* not working in both web and ios */
const  onPressOut1=()=>{
    enter("onPressOut1")
    exit("onPressOut1")
  }
  function enter(name){console.log("--ENTER--"+name)}
  function exit(name){}//console.log("--EXIT--"+name)} 
 const logo = {
  uri: 'https://reactnative.dev/img/tiny_logo.png',
  width: 64,
  height: 64
};

  return (
    <View>
       
<ScrollView>
    <Text style={{ fontSize: 96 }}>Scroll me plz</Text>
    <Image source={logo} />
    <Image source={logo} />
    <Image source={logo} />
    <Image source={logo} />
    <Image source={logo} />
    <Image source={logo} />
    <Image source={logo} />
    <Image source={logo} />
    <Image source={logo} />
    <Image source={logo} />
    <Image source={logo} />
    <Image source={logo} />
    <Image source={logo} />
    <Image source={logo} />
    <Image source={logo} />
    <Image source={logo} />
    <Image source={logo} />
    <Image source={logo} />
    <Image source={logo} />

  </ScrollView>
  <TextInput style={styles.input}/>    
    </View>
  );
};

 

const styles = StyleSheet.create({
  scrollView: {
    backgroundColor: Colors.lighter,
  },
  engine: {
    position: 'absolute',
    right: 0,
  },
  body: {
    backgroundColor: Colors.white,
  },
  sectionContainer: {
    marginTop: 32,
    paddingHorizontal: 24,
  },
  sectionTitle: {
    fontSize: 24,
    fontWeight: '600',
    color: Colors.black,
  },
  sectionDescription: {
    marginTop: 8,
    fontSize: 18,
    fontWeight: '400',
    color: Colors.dark,
  },
  highlight: {
    fontWeight: '700',
  },
  footer: {
    color: Colors.dark,
    fontSize: 12,
    fontWeight: '600',
    padding: 4,
    paddingRight: 12,
    textAlign: 'right',
  },
     input: {
    height: 40,
    width: 150,
    margin: 12,
    borderWidth: 1,
    padding: 10,
  },
      button: {
    alignItems: "center",
    backgroundColor: "black",
    padding: 10,
    width: 100
  },

});

 

export default SimpleViewApp;

AppRegistry.registerComponent('SimpleViewApp', () => SimpleViewApp);


