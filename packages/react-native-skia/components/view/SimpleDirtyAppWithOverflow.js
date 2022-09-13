import * as React from 'react';
import {useState} from 'react';
import { View, AppRegistry, Image, Text } from 'react-native';

const SimpleViewApp = React.Node = () => {

  let [bgColor,setBgColor] = useState('yellow');

  setTimeout(()=>{
      if(bgColor == 'yellow') setBgColor('orange');
      else setBgColor('yellow');
  },3000);

  return (
    <View
      style={{ flex: 1,
               flexDirection: 'column',
               justifyContent: 'center',
               alignItems: 'center',
               backgroundColor: '#444' }}>
      <View style={{backgroundColor:bgColor,borderWidth:2,borderColor:'black',width:300,height:300,position:'absolute',top:50,left:100}}>
      </View>
      <View style={{backgroundColor:bgColor,borderWidth:2,borderColor:'black',width:300,height:300,position:'absolute',top:50,left:500}}>
      </View>
      <View style={{backgroundColor:bgColor,borderWidth:2,borderColor:'black',width:300,height:300,position:'absolute',top:400,left:100}}>
      </View>
      <View style={{backgroundColor:bgColor,borderWidth:2,borderColor:'black',width:300,height:300,position:'absolute',top:400,left:500}}>
      </View>
      <View style={{backgroundColor:bgColor,borderWidth:5,borderColor:'red',width:300,height:400,position:'absolute',top:150,left:300,overflow:"visible"}}>
         <View style={{backgroundColor:"green",width:100,height:100,margin:5}}>
         </View>
         <View style={{backgroundColor:"green",width:100,height:100,margin:5}}>
         </View>
         <View style={{backgroundColor:"green",width:100,height:100,margin:5}}>
         </View>
         <View style={{backgroundColor:"green",width:100,height:100,margin:5}}>
         </View>
         <View style={{backgroundColor:"green",width:100,height:100,margin:5}}>
         </View>
         <View style={{backgroundColor:"green",width:100,height:100,margin:5}}>
         </View>
     </View>
     <View style={{backgroundColor:bgColor,borderWidth:5,borderColor:'red',width:300,height:50,position:'absolute',top:600,left:300}}>
     </View>
     <View style={{backgroundColor:bgColor,borderWidth:2,borderColor:'black',width:300,height:300,position:'absolute',top:50,left:900}}>
     </View>
     <View style={{backgroundColor:bgColor,borderWidth:2,borderColor:'black',width:300,height:300,position:'absolute',top:50,left:1300}}>
     </View>
     <View style={{backgroundColor:bgColor,borderWidth:2,borderColor:'black',width:300,height:300,position:'absolute',top:400,left:900}}>
     </View>
     <View style={{backgroundColor:bgColor,borderWidth:2,borderColor:'black',width:300,height:300,position:'absolute',top:400,left:1300}}>
     </View>
     <View style={{backgroundColor:bgColor,borderWidth:5,borderColor:'red',width:300,height:400,position:'absolute',top:150,left:1100,overflow:"hidden"}}>
        <View style={{backgroundColor:"green",width:100,height:100,margin:5}}>
        </View>
        <View style={{backgroundColor:"green",width:100,height:100,margin:5}}>
        </View>
        <View style={{backgroundColor:"green",width:100,height:100,margin:5}}>
        </View>
        <View style={{backgroundColor:"green",width:100,height:100,margin:5}}>
        </View>
        <View style={{backgroundColor:"green",width:100,height:100,margin:5}}>
        </View>
        <View style={{backgroundColor:"green",width:100,height:100,margin:5}}>
        </View>
    </View>
    <View style={{backgroundColor:bgColor,borderWidth:5,borderColor:'red',width:300,height:50,position:'absolute',top:600,left:1100}}>
    </View>
    </View>
  );
};

AppRegistry.registerComponent('SimpleViewApp', () => SimpleViewApp);
