// Create a client instance
client = new Paho.MQTT.Client("192.168.0.105", 9001, "CatBenderson");

// set callback handlers
client.onConnectionLost = onConnectionLost;
client.onMessageArrived = onMessageArrived;

// connect the client
client.connect({ onSuccess: onConnect });

var map = L.map('map').setView([19.546440, -96.904226], 13);
L.tileLayer('https://tile.openstreetmap.org/{z}/{x}/{y}.png', { maxZoom: 19, attribution: '&copy; <a href="http://www.openstreetmap.org/copyright">OpenStreetMap</a>' }).addTo(map);

// var markerLayer = L.layerGroup();
var puntito = new L.Marker([0, 0]).addTo(map);

function agregarPopUP() {
    var cord1 = document.getElementById("co1").value
    var cord2 = document.getElementById("co2").value
    var text = document.getElementById("txt").value
    var a = document.getElementById("a")

    puntito.setLatLng(L.latLng(cord1, cord2))
    puntito.bindPopup("<b>" + text + "</b>").openPopup();
};

// var popup = L.popup();
// function onMapClick(e) {
//     popup
//         .setLatLng(e.latlng)
//         .setContent("Coordenadas: " + e.latlng.toString())
//         .openOn(map);
// }

// map.on('click', onMapClick);


// called when the client connects
function onConnect() {
    // Once a connection has been made, make a subscription and send a message.
    console.log("onConnect");
    client.subscribe("/temperaturaA");
    message = new Paho.MQTT.Message("Hello");
    message.destinationName = "World";
    //client.send(message);
}

// called when the client loses its connection
function onConnectionLost(responseObject) {
    if (responseObject.errorCode !== 0) {
        console.log("onConnectionLost:" + responseObject.errorMessage);
    }
}

// called when a message arrives
function onMessageArrived(message) {
    var mensajeJson = JSON.parse(message.payloadString);
    puntito.setLatLng(L.latLng(mensajeJson.c1, mensajeJson.c2))
    puntito.bindPopup("<b> Temperatura: " + mensajeJson.temperatura + "</b>").openPopup();

}

function sendMessage() {
    client.subscribe("World");
    message = new Paho.MQTT.Message(`${client} ${document.getElementById("mensaje").value}`);
    message.destinationName = "World";
    client.send(message);

    document.getElementById("mensaje").value = "";
}