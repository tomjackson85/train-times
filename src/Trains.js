
var keyHomeStation = 100;
var valueHomeStation = 'WLI';
var keyWorkStation = 101;
var valueWorkStation = 'LEW';

// Persist write a key with associated value
localStorage.setItem(keyHomeStation, valueHomeStation);
localStorage.setItem(keyWorkStation, valueWorkStation);

// Persist read a key's value. May be null!
var homeStation = localStorage.getItem(keyHomeStation);
var workStation = localStorage.getItem(keyWorkStation);

console.log(homeStation);
console.log(workStation);

var xhrRequest = function (url, type, callback) {
  var xhr = new XMLHttpRequest();
  xhr.onload = function () {
    callback(this.responseText);
  };
  xhr.open(type, url);
  xhr.send();
};

function locationSuccess(pos) {
  // We will request the weather here
  
  console.log("LAT: " + pos.coords.latitude);
  console.log("LON: " + pos.coords.longitude);
  
 }

function locationError(err) {
  console.log('Error requesting location!');
}

function nullCheckJson(json){
  if(!json){
    return "";
  }else{
    return json;
  }
}

function getTrains(fromStation, toStation) {
//  navigator.geolocation.getCurrentPosition(
//    locationSuccess,
//    locationError,
//    {timeout: 15000, maximumAge: 60000}
//  );
  
  // Construct URL
  var url = 'https://huxley.apphb.com/all/'+ fromStation +'/to/'+ toStation +'/5?accessToken=DA1C7740-9DA0-11E4-80E6-A920340000B1';

  // Send request to OpenWeatherMap
  xhrRequest(url, 'GET', 
    function(responseText) {
      // responseText contains a JSON object with weather info
      var json = JSON.parse(responseText);
      
      console.log(json.trainServices[0].destination[0].via);
      
      var serialisedTrainString = "";
      
      for(x in json.trainServices){
        serialisedTrainString += nullCheckJson(json.trainServices[x].destination[0].locationName) + "|";
        serialisedTrainString += nullCheckJson(json.trainServices[x].destination[0].via) + "|";
        serialisedTrainString += nullCheckJson(json.trainServices[x].std) + "|";
        serialisedTrainString += nullCheckJson(json.trainServices[x].etd) + "|";
        serialisedTrainString += nullCheckJson(json.trainServices[x].platform) + "~";
      }
      
      // strip of the last ~
      if(serialisedTrainString.slice(-1)== "~"){
         serialisedTrainString = serialisedTrainString.slice(0,-1);
         }
      
      console.log(serialisedTrainString);
      
      // Assemble dictionary using our keys
      var dictionary = {
        'KEY_STATION': nullCheckJson(json.locationName),
        'KEY_FILTER_STATION': nullCheckJson(json.filterLocationName),
        'KEY_TRAIN_DATA':serialisedTrainString
      };

      // Send to Pebble
      Pebble.sendAppMessage(dictionary,
      function(e) {
        console.log('Weather info sent to Pebble successfully!');
      },
      function(e) {
      console.log('Error sending weather info to Pebble!');
      }
      );
      
    }      
  );
}

function getTrainsBasedOnTime(){
  var myDate = new Date();   
    if ( myDate.getHours() < 12 )  
    {   
      getTrains(homeStation,workStation);   
    } 
    else {
      getTrains(workStation,homeStation);
    }
}

// Listen for when the watchface is opened
Pebble.addEventListener('ready', 
  function(e) {
    console.log('PebbleKit JS ready!');
    
       getTrainsBasedOnTime();

  }
);

// Listen for when an AppMessage is received
Pebble.addEventListener('appmessage',
  function(e) {
    console.log('AppMessage received!');

       getTrainsBasedOnTime();
      
  }                     
);



// Configuration

Pebble.addEventListener("showConfiguration",
  function(e) {
    //Load the remote config page
    //Pebble.openURL("https://dl.dropboxusercontent.com/u/10824180/pebble%20config%20pages/sdktut9-config.html");
    
    Pebble.openURL("https://dl.dropboxusercontent.com/u/14899592/TrainTimeConfig.html");
    
  }
);

Pebble.addEventListener("webviewclosed",
  function(e) {
    //Get JSON dictionary
    var configuration = JSON.parse(decodeURIComponent(e.response));
    console.log("Configuration window returned: " + JSON.stringify(configuration));
    
    localStorage.setItem(keyHomeStation, configuration.homeStation);
    localStorage.setItem(keyWorkStation, configuration.workStation);
    
    homeStation = localStorage.getItem(keyHomeStation);
    workStation = localStorage.getItem(keyWorkStation);
    
    getTrainsBasedOnTime();
 /*
    //Send to Pebble, persist there
    Pebble.sendAppMessage(
      {"KEY_INVERT": configuration.invert},
      function(e) {
        console.log("Sending settings data...");
      },
      function(e) {
        console.log("Settings feedback failed!");
      }
    ); */
  }
);