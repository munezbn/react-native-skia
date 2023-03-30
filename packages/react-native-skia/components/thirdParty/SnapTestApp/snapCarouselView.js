import * as React from "react";
import { Text, View, TouchableOpacity, TouchableHighlight } from "react-native";

import Carousel from "react-native-snap-carousel";
import PropChangeView from "./PropChangeView";

export default class SnapCarouselView extends React.Component {
  constructor(props) {
    super(props);

    this.state = {
      activeIndex: 3,
      ap: false,
      carouselItems: []
    };
    for (let i = 0; i < 20; i++) {
      this.state.carouselItems.push({
        title: "Item" + (i + 1),
        text: "Text" + (i + 1)
      });
    }
  }
  _renderItem({ item, index }) {
    return (
      <TouchableHighlight underlayColor={"red"} activeOpacity={0.1}>
        <View
          style={{
            backgroundColor: "floralwhite",
            borderRadius: 5,
            height: 200,
            width: 200,
            padding: 50,
            marginLeft: 5,
            marginRight: 25
          }}
        >
          <Text style={{ fontSize: 30 }}>{item.title}</Text>
          <Text>{item.text}</Text>
        </View>
      </TouchableHighlight>
    );
  }
  render() {
    //let SLIDER_WIDTH = 360;
    let SLIDER_WIDTH = 600;
    //console.log("SnapCarouselView >> props", this.props);

    const { carouselRef, ...carouselProps } = this.props;
    this.carouselProps = carouselProps;
    this.carouselRef = carouselRef;

    console.log("carouselProps:", carouselProps);
    console.log("carouselRef:", carouselRef);

    return (
      <View>
        <View
          ref1
          style={{
            borderColor: "red",
            borderWidth: 2,
            backgroundColor: "rebeccapurple",
            width: 700,
            height: 400,
            padding: 10
          }}
        >
          <Carousel
            layout={"default"}
            // ref={ref => this.carousel = ref}
            ref={(ref) => {
              this.carouselRef.current = ref;
              console.log("REF: ", ref);
            }}
            data={this.state.carouselItems}
            sliderWidth={SLIDER_WIDTH}
            itemWidth={200}
            //autoplay = {this.state.ap}
            autoplay={true}
            autoplayInterval={400}
            autoplayDelay={2000}
            //  layoutCardOffset = {150}

            useScrollView={true}
            lockScrollWhileSnapping={true}
            lockScrollTimeoutDuration={1000}
            firstItem={1}
            style={{ backgroundColor: "yellow" }}
            apparitionDelay={500}
            renderItem={this._renderItem}
            {...this.carouselProps}
            onSnapToItem={(index) => {
              // console.log("------onSnapToItem-------index:" + index);
              // this.setState({ activeIndex: index });
            }}
          />
        </View>
        <View style={{ display: "flex", flexDirection: "row" }}>
          <View>
            <Text style={{ fontSize: 30 }}>Methods</Text>
            <TouchableOpacity
              onPress={() => {
                this.carouselRef.current.snapToItem(0);
                this.carouselRef.current.startAutoplay();
              }}
              style={{
                margin: 10,
                alignItems: "center",
                justifyContent: "center",
                width: 250,
                height: 50,
                borderColor: "black",
                borderWidth: 2,
                backgroundColor: "#3529"
              }}
            >
              <Text style={{ fontSize: 30 }}>Start AutoPlay</Text>
            </TouchableOpacity>

            <TouchableOpacity
              onPress={() => {
                this.carouselRef.current.stopAutoplay();
                this.carouselRef.current.snapToItem(0);
              }}
              style={{
                margin: 8,
                alignItems: "center",
                justifyContent: "center",
                width: 250,
                height: 50,
                borderColor: "black",
                borderWidth: 2,
                backgroundColor: "#3529"
              }}
            >
              <Text style={{ fontSize: 30 }}>Stop AutoPlay</Text>
            </TouchableOpacity>
            <TouchableOpacity
              onPress={() => {
                this.carouselRef.current.snapToNext();
              }}
              style={{
                margin: 8,
                alignItems: "center",
                justifyContent: "center",
                width: 250,
                height: 50,
                borderColor: "black",
                borderWidth: 2,
                backgroundColor: "#3529"
              }}
            >
              <Text style={{ fontSize: 30 }}>Snap next</Text>
            </TouchableOpacity>
            <TouchableOpacity
              onPress={() => {
                this.carouselRef.current.snapToPrev();
              }}
              style={{
                margin: 8,
                alignItems: "center",
                justifyContent: "center",
                width: 250,
                height: 50,
                borderColor: "black",
                borderWidth: 2,
                backgroundColor: "#3529"
              }}
            >
              <Text style={{ fontSize: 30 }}>Snap Prev</Text>
            </TouchableOpacity>
          </View>
          <View>
            <PropChangeView {...this.carouselProps} />
          </View>
        </View>
      </View>
    );
  }
}
