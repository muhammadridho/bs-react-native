[@bs.config {jsx: 3}];

open ReactNative;

let styles =
  StyleSheet.create(
    Style.{
      "header":
        style(
          ~justifyContent=`center,
          ~alignItems=`center,
          ~backgroundColor=color("#fefefe"),
          (),
        ),
    },
  );

[@react.component]
let make = (~currentLocation, ~children) => {
  <View style=styles##header>
    <Image source={Image.Source.fromUri(~uri="/apple-touch-icon.png", ())} />
    <Text> "Header"->React.string </Text>
  </View>;
};
