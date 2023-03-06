import * as React from "react"
import {Svg, G, Text, TSpan} 
from 'react-native-svg';

const startXOffset='10';
const startYOffset='10';
const fill="yellow";
const stroke="green";
const fontSize='22';
const fontFamily='DejaVuSans-Bold';
const wordSpacing='10';
const LetterSpacing='3';
const yoffset=22+5;
const Long_Text='Svg does not support paragraph.It means content supposed to write in a single line.';

const text_anchor =  (
   <Svg height='90' width="800"  >
      <Text fill={fill} fontSize={fontSize} fontFamily={fontFamily} >
          <TSpan x='100' dy={yoffset} textAnchor='start'>textAnchor : Start</TSpan>
          <TSpan x='100' dy={yoffset} textAnchor='middle'>textAnchor : Middle</TSpan>
          <TSpan x='100' dy={yoffset} textAnchor='end'>textAnchor : End</TSpan>
        </Text>
    </Svg>
);

const text_decoration =  (
     <Svg height='110' width="800"  >
      <Text fill={fill} fontSize='20' fontFamily={fontFamily} >
          <TSpan x='50' dy={yoffset} textDecoration='none'>textDecoration : None</TSpan>
          <TSpan x='50' dy={yoffset} textDecoration='underline'>textDecoration : Underline</TSpan>
          <TSpan x='50' dy={yoffset} textDecoration='line-through'>textDecoration : Line Through</TSpan>
          <TSpan x='50' dy={yoffset} textDecoration='overline'>textDecoration : Overline</TSpan>
        </Text>
    </Svg>
);

const letter_Spacing =  (
     <Svg height="250" width="800"  >
      <Text fill={fill} fontSize={fontSize} fontFamily={fontFamily} >
          <TSpan x='50' dy={yoffset} letterSpacing='3'>Letter Spacing as 3px </TSpan>
          <TSpan x='50' dy={yoffset} letterSpacing='1'>Letter Spacing as 1px</TSpan>
          <TSpan x='50' dy={yoffset} >Letter Spacing as defaut</TSpan>
          <TSpan x='50' dy={yoffset} letterSpacing='0'>Letter Spacing as 0</TSpan>
          <TSpan x='50' dy={yoffset} letterSpacing='-1'>Letter Spacing as -1</TSpan>
          <TSpan x='50' dy={yoffset} letterSpacing='-3'>Letter Spacing as -3</TSpan>
          <TSpan x='50' dy={yoffset} letterSpacing='.5'>Letter Spacing as .5px</TSpan>
          <TSpan x='50' dy={yoffset} letterSpacing='10'>Letter Spacing as 10px</TSpan>
        </Text>
    </Svg>
);

const word_Spacing =(
     <Svg height="90" width="800"  >
      <Text fill={fill} fontSize={fontSize} fontFamily={fontFamily} >
          <TSpan x='50' dy={yoffset} >Word Spacing as default</TSpan>
          <TSpan x='50' dy={yoffset} wordSpacing='50'>Word Spacing as 50 px</TSpan>
          <TSpan x='50' dy={yoffset} wordSpacing='0'>Word Spacing as 0</TSpan>
        </Text>
    </Svg>

);

const font_weight =  (
     <Svg height="120" width="800"  >
      <Text fill={fill} fontSize={fontSize} fontFamily={fontFamily} >
          <TSpan x='50' dy={yoffset} fontWeight='bold'>Font Weight as bold</TSpan>
          <TSpan x='50' dy={yoffset} fontWeight='normal'>Font Weight as normal</TSpan>
          <TSpan x='50' dy={yoffset} fontWeight='800'>Font Weight as 800</TSpan>
          <TSpan x='50' dy={yoffset} fontWeight='100'>Font Weight as 100</TSpan>
        </Text>
    </Svg>
);

const font_style =  (
     <Svg height="90" width="800"  >
      <Text fill={fill} fontSize={fontSize} fontFamily={fontFamily} >
          <TSpan x='50' dy={yoffset} textDecoration='normal'>Font Style as normal</TSpan>
          <TSpan x='50' dy={yoffset} fontStyle='italic'>Font Style as italic</TSpan>
          <TSpan x='50' dy={yoffset} fontStyle='oblique'>Font Style as oblique</TSpan>
        </Text>
    </Svg>
);

const deltaPositioning =(
     <Svg height="400" width="800"  >
      <Text fill={fill} fontSize={fontSize} fontFamily={fontFamily} >
          <TSpan x='50' y='150' fill='blue'>1. Text @ x=50 y=150</TSpan>
          <TSpan dy='50'>2. Text @ dy=50 </TSpan>
          <TSpan dx='50' >3. Text @ dx=50</TSpan>
          <TSpan x='0' y='300' fill='blue'>4. Text @ x=0 y=300</TSpan>
          <TSpan dy='50'>5.Text @ dy=50 </TSpan>
          <TSpan dx='50'>6.Text @ dx=50 </TSpan>
          <TSpan x='0' y='50' fill='blue'>7. Text @ x=0 y=50</TSpan>
          <TSpan dy='50'>8.Text @ dy=50 </TSpan>
          <TSpan dx='50'>9.Text @ dx=50 </TSpan>
        </Text>
    </Svg>

);

const text_style =  (
     <Svg height="200" width="800"  >
      <Text fill={fill} fontSize={fontSize} fontFamily={fontFamily} >
          <TSpan x='50' dy='40' fontSize='40'>Text With Fill</TSpan>
          <TSpan x='50' dy='40' fill='none' stroke={stroke} fontSize='40' strokeWidth='2'>Text With stroke</TSpan>
          <TSpan x='50' dy='50' stroke={stroke} fontSize='50' strokeWidth='3'>Text With Fill & Stroke</TSpan>
          <TSpan x='50' dy='50' fill='blue' stroke='yellow' fontSize='50' strokeWidth='2' strokeLinecap="square" strokeDasharray="2,4">Text With Fill & Stroke styled</TSpan>
        </Text>
    </Svg>
);

const full_set =  (
     <Svg height="250" width="800"  >
      <Text fill='yellow' fontSize={fontSize} fontFamily={fontFamily} 
            letterSpacing='5'
            textAnchor='start'
            textDecoration='underline'
            x='100'
            dy='50'
            >
          <TSpan >Style from Parent    </TSpan>
          <TSpan x='100' dy='40' textDecoration='line-through'>
                 Text Decoration changed to line-through
          </TSpan>
          <TSpan x='100' dy='40' textAnchor='middle'>
                 Text Anchor changed to middle
          </TSpan>
          <TSpan x='100' dy='40' stroke='green'>
                 fill color changed to green
          </TSpan>
          <TSpan x='100' dy='40' fontFamily='monospace'>
                 font family changed to monospace
          </TSpan>
        </Text>
    </Svg>
);

const paragrph_test =(
     <Svg height="200" width="800"  >
      <Text fill={fill} fontSize={fontSize} fontFamily={fontFamily} >
          <TSpan x= '0' dy='50' fill='yellow'>{Long_Text}</TSpan>
          <TSpan x= '0' dy='50'>2. TSpan with delta x= '0' dy='50' </TSpan>
          <TSpan dx='50' >3. TSpan with delta dx='50'</TSpan>
          <TSpan x= '0' dy='50' fill='yellow' fontSize='18'>{Long_Text}</TSpan>
        </Text>
    </Svg>

);

const features = [text_style,font_weight,font_style,text_anchor,letter_Spacing,word_Spacing,text_decoration,deltaPositioning,full_set,paragrph_test];
var featureName=['Text with Stroke & Fill','Font Weight','Font Style','Text Anchor','Letter Spacing','Word Spacing','Text Decoration','Delta Positioning','Combined Feature with Inheritence','Long Test with delta positioning'];

export default {featureName,features};

