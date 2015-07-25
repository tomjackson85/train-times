

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



// Listen for when the watchface is opened
Pebble.addEventListener('ready', 
  function(e) {
    console.log('PebbleKit JS ready!');
    
    var myDate = new Date();   
    if ( myDate.getHours() < 12 )  
    {   
      getTrains("WLI","LEW"); 
      //getTrains("TBW","LBG");   
    } 
    else {
      getTrains("LEW","WLI");
      //getTrains("LBG","TBW");
    }
       
    
    // Get the initial trains
    //getTrains("WLI","LEW");
  }
);

// Listen for when an AppMessage is received
Pebble.addEventListener('appmessage',
  function(e) {
    console.log('AppMessage received!');
    //getTrains("WLI","LEW");
    
    var myDate = new Date();   
    if ( myDate.getHours() < 12 )  
    {   
      getTrains("WLI","LEW"); 
      //getTrains("TBW","LBG");   
    } 
    else {
      getTrains("LEW","WLI");
      //getTrains("LBG","TBW");
    }
      
  }                     
);