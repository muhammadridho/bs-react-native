


var NativeEvent = /* module */[];

function layout(t) {
  var l = t.nativeEvent.layout;
  return /* record */[
          /* x */l.x,
          /* y */l.y,
          /* width */l.width,
          /* height */l.height
        ];
}

var NativeLayoutEvent = /* module */[/* layout */layout];

function contentOffset(t) {
  var co = t.nativeEvent.contentOffset;
  return /* record */[
          /* x */co.x,
          /* y */co.y
        ];
}

function contentSize(t) {
  var cs = t.nativeEvent.contentSize;
  return /* record */[
          /* width */cs.width,
          /* height */cs.height
        ];
}

function layoutMeasurement(t) {
  var lm = t.nativeEvent.layoutMeasurement;
  return /* record */[
          /* width */lm.width,
          /* height */lm.height
        ];
}

function contentInset(t) {
  var ci = t.nativeEvent.contentInset;
  return /* record */[
          /* bottom */ci.bottom,
          /* top */ci.top,
          /* left */ci.left,
          /* right */ci.right
        ];
}

var NativeScrollEvent = /* module */[
  /* contentOffset */contentOffset,
  /* contentSize */contentSize,
  /* layoutMeasurement */layoutMeasurement,
  /* contentInset */contentInset
];

var NativePressEvent = 0;

export {
  NativeEvent ,
  NativePressEvent ,
  NativeLayoutEvent ,
  NativeScrollEvent ,
  
}
/* No side effect */
