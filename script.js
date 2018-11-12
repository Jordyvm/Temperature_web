
var ref = firebase.database().ref();

  var ref = firebase.database().ref();                           
  ref.on("value", function(snapshot){
    var data = snapshot.val();
    current.innerHTML = data.currentTemp;
    max.innerHTML = data.maxTemp;
    min.innerHTML = data.minTemp;
});