import React, { useState, useRef , Component} from "react";
import { TouchableHighlight, TouchableOpacity, Pressable, Text, View, ImageBackground, Image, ScrollView } from "react-native";
import { Dimensions , StyleSheet} from "react-native";
import { RecyclerListView, DataProvider, LayoutProvider } from "recyclerlistview";

const windowSize = Dimensions.get('window');
let titleTextFontSize = windowSize.height/25;
let titleTextContentSize = windowSize.height/45;
let titleTextGenreSize = windowSize.height/35;
let content = [];
let hsvWidth = (windowSize.width/100)*90;
let aheadOffset = windowSize.height*3;

const thumbnailImagePath = [
      require('./images/thumbnail_300x160/1.jpg'),
      require('./images/thumbnail_300x160/2.jpg'),
      require('./images/thumbnail_300x160/3.jpg'),
      require('./images/thumbnail_300x160/4.jpg'),
      require('./images/thumbnail_300x160/5.jpg'),
      require('./images/thumbnail_300x160/6.jpg'),
      require('./images/thumbnail_300x160/7.jpg'),
      require('./images/thumbnail_300x160/8.jpg'),
      require('./images/thumbnail_300x160/12.jpg'),
      require('./images/thumbnail_300x160/11.jpg'),
      require('./images/thumbnail_300x160/16.jpg'),
      require('./images/thumbnail_300x160/21.jpg'),
      require('./images/thumbnail_300x160/10.jpg'),
      require('./images/thumbnail_300x160/9.jpg'),
      require('./images/thumbnail_300x160/19.jpg'),
      require('./images/thumbnail_300x160/24.jpg'),
      require('./images/thumbnail_300x160/13.jpg'),
      require('./images/thumbnail_300x160/15.jpg'),
      require('./images/thumbnail_300x160/20.jpg'),
      require('./images/thumbnail_300x160/23.jpg'),
      require('./images/thumbnail_300x160/14.jpg'),
      require('./images/thumbnail_300x160/22.jpg'),
      require('./images/thumbnail_300x160/18.jpg'),
      require('./images/thumbnail_300x160/17.jpg'),
      require('./images/thumbnail_300x160/2.jpg'),
      require('./images/thumbnail_300x160/5.jpg'),
      require('./images/thumbnail_300x160/8.jpg'),
      require('./images/thumbnail_300x160/12.jpg'),
      require('./images/thumbnail_300x160/21.jpg'),
      require('./images/thumbnail_300x160/24.jpg'),
      require('./images/thumbnail_300x160/14.jpg'),
      require('./images/thumbnail_300x160/16.jpg'),
];
const posterImagePath_716x300 = [
      require('./images/poster_716x300/1.jpg'),
      require('./images/poster_716x300/2.jpg'),
      require('./images/poster_716x300/3.jpg'),
      require('./images/poster_716x300/4.jpg'),
      require('./images/poster_716x300/5.jpg'),
      require('./images/poster_716x300/6.jpg'),
      require('./images/poster_716x300/7.jpg'),
      require('./images/poster_716x300/8.jpg'),
      require('./images/poster_716x300/12.jpg'),
      require('./images/poster_716x300/11.jpg'),
      require('./images/poster_716x300/16.jpg'),
      require('./images/poster_716x300/21.jpg'),
      require('./images/poster_716x300/10.jpg'),
      require('./images/poster_716x300/9.jpg'),
      require('./images/poster_716x300/19.jpg'),
      require('./images/poster_716x300/24.jpg'),
      require('./images/poster_716x300/13.jpg'),
      require('./images/poster_716x300/15.jpg'),
      require('./images/poster_716x300/20.jpg'),
      require('./images/poster_716x300/23.jpg'),
      require('./images/poster_716x300/14.jpg'),
      require('./images/poster_716x300/22.jpg'),
      require('./images/poster_716x300/18.jpg'),
      require('./images/poster_716x300/17.jpg'),
      require('./images/poster_716x300/2.jpg'),
      require('./images/poster_716x300/5.jpg'),
      require('./images/poster_716x300/8.jpg'),
      require('./images/poster_716x300/12.jpg'),
      require('./images/poster_716x300/21.jpg'),
      require('./images/poster_716x300/24.jpg'),
      require('./images/poster_716x300/14.jpg'),
      require('./images/poster_716x300/16.jpg'),
];
const posterImagePath_512x288 = [
      require('./images/poster_512x288/1.jpg'),
      require('./images/poster_512x288/2.jpg'),
      require('./images/poster_512x288/3.jpg'),
      require('./images/poster_512x288/4.jpg'),
      require('./images/poster_512x288/5.jpg'),
      require('./images/poster_512x288/6.jpg'),
      require('./images/poster_512x288/7.jpg'),
      require('./images/poster_512x288/8.jpg'),
      require('./images/poster_512x288/12.jpg'),
      require('./images/poster_512x288/11.jpg'),
      require('./images/poster_512x288/16.jpg'),
      require('./images/poster_512x288/21.jpg'),
      require('./images/poster_512x288/10.jpg'),
      require('./images/poster_512x288/9.jpg'),
      require('./images/poster_512x288/19.jpg'),
      require('./images/poster_512x288/24.jpg'),
      require('./images/poster_512x288/13.jpg'),
      require('./images/poster_512x288/15.jpg'),
      require('./images/poster_512x288/20.jpg'),
      require('./images/poster_512x288/23.jpg'),
      require('./images/poster_512x288/14.jpg'),
      require('./images/poster_512x288/22.jpg'),
      require('./images/poster_512x288/18.jpg'),
      require('./images/poster_512x288/17.jpg'),
      require('./images/poster_512x288/2.jpg'),
      require('./images/poster_512x288/5.jpg'),
      require('./images/poster_512x288/8.jpg'),
      require('./images/poster_512x288/12.jpg'),
      require('./images/poster_512x288/21.jpg'),
      require('./images/poster_512x288/24.jpg'),
      require('./images/poster_512x288/14.jpg'),
      require('./images/poster_512x288/16.jpg'),
];

var posterImagePath = windowSize.height > 720 ? posterImagePath_716x300 : posterImagePath_512x288 ;

const ViewTypes = {
    FULL: 0,
    HALF_LEFT: 1,
    HALF_RIGHT: 2
};

let containerCount = 0;
let index = 0;

class CellContainer extends React.Component {
    constructor(args) {
        super(args);
        index +=8;
        if(index > 24) index = 0;
        this._indexId = index;
        this.changeBackground = args.changeBackground;
    }

    addItems = () => {
       var arr = [];
       let n = this._indexId
       for (var i=n; i<n+8; i++){
          arr.push(<FocusableComponent count={i} change={this.changeBackground}></FocusableComponent>);
       }
       return arr;
    }

    render() {
        return(
          <ScrollView style={styles.horizontalScrollView} horizontal={true} >
            {this.addItems()}
          </ScrollView>
        );
    }
}

class RecycleTestComponent extends React.Component {
    constructor(args) {
        super(args);
        let dataProvider = new DataProvider((r1, r2) => {
            return r1 !== r2;
        });
        this._layoutProvider = new LayoutProvider(
            index => {
                    return ViewTypes.FULL;
            },
            (type, dim) => {
                switch (type) {
                    case ViewTypes.FULL:
                        dim.width = hsvWidth-10;
                        dim.height = 220;
                        break;
                    default:
                        dim.width = 0;
                        dim.height = 0;
                }
            }
        );

        this._rowRenderer = this._rowRenderer.bind(this);

        //Since component should always render once data has changed, make data provider part of the state
        this.state = {
            dataProvider: dataProvider.cloneWithRows(this._generateArray(30)),
            count : 30
        };

        this.changeBackground = args.changeBackground;

    }

    _generateArray(n) {
        let arr = new Array(n);
        for (let i = 0; i < n; i++) {
            arr[i] = i;
        }
        return arr;
    }

    _rowRenderer(type, data) {
        switch (type) {
            case ViewTypes.FULL:
                return (
                 <>
                   <Text style={styles.elementText}>{data}</Text>
                   <CellContainer changeBackground={this.changeBackground}>
                   </CellContainer>
                 </>
                );
            default:
                return null;
        }
    }

    handleEnd() {
           this.setState({dataProvider:this.state.dataProvider.cloneWithRows(this._generateArray(this.state.count+30)),
                          count:this.state.count+30});
    }

    render() {
        return <RecyclerListView style={styles.verticalScrollView} layoutProvider={this._layoutProvider}
                         dataProvider={this.state.dataProvider} rowRenderer={this._rowRenderer}
                         onEndReached={this.handleEnd.bind(this)} renderAheadOffset={aheadOffset}/>;
    }
}

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
       props.change((props.count));
   }

       return (
          <Pressable isTVSelectable='true' onBlur={onBlur} onFocus={onFocus} style={[styles.elementView]} >
             <Image style={{transform:[{scale: state.imgscale}],width:300,height:160,marginLeft:30,marginTop:16}} source={thumbnailImagePath[props.count]}>
             </Image>
          </Pressable>
       );
}

const PosterView = (pvProps) => {
  React.useEffect(()=>{pvProps.pvRef.current=setPosterIndex},[]);

  let content = pvProps.contentData;
  let [index, setIndex] = useState(0);
  let text1 = content[index].duration.concat("  |  ", content[index].genre, "  |  ", content[index].year)

  function setPosterIndex(count) {
     setIndex(count);
  }

  return (
   <>
    <View style={styles.posterContentView}>
      <Text style={styles.titleText}>{content[index].title}</Text>
      <Text style={[styles.titleTextContent,{fontSize:titleTextGenreSize}]}>{text1}</Text>
      <Text style={[styles.titleTextContent,{fontSize:titleTextContentSize}]}>{content[index].description}</Text>
    </View>
    <Image source={posterImagePath[index]} style={styles.posterView} resizeMode="contain">
    </Image>
   </>
  );
}

const SampleVODPage = (props) => {
    const pvRef = React.useRef(null);

    function changeBackground(count) {
       pvRef.current(count);
    }

    return (
        <ImageBackground style={styles.backgroundimage} source={require('./images/bg.jpg')}>
           <PosterView pvRef={pvRef} contentData={props.contentData}></PosterView>
           <RecycleTestComponent changeBackground={changeBackground}></RecycleTestComponent>
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
       position : 'absolute',
       top : 20,
       left : windowSize.width/2,
       width : '40%',
       height : '40%',
       shadowColor: 'black',
       shadowRadius: 10,
       shadowOpacity: 0,
       shadowOffset: {width:5 , height:30},
    },
    posterContentView: {
       margin: 10,
       position : 'absolute',
       top : 30,
       left : 30,
       width : '40%',
       height : '40%',
    },
    titleText: {
       color : 'white',
       fontWeight : 'bold',
       textShadowColor : 'black',
       textShadowRadius : 1,
       fontSize : titleTextFontSize
    },
    titleTextContent: {
       marginTop : 25,
       color : 'white',
    },
    verticalScrollView: {
       margin : 10,
       position : 'absolute',
       top : windowSize.height/2,
       left : 30,
       width : '90%',
       height : '40%',
    },
    horizontalScrollView: {
       margin : 5,
    },
    elementView: {
       width : 360, // Thumbnail image size 
       height : 192,
       shadowColor: 'black',
    },
    elementText: {
       color : 'white',
       fontWeight : 'bold',
       fontSize : 10
    }

});

export default SampleVODPage
