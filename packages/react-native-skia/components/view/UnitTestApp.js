import React, { useState} from "react";
import { AppRegistry,StyleSheet,Dimensions} from "react-native";
import { View,Text,TouchableHighlight} from "react-native";

const windowSize = Dimensions.get('window');

const TestPages = [
    {Title:"Show casing Frame types",Name:'View'},
    {Title:"Show casing Shadow types : On View",Name:'Shadow'},
    {Title:"Show casing Shadow types : On View With Transform",Name:'ShadowWithTransform'},
    {Title:"Show casing Shadow types : On Image",Name:'ImageShadow'},
    {Title:"Show casing Shadow types : On Image With Transform",Name:'ImageShadowWithTransform'},
    {Title:"Show casing Shadow types : On Image With Resize Mode",Name:'ImageShadowWithResizeMode'},
];

var FramesPerRow_FrameTypes = 4; // Max of only 2 rows in a page
const TestCase_FrameTypes = [
    {Title:"BG + monChrome Border",backgroundColor:'burlywood',borderColor:'red',AdditionDescription:''},
    {Title:"Default monoChrome Border",AdditionDescription:'BorderWidth : Non Zero, Border & BackGround Color:Not Specified'},
    {Title:"BG + PolyChrome Border",backgroundColor:'burlywood',borderBottomColor:'red',borderRightColor:'yellow',AdditionDescription:'Border Color not specified for Left & Top'},
    {Title:"BG+Border with transparent Alpha",borderColor:'#ff000000',AdditionDescription:'All sides has Transparent alpha'},

    {Title:"BG +InVisible monChrome Border",backgroundColor:'burlywood',borderColor:'red',borderWidth:0,AdditionDescription:'BorderWidth :0, Color:Valid'},
    {Title:"BG +Discrete Border",backgroundColor:'burlywood',borderRightWidth:0,borderLeftWidth:0,AdditionDescription:'Border width invalid for missing sides + Border Color Not specified'},
    {Title:"Discrete Border",borderRightWidth:15,borderBottomWidth:5,borderTopWidth:5,borderBottomColor:'red',borderRightColor:'yellow',AdditionDescription:'Border with varying width'},
];

var FramesPerRow_Shadow = 3; // Max of only 2 rows in a page
const TestCase_ShadowOnView = [
    {Title:"BG + Rect Border",backgroundColor:'burlywood',borderColor:'red',AdditionDescription:''},
    {Title:"No BG + Rect Border ",borderColor:'red',AdditionDescription:'BorderWidth :Valid, BackGround Color:Not Specified'},
    {Title:"polyChrome Rect Border",borderBottomColor:'red',AdditionDescription:'BorderWidth : Non Zero, Color:Not Specified'},
    {Title:"Discrete Border",borderBottomColor:'red',borderRightColor:'yellow',AdditionDescription:'Borders with varying color & uniform width'},
    {Title:"Discrete Border",backgroundColor:'burlywood',borderRightWidth:0,borderLeftWidth:0,AdditionDescription:'Borders with varying/invisible width'},
    {Title:"InVisible BG+Border",borderColor:'#ff000000',AdditionDescription:'Background color : Not Specified+ BorderColor : has Alpha Zero'},

];

const shadowProperty={
    shadowColor:'aqua',
    shadowOpacity:1,
    shadowOffset:{width:10, height:10}}

const getFrames = (n,count,testCase,styles) => {
   var arr = [];
   console.log("testCaseTitle :: ",testCase);

   for (var i=n; i<(n+count); i++){
       var props = Object.assign({}, styles,TestCase_FrameTypes[i]);
       console.log("TestCases :: ",props);

      arr.push(  <View style={props}>
                    {getFramesDescription(TestCase_FrameTypes[i])}
                </View>);
   }
   return arr;
}

const getFramesDescription = (FrameProps) => {
   var arr = [];
   var headerStyle = Object.assign({}, styles.TextStyle,
                                      {color:'blue',
                                       fontWeight:'bold'});
    return   (     <Text>
                   <Text style ={headerStyle}>{FrameProps.Title}{'\n'}{'\n'}</Text>
                   <Text style ={styles.TextStyle}>{FrameProps.AdditionDescription}{'\n'}</Text>
                  </Text>
             );
}

const getTestCases=(testCaseTitle)=>{
    var TestCases =[];
    var framesPerRow;
    var stylesProps=styles.contentStyle;
    if(testCaseTitle == 'View') {
        TestCases=TestCase_FrameTypes;
        framesPerRow=FramesPerRow_FrameTypes;
    } else if(testCaseTitle == 'Shadow') {
        TestCases=TestCase_ShadowOnView;
        framesPerRow=FramesPerRow_Shadow;
        stylesProps = Object.assign({}, shadowProperty,stylesProps);
    }else if(testCaseTitle == 'ShadowWithTransform') {
        TestCases=TestCase_ShadowOnView;
        framesPerRow=FramesPerRow_Shadow;
    }else if(testCaseTitle == 'ImageShadow') {
        TestCases=TestCase_ShadowOnImage;
        framesPerRow=FramesPerRow_Shadow;
    }else if(testCaseTitle == 'ImageShadowWithTransform') {
        TestCases=TestCase_ShadowOnImage;
        framesPerRow=FramesPerRow_Shadow;
    }else if(testCaseTitle == 'ImageShadowWithResizeMode') {
        TestCases=TestCase_ShadowOnImage;
        framesPerRow=FramesPerRow_Shadow;
    }

    var arr = [];
    if(framesPerRow > TestCases.length) {
        arr.push(<View style={styles.ViewStyle}>
                    {getFrames(0,TestCases.length,testCaseTitle,stylesProps)}
                  </View>
                );
    } else {
        arr.push (
            <View style={styles.ViewStyle}>
                {getFrames(0,framesPerRow,testCaseTitle,stylesProps)}
            </View>
        )
        if( TestCase_FrameTypes.length > framesPerRow) {
            arr.push (
                 <View style={styles.ViewStyle}>
                     {getFrames(framesPerRow,TestCases.length-framesPerRow,testCaseTitle,stylesProps)}
                 </View>
            )
        }
    }
    return arr;
}

const UnitTestApp = () => {

    let [TestCaseCount, setTestCase] = useState(0);

    const getButtons =()=>{
        var arr=[];
        if(TestCaseCount > 0) {
            arr.push(<TouchableHighlight underlayColor='#61dafb'
                      style={styles.button}
                      onPress={() => {
                            setTestCase(TestCaseCount -1)
                            console.log("calling Previous")} 
                        }
                      >
                      <Text>Previous</Text>
                    </TouchableHighlight>);
        }
        if(TestCaseCount<(TestPages.length-1)) {
            arr.push(<TouchableHighlight underlayColor='#61dafb'
                      style={styles.button}
                      onPress={() => {
                          setTestCase(TestCaseCount +1 )
                          console.log("calling next")} 
                        }
                      >
                      <Text>Next</Text>
                    </TouchableHighlight>);
        }
        return arr;
    }
    return (
        <View style={styles.PageStyle}>
            <Text style={styles.HeaderTextStyle}>{TestPages[TestCaseCount].Title}</Text>
                {getTestCases(TestPages[TestCaseCount].Name)}
            <View style={styles.ButtonView}>
                {getButtons()}
            </View>
        </View>
    )
}

const styles = StyleSheet.create({
    PageStyle: {
        marginTop: '2%',
        marginLeft:'2%',
       alignItems : 'center',
       justifyContent : 'space-evenly',
       flexDirection:'column',
       borderWidth: 3,
       width : '95%',
       height : '95%',
       backgroundColor:'#5f9ea0',//cadetblue
    },
    ViewStyle: {
       marginLeft:'1%',
       marginLeft:'2%',
       justifyContent : 'space-between',
       flexDirection:'row',
       width : '95%',
       padding:'1%',
       height : windowSize.height*.40,
       borderWidth: 3,
       borderRadius : 10,
       backgroundColor:'transparent',
    },
    contentStyle: {
       marginTop:'1%',
       marginLeft:'1%',
       height :'95%',
       width : '20%',
       alignItems : 'center',
       justifyContent : 'center',
       borderRadius : 20,
       borderWidth:10,

    },
    ButtonView: {
       marginRight:'2%',
       marginLeft: '2%',
       width : '95%',
       alignItems : 'flex-start',
       justifyContent : 'space-between',
       flexDirection:'row',
    },
    button: {
      alignItems: "center",
      backgroundColor: "#DDDDDD",
      padding: 10,
      width: windowSize.width*.1
    },
    HeaderTextStyle: {
       fontSize : windowSize.width/50,
       fontWeight:'bold'
    },
    TextStyle: {
        textAlign:'center'
    },


});
AppRegistry.registerComponent('SimpleViewApp', () => UnitTestApp);

export default UnitTestApp

