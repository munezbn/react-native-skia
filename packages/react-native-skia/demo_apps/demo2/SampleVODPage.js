import React, { useState, useRef } from "react";
import { TouchableHighlight, TouchableOpacity, Pressable, Text, View, ImageBackground, Image, ScrollView } from "react-native";
import { Dimensions, StyleSheet } from "react-native";

import ProgressiveImage from './ProgressiveImage';

const windowSize = Dimensions.get('window');
let titleTextFontSize = windowSize.height / 25;
let titleTextContentSize = windowSize.height / 45;
let titleTextGenreSize = windowSize.height / 35;
let content = [];
const serverURL = "http://localhost:9000";

const DEFAULT_IMAGE_300_160 = require('./images/home_content_default.png');
const DEFAULT_IMAGE_700_300 = require('./images/home_content_default_716_403.png');

const thumbnailImagePath = [
   { uri: serverURL + '/images/thumbnail_300x160/1.jpg' },
   { uri: serverURL + '/images/thumbnail_300x160/2.jpg' },
   { uri: serverURL + '/images/thumbnail_300x160/3er.jpg' },
   { uri: serverURL + '/images/thumbnail_300x160/4.jpg' },
   { uri: serverURL + '/images/thumbnail_300x160/5.jpg' },
   { uri: serverURL + '/images/thumbnail_300x160/6.jpg' },
   { uri: serverURL + '/images/thumbnail_300x160/7.jpg' },
   { uri: serverURL + '/images/thumbnail_300x160/8.jpg' },
   { uri: serverURL + '/images/thumbnail_300x160/12.jpg' },
   { uri: serverURL + '/images/thumbnail_300x160/11.jpg' },
   { uri: serverURL + '/images/thumbnail_300x160/16.jpg' },
   { uri: serverURL + '/images/thumbnail_300x160/21.jpg' },
   { uri: serverURL + '/images/thumbnail_300x160/10.jpg' },
   { uri: serverURL + '/images/thumbnail_300x160/9.jpg' },
   { uri: serverURL + '/images/thumbnail_300x160/19.jpg' },
   { uri: serverURL + '/images/thumbnail_300x160/24.jpg' },
   { uri: serverURL + '/images/thumbnail_300x160/13.jpg' },
   { uri: serverURL + '/images/thumbnail_300x160/15.jpg' },
   { uri: serverURL + '/images/thumbnail_300x160/20.jpg' },
   { uri: serverURL + '/images/thumbnail_300x160/23.jpg' },
   { uri: serverURL + '/images/thumbnail_300x160/14.jpg' },
   { uri: serverURL + '/images/thumbnail_300x160/22.jpg' },
   { uri: serverURL + '/images/thumbnail_300x160/18.jpg' },
   { uri: serverURL + '/images/thumbnail_300x160/17.jpg' },
   { uri: serverURL + '/images/thumbnail_300x160/2.jpg' },
   { uri: serverURL + '/images/thumbnail_300x160/5.jpg' },
   { uri: serverURL + '/images/thumbnail_300x160/8.jpg' },
   { uri: serverURL + '/images/thumbnail_300x160/12.jpg' },
   { uri: serverURL + '/images/thumbnail_300x160/21.jpg' },
   { uri: serverURL + '/images/thumbnail_300x160/24.jpg' },
   { uri: serverURL + '/images/thumbnail_300x160/14.jpg' },
   { uri: serverURL + '/images/thumbnail_300x160/16.jpg' },
];
const posterImagePath_716x300 = [
   { uri: serverURL + '/images/poster_716x300/1.jpg' },
   { uri: serverURL + '/images/poster_716x300/2.jpg' },
   { uri: serverURL + '/images/poster_716x300/3er.jpg' },
   { uri: serverURL + '/images/poster_716x300/4.jpg' },
   { uri: serverURL + '/images/poster_716x300/5.jpg' },
   { uri: serverURL + '/images/poster_716x300/6.jpg' },
   { uri: serverURL + '/images/poster_716x300/7.jpg' },
   { uri: serverURL + '/images/poster_716x300/8.jpg' },
   { uri: serverURL + '/images/poster_716x300/12.jpg' },
   { uri: serverURL + '/images/poster_716x300/11.jpg' },
   { uri: serverURL + '/images/poster_716x300/16.jpg' },
   { uri: serverURL + '/images/poster_716x300/21.jpg' },
   { uri: serverURL + '/images/poster_716x300/10.jpg' },
   { uri: serverURL + '/images/poster_716x300/9.jpg' },
   { uri: serverURL + '/images/poster_716x300/19.jpg' },
   { uri: serverURL + '/images/poster_716x300/24.jpg' },
   { uri: serverURL + '/images/poster_716x300/13.jpg' },
   { uri: serverURL + '/images/poster_716x300/15.jpg' },
   { uri: serverURL + '/images/poster_716x300/20.jpg' },
   { uri: serverURL + '/images/poster_716x300/23.jpg' },
   { uri: serverURL + '/images/poster_716x300/14.jpg' },
   { uri: serverURL + '/images/poster_716x300/22.jpg' },
   { uri: serverURL + '/images/poster_716x300/18.jpg' },
   { uri: serverURL + '/images/poster_716x300/17.jpg' },
   { uri: serverURL + '/images/poster_716x300/2.jpg' },
   { uri: serverURL + '/images/poster_716x300/5.jpg' },
   { uri: serverURL + '/images/poster_716x300/8.jpg' },
   { uri: serverURL + '/images/poster_716x300/12.jpg' },
   { uri: serverURL + '/images/poster_716x300/21.jpg' },
   { uri: serverURL + '/images/poster_716x300/24.jpg' },
   { uri: serverURL + '/images/poster_716x300/14.jpg' },
   { uri: serverURL + '/images/poster_716x300/16.jpg' },
];
const posterImagePath_512x288 = [
   { uri: serverURL + '/images/poster_512x288/1.jpg' },
   { uri: serverURL + '/images/poster_512x288/2.jpg' },
   { uri: serverURL + '/images/poster_512x288/3.jpg' },
   { uri: serverURL + '/images/poster_512x288/4.jpg' },
   { uri: serverURL + '/images/poster_512x288/5.jpg' },
   { uri: serverURL + '/images/poster_512x288/6.jpg' },
   { uri: serverURL + '/images/poster_512x288/7.jpg' },
   { uri: serverURL + '/images/poster_512x288/8.jpg' },
   { uri: serverURL + '/images/poster_512x288/12.jpg' },
   { uri: serverURL + '/images/poster_512x288/11.jpg' },
   { uri: serverURL + '/images/poster_512x288/16.jpg' },
   { uri: serverURL + '/images/poster_512x288/21.jpg' },
   { uri: serverURL + '/images/poster_512x288/10.jpg' },
   { uri: serverURL + '/images/poster_512x288/9.jpg' },
   { uri: serverURL + '/images/poster_512x288/19.jpg' },
   { uri: serverURL + '/images/poster_512x288/24.jpg' },
   { uri: serverURL + '/images/poster_512x288/13.jpg' },
   { uri: serverURL + '/images/poster_512x288/15.jpg' },
   { uri: serverURL + '/images/poster_512x288/20.jpg' },
   { uri: serverURL + '/images/poster_512x288/23.jpg' },
   { uri: serverURL + '/images/poster_512x288/14.jpg' },
   { uri: serverURL + '/images/poster_512x288/22.jpg' },
   { uri: serverURL + '/images/poster_512x288/18.jpg' },
   { uri: serverURL + '/images/poster_512x288/17.jpg' },
   { uri: serverURL + '/images/poster_512x288/2.jpg' },
   { uri: serverURL + '/images/poster_512x288/5.jpg' },
   { uri: serverURL + '/images/poster_512x288/8.jpg' },
   { uri: serverURL + '/images/poster_512x288/12.jpg' },
   { uri: serverURL + '/images/poster_512x288/21.jpg' },
   { uri: serverURL + '/images/poster_512x288/24.jpg' },
   { uri: serverURL + '/images/poster_512x288/14.jpg' },
   { uri: serverURL + '/images/poster_512x288/16.jpg' },
];

var posterImagePath = windowSize.height > 720 ? posterImagePath_716x300 : posterImagePath_512x288;

const FocusableComponent = (props) => {
   let [state, setState] = useState({ imgscale: 1, bw: 0 });
   const onPress = () => { }

   const onBlur = (e) => {
      console.log("onBlur---------")
      setState({ imgscale: 1, bw: 0 });
   }

   const onFocus = (e) => {
      console.log("onFocus---------")
      setState({ imgscale: 1.2, bw: 2 });
      props.change((props.count));
   }

   if (props.count >= 24) {
      return (
         <TouchableOpacity isTVSelectable='true' activeOpacity={0.75} onBlur={onBlur} onFocus={onFocus} style={[styles.elementView]} >
            {/* // <Image style={{ transform: [{ scale: state.imgscale }], width: 300, height: 160, marginLeft: 30, marginTop: 16 }} source={thumbnailImagePath[props.count]}>
            // </Image> */}
            <ProgressiveImage uri={thumbnailImagePath[props.count]} defaultSource={DEFAULT_IMAGE_300_160} style={{ transform: [{ scale: state.imgscale }], width: 300, height: 160, marginLeft: 30, marginTop: 16 }} resizeMode="contain" />
         </TouchableOpacity>
      );
   } else if ((props.count >= 16)) {
      return (
         <TouchableHighlight isTVSelectable='true' onPress={onPress} activeOpacity={0.9} underlayColor='transparent'
            onBlur={onBlur} onFocus={onFocus}
            style={[styles.elementView]} >
            {/* // <Image style={{ transform: [{ scale: state.imgscale }], width: 300, height: 160, marginLeft: 30, marginTop: 16 }} source={thumbnailImagePath[props.count]} resizeMode="cover">
            // </Image> */}
            <ProgressiveImage uri={thumbnailImagePath[props.count]} defaultSource={DEFAULT_IMAGE_300_160} style={{ transform: [{ scale: state.imgscale }], width: 300, height: 160, marginLeft: 30, marginTop: 16 }} resizeMode="cover" />
         </TouchableHighlight>
      );
   } else if ((props.count >= 8)) {
      return (
         <Pressable isTVSelectable='true' onBlur={onBlur} onFocus={onFocus} style={[styles.elementView]} >
            {/* // <Image style={{ transform: [{ scale: state.imgscale }], width: 300, height: 160, marginLeft: 30, marginTop: 16 }} source={thumbnailImagePath[props.count]}>
            // </Image> */}
            <ProgressiveImage uri={thumbnailImagePath[props.count]} defaultSource={DEFAULT_IMAGE_300_160} style={{ transform: [{ scale: state.imgscale }], width: 300, height: 160, marginLeft: 30, marginTop: 16 }} resizeMode="cover" />
         </Pressable>
      );
   } else {
      return (
         <Pressable isTVSelectable='true' onBlur={onBlur} onFocus={onFocus} style={[styles.elementView]} >
            {/* // <Image style={{ borderWidth: state.bw, borderColor: 'lightcyan', width: 300, height: 160, marginLeft: 25, marginTop: 10 }} source={thumbnailImagePath[props.count]}>
            // </Image> */}
            <ProgressiveImage uri={thumbnailImagePath[props.count]} defaultSource={DEFAULT_IMAGE_300_160} style={{ borderWidth: state.bw, borderColor: 'lightcyan', width: 300, height: 160, marginLeft: 25, marginTop: 10 }} resizeMode="cover" />
         </Pressable>
      );
   }
}

const PosterView = (pvProps) => {
   React.useEffect(() => { pvProps.pvRef.current = setPosterIndex }, []);

   let content = pvProps.contentData;
   let [index, setIndex] = useState(0);
   let text1 = content[index].duration.concat("  |  ", content[index].genre, "  |  ", content[index].year)

   function setPosterIndex(count) {
      setIndex(count);
   }

   return (
      <>
         <View style={styles.posterContentView}>
            <Text style={styles.titleText}>{content[index].title} Title</Text>
            <Text style={[styles.titleTextContent, { fontSize: titleTextGenreSize }]}>{text1}</Text>
            <Text style={[styles.titleTextContent, { fontSize: titleTextContentSize }]}>{content[index].description}</Text>
         </View>
         <Image source={posterImagePath[index]} style={styles.posterView} resizeMode="contain">
         </Image>
         {/* // <ProgressiveImage uri={posterImagePath[index]} defaultSource={DEFAULT_IMAGE_700_300} style={styles.posterView} resizeMode="contain" /> */}
      </>
   );
}

const SampleVODPage = (props) => {
   const pvRef = React.useRef(null);

   function changeBackground(count) {
      pvRef.current(count);
   }

   const addItems = (n) => {
      var arr = [];
      for (var i = n; i < n + 8; i++) {
         arr.push(<FocusableComponent count={i} change={changeBackground}></FocusableComponent>);
      }
      return arr;
   }

   const horizontalScrollView = (x) => {
      return (
         <ScrollView style={styles.horizontalScrollView} horizontal={true}>
            {addItems(x)}
         </ScrollView>
      );
   }

   const horizontalScrollViewHeader = (text) => {
      return (
         <View style={{ margin: 10 }}>
            <Text style={styles.elementText}>
               {text}
            </Text>
         </View>
      );
   }

   const verticalScrollView = () => {
      return (
         <ScrollView style={styles.verticalScrollView}>
            {horizontalScrollViewHeader('Continue Watching')}
            {horizontalScrollView(0)}
            {horizontalScrollViewHeader('Favorites')}
            {horizontalScrollView(8)}
            {horizontalScrollViewHeader('Recommendations')}
            {horizontalScrollView(16)}
            {horizontalScrollViewHeader('My List')}
            {horizontalScrollView(24)}
         </ScrollView>
      );
   }

   return (
      <ImageBackground style={styles.backgroundimage} source={require('./images/bg.jpg')}>
         <PosterView pvRef={pvRef} contentData={props.contentData}></PosterView>
         {verticalScrollView()}
      </ImageBackground>
   );
}

const styles = StyleSheet.create({
   backgroundimage: {
      flex: 1,
      width: windowSize.width,
      height: windowSize.height,
   },
   posterView: {
      margin: 10,
      position: 'absolute',
      top: 20,
      left: windowSize.width / 2,
      width: '40%',
      height: '40%',
      shadowColor: 'black',
      shadowRadius: 10,
      shadowOpacity: 1,
      shadowOffset: { width: 5, height: 30 },
   },
   posterContentView: {
      margin: 10,
      position: 'absolute',
      top: 30,
      left: 30,
      width: '40%',
      height: '40%',
   },
   titleText: {
      color: 'white',
      fontWeight: 'bold',
      textShadowColor: 'black',
      textShadowRadius: 1,
      fontSize: titleTextFontSize
   },
   titleTextContent: {
      marginTop: 25,
      color: 'white',
   },
   verticalScrollView: {
      margin: 10,
      position: 'absolute',
      top: windowSize.height / 2,
      left: 30,
      width: '90%',
      height: '40%',
   },
   horizontalScrollView: {
      margin: 5,
   },
   elementView: {
      width: 360, // Thumbnail image size 
      height: 192,
      shadowColor: 'black',
   },
   elementText: {
      color: 'white',
      fontWeight: 'bold',
      fontSize: titleTextGenreSize
   }

});

export default SampleVODPage
