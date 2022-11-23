import * as React from 'react';
import { View, AppRegistry,StyleSheet, Image, Text } from 'react-native';

const SimpleViewApp = React.Node = () => {
  return (
    <View
      style={{ flex: 1,
               flexDirection: 'column',
               justifyContent: 'center',
               alignItems: 'center',
               backgroundColor: '#444' }}>
          <Text style ={ {color:'blue',
                         fontWeight:'bold'}}>" Outer " {'\n'}
                   <Text style ={styles.TextStyle}>"Title"{'\n'}{'\n'}</Text>
                   <Text style ={styles.TextStyle}>"Descrition"{'\n'}</Text>
          </Text>

      <Image
        style={{ width: 512, height: 512 }}
        source={require('react-native/Libraries/NewAppScreen/components/logo.png')}
      />
      <Text style={{ color: '#fff', fontSize: 36,
                     textAlign: 'center', marginTop: 32 }}>
        React Native loves Skia</Text>
    </View>
  );
};

const styles = StyleSheet.create({
    TextStyle: {
        textAlign:'center'
    },


});

AppRegistry.registerComponent('SimpleViewApp', () => SimpleViewApp);
