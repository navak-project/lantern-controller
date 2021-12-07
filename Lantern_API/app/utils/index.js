const oscClient = require("node-osc");
const client = new oscClient.Client('127.0.0.1', 3333);

const delay = ms => new Promise(resolve => setTimeout(resolve, ms));

async function pulseOSC(){
    await client.send('/dbUpdate', 1);
    await delay(100)
    await client.send('/dbUpdate', 0);
  }

exports.pulseOSC = pulseOSC;