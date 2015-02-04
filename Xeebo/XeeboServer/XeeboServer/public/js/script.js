var addEvent = function(elem, type, eventHandle) {
  if (elem == null || typeof(elem) == 'undefined') return;
  if ( elem.addEventListener ) {
    elem.addEventListener( type, eventHandle, false );
  } else if ( elem.attachEvent ) {
    elem.attachEvent( "on" + type, eventHandle );
  } else {
    elem["on"+type]=eventHandle;
  }
};
var fixDepth = function() {
  console.log("test");
  var height = window.innerHeight;
  var middle = height/2;
  var unitOffset = middle/26-2.2;
  var paddingVal = Math.round(unitOffset*26);
  console.log(paddingVal)
  $("#depthGauge").css("padding-top",paddingVal+"px")
};

var onLoad = function() {
  addEvent(window,"resize",fixDepth);
  fixDepth();
};
onLoad();