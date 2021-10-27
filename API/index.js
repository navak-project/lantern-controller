const mqtt = require('mqtt')
const osc = require('node-osc');

const host = '192.168.1.13'
const port = '1883'
const clientId = `mqtt_${Math.random().toString(16).slice(3)}`

const connectUrl = `mqtt://${host}:${port}`
const client = mqtt.connect(connectUrl, {
  clientId,
  clean: true,
  connectTimeout: 4000,
  username: 'emqx',
  password: 'public',
  reconnectPeriod: 1000,
})

// MQTT
const topic = 'dwm/node/0b85/uplink/location'
const scanTopics = '#'

// OSC
const oscClient = new osc.Client('127.0.0.1', 3333);
var topics = [];

var tags = [];

client.on('connect', () => {
  console.log('Connected')
//   client.subscribe(topic, () => {
//     console.log(`Subscribe to topic '${topic}'`)
//   })

    // Get all topics
    client.subscribe(scanTopics,() => {
        console.log('Scanning for topics!');
        client.unsubscribe(scanTopics, () => {
            console.log('Got all topics.')
        })
    })
})

client.on('message', (topic, message) => {
    var obj = JSON.parse(message);

    // console.log(obj);
    // oscClient.send('/0b85/posX', obj.position.x);
    // oscClient.send('/0b85/posY', obj.position.y);

    console.log(topic);
    console.log(obj);
    // topics.push(topic);
    // topics.push(obj);
    
    

    if(obj.configuration != null){
        topics.push(obj);
        if(obj.configuration.nodeType == 'ANCHOR'){
            // console.log(obj.configuration.label);
            // console.log(obj.configuration.anchor.position);
            SendAnchorData(obj.configuration.label, obj.configuration.anchor.position);
        } else if(obj.configuration.nodeType == 'TAG'){
            SendTagData(obj.configuration.label, topic.substring(9,13));
        }
    }
})

function SendAnchorData(name, data){
    // console.log(name, data);
    // BUNDLE DATA TOGETHER
    oscClient.send(`/anchorData/${name}/posX`, data.x);
    oscClient.send(`/anchorData/${name}/posY`, data.y);
    oscClient.send(`/anchorData/${name}/posZ`, data.z);
}

function SendTagData(name, data){
    oscClient.send(`/tagData/${name}/id`, data);
}