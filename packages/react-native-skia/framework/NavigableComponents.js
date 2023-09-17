import { AppRegistry} from 'react-native';
import React, { useState } from "react";
import { View, Text, StyleSheet, TouchableOpacity, TouchableHighlight, TouchableWithoutFeedback, Button, Pressable } from "react-native";

const App = () => {
  const [focusedComponent, setFocusedComponent] = useState("");
  const [pressedComponent, setPressedComponent] = useState("");

  const handleFocus = (componentName) => {
    setPressedComponent("");
    setFocusedComponent(`${componentName} is focused`);
  };

  const handleBlur = () => {
    setPressedComponent("");
    setFocusedComponent("");
  };
  
  const handlePress = (componentName) => {
    setPressedComponent(`${componentName} is pressed`);
  };

  return (
    <View style={styles.container}>
      <TouchableOpacity
        style={styles.button}
        onPress={() => handlePress("TouchableOpacity")}
        onFocus={() => handleFocus("TouchableOpacity")}
        onBlur={() => handleBlur()}
      >
        <Text style={styles.buttonText}>TouchableOpacity</Text>
      </TouchableOpacity>

      <TouchableHighlight
        style={styles.button}
        underlayColor="lightgreen"
        onPress={() => handlePress("TouchableHighlight")}
        onFocus={() => handleFocus("TouchableHighlight")}
        onBlur={() => handleBlur()}
      >
        <Text style={styles.buttonText}>TouchableHighlight</Text>
      </TouchableHighlight>

      <TouchableWithoutFeedback
        onPress={() => handlePress("TouchableWithoutFeedback")}
        onFocus={() => handleFocus("TouchableWithoutFeedback")}
        onBlur={() => handleBlur()}
      >
        <View style={styles.button}>
          <Text style={styles.buttonText}>TouchableWithoutFeedback</Text>
        </View>
      </TouchableWithoutFeedback>

      <Button
        title="Button"
        onPress={() => handlePress("Button")}
      />
      
      <Button
        title="Disabled Button"
        disabled
        onPress={() => handlePress("Disabled Button")}
      />

      <Pressable
        style={styles.button}
        onPress={() => handlePress("Pressable")}
        onFocus={() => handleFocus("Pressable")}
        onBlur={() => handleBlur()}
      >
        <Text style={styles.buttonText}>Pressable</Text>
      </Pressable>

      <Text style={styles.statusText}>
        {pressedComponent || focusedComponent}
      </Text>
    </View>
  );
};

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: "center",
    alignItems: "center",
  },
  button: {
    marginVertical: 10,
    padding: 10,
    backgroundColor: "lightblue",
    borderRadius: 5,
  },
  buttonText: {
    fontSize: 16,
    fontWeight: "bold",
  },
  statusText: {
    marginTop: 20,
    fontSize: 18,
    fontWeight: "bold",
    color: "green",
  },
});

export default App;

AppRegistry.registerComponent('SimpleViewApp', () => App);
