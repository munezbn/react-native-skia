import * as React from 'react';
import { View, AppRegistry, Image, Text } from 'react-native';

import { Canvas, Skia,
  Circle, Rect, Path, TextPath, Group,
  CornerPathEffect, DiscretePathEffect,
  SweepGradient, LinearGradient, vec} from "@shopify/react-native-skia";


const SimpleViewApp = React.Node = () => {
  const width = 256;
  const height = 256;
  const r1 = 215;
  const r2 = 128;

  const size = 128;
  const path = Skia.Path.Make();
  path.addCircle(size, size, size/2);

  return (
    <Canvas style={{ flex: 1 }}>

      <Rect x={0} y={0} width={256} height={256}>
        <SweepGradient
          c={vec(128, 128)}
          colors={["cyan", "magenta", "yellow", "cyan"]}
        />
      </Rect>

      <Circle cx={3*r2} cy={r2} r={r2}>
        <LinearGradient
          start={vec(0, 0)}
          end={vec(2 * r2, 2 * r2)}
          colors={["#00ff87", "#60efff"]}
        />
      </Circle>

      <Group>
        <LinearGradient
          start={vec(2 * r2, 2 * r2)}
          end={vec(4 * r2, 4 * r2)}
          colors={["#0061ff", "#60efff"]}
        />
        <Circle cx={3 * r2} cy={3 * r2} r={r2} />
      </Group>

      <Group>
        <LinearGradient
          start={vec(2 * r2, 2 * r2)}
          end={vec(4 * r2, 4 * r2)}
          colors={["#0061ff", "#60efff"]}
        />
      <Rect
        x={4*r2}
        y={10}
        width={128}
        height={256 - 16}
        color="#61DAFB">
        <CornerPathEffect r={64} />
      </Rect>
      </Group>

    </Canvas>
  );
};

AppRegistry.registerComponent('SimpleViewApp', () => SimpleViewApp);
