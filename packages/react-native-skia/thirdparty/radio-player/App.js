import * as React from 'react';
import { AppRegistry, StyleSheet, Text, TextInput, TouchableHighlight, View } from 'react-native';
const RadioPlayer = require('./RadioPlayerModule');

const RadioPlayerApp = () => {
  const [muteStatus, setMuteStatus] = React.useState(false);
  const [playerState, setPlayerState] = React.useState('stopped');
  const [metadata, setMetadata] = React.useState();

  React.useEffect(() => {
    RadioPlayer.addListener('StateDidChange', (eventObject) => {
      setPlayerState(eventObject.state);
    });
    return () => {
      RadioPlayer.removeListener('StateDidChange', (eventObject) => {
        setPlayerState(eventObject.state);
      });
    };
  }, []);

  React.useEffect(() => {
    RadioPlayer.addListener('MetadataDidChange', setMetadata);
    return () => {
      RadioPlayer.addListener('MetadataDidChange', setMetadata);
    };
  }, []);

  let play = () => {
     console.log("Call RadioPlayer play");
     RadioPlayer.play();
  };

  let stop = () => {
     console.log("Call RadioPlayer stop");
     RadioPlayer.stop();
  };

  let tune = () => {
     console.log("Call RadioPlayer tune");
     RadioPlayer.tune();
  };

  let setVolume = (e) => {
     let level = parseInt(e.nativeEvent.text);
     console.log("Call RadioPlayer setVolume:"+level);
     RadioPlayer.setVolume(level);
  };

  let toggleMute = () => {
     setMuteStatus(!muteStatus);
     console.log("Call RadioPlayer Mute:"+ muteStatus);
     RadioPlayer.mute(muteStatus);
  };


  return (
    <View style={styles.container}>
      <View style={styles.container}>
        <Text style={styles.text}>Title</Text>
        <Text style={[styles.text,{color:'green'}]}>{metadata?.trackName ?? 'Unknown'}</Text>
        <Text style={styles.text}>Artist</Text>
        <Text style={[styles.text,{color:'green'}]}>{metadata?.artistName ?? 'Unknown'}</Text>
        <Text style={styles.text}>State</Text>
        <Text style={[styles.text,{color:'green'}]}>{playerState}</Text>
      </View>
      <View style={[styles.container, styles.actions]}>
        <TouchableHighlight style={styles.buttons} underlayColor='lightcyan' onPress={tune}>
          <Text style={styles.text}>{"Tune"}</Text>
        </TouchableHighlight>
        <TouchableHighlight style={styles.buttons} underlayColor='lightcyan' onPress={play}>
          <Text style={styles.text}>{"Play"}</Text>
        </TouchableHighlight>
        <TouchableHighlight style={styles.buttons} underlayColor='lightcyan' onPress={stop}>
          <Text style={styles.text}>{"Stop"}</Text>
        </TouchableHighlight>
        <TouchableHighlight style={styles.buttons} underlayColor='lightcyan' onPress={toggleMute}>
          <Text style={styles.text}>{"Mute: "+ muteStatus}</Text>
        </TouchableHighlight>
        <Text style={styles.text}>{"Set Volume"}</Text>
        <TextInput style={styles.buttons} onEndEditing={setVolume} showSoftInputOnFocus={false}/>
      </View>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    alignItems: 'center',
    justifyContent: 'center',
    margin:10,
    borderColor:'black',
    borderWidth:3,
    backgroundColor:'lightgrey',
    width:'80%',
    height:'30%',
  },
  actions: {
    flex: 1,
    flexDirection: 'row',
  },
  buttons:{
    borderColor:'black',
    borderWidth:3,
    borderRadius:10,
    backgroundColor:'darkcyan',
    width:150,
    height:50,
    margin:5,
    padding:10,
  },
  text: {
    color:'black',
    margin:5,
  }

});

export default RadioPlayerApp;
AppRegistry.registerComponent('SimpleViewApp', () => RadioPlayerApp);
