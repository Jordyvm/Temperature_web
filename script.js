
var ref = firebase.database().ref();

  var ref = firebase.database().ref();                           
  ref.on("value", function(snapshot){
    var data = snapshot.val();
    current.innerHTML = data.currentTemp.toPrecision(4);
    max.innerHTML = data.maxTemp.toPrecision(4);
    min.innerHTML = data.minTemp.toPrecision(4);
});