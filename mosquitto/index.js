// Create a client instance
client = new Paho.MQTT.Client("192.168.246.77", 9001, "CatBenderson");

// set callback handlers
client.onConnectionLost = onConnectionLost;
client.onMessageArrived = onMessageArrived;

// connect the client
client.connect({onSuccess:onConnect});


// called when the client connects
function onConnect() {
  // Once a connection has been made, make a subscription and send a message.
  console.log("onConnect");
  client.subscribe("World");
  message = new Paho.MQTT.Message("Hello");
  message.destinationName = "World";
  //client.send(message);
}

// called when the client loses its connection
function onConnectionLost(responseObject) {
  if (responseObject.errorCode !== 0) {
    console.log("onConnectionLost:"+responseObject.errorMessage);
  }
}

// called when a message arrives
function onMessageArrived(message) {
  var div = document.getElementById("chat");
  div.innerHTML = div.innerHTML + `<p>${message.payloadString}</p>`;
  //console.log("onMessageArrived:"+message.payloadString);
}

function sendMessage() {
  client.subscribe("World");
  message = new Paho.MQTT.Message(`${client.} ${document.getElementById("mensaje").value}`);
  message.destinationName = "World";
  client.send(message);

  document.getElementById("mensaje").value=""; 
}