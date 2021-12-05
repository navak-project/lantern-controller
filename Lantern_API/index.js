const express = require("express");
const cors = require("cors");
var ping  = require("net-ping");
var piing = require("ping");

// const db = require("../models");
// const Lantern = db.lanterns;

const app = express();

var corsOptions = {
  origin: "http://localhost:8081"
};

// Used to ping device to determine state of life
var session = ping.createSession();

app.use(cors(corsOptions));

// parse requests of content-type - application/json
app.use(express.json());

// parse requests of content-type - application/x-www-form-urlencoded
app.use(express.urlencoded({ extended: true }));

const db = require("./app/models");
const lanternRoutes = require("./app/routes/lantern.routes");
db.mongoose
  .connect(db.url, {
    useNewUrlParser: true,
    useUnifiedTopology: true
  })
  .then(() => {
    console.log("Connected to the database!");
  })
  .catch(err => {
    console.log("Cannot connect to the database!", err);
    process.exit();
  });

// simple route
app.get("/", (req, res) => {
  res.json({ message: "Welcome to wd application." });
});
var ips = ["192.168.1.10", "192.168.1.12", "192.168.1.13","192.168.1.11"]

// set port, listen for requests
const PORT = process.env.PORT || 8080;
require("./app/routes/lantern.routes")(app);
app.listen(PORT, () => {
  console.log(`Server is running on port ${PORT}.`);
  GetAllActive();
  const pingInterval = setInterval(() => {
    GetAllActive();
  }, 5000);

});


async function GetAllActive() {
  var query = {status : true};
    try {
        const allActive = await db.lanterns.find(query);
        // console.log("ALL ACTIVE:")
        allActive.forEach(lantern => {
          session.pingHost(lantern['ipAddress'], (error, target) => {
            if(error){
              UpdateState(target);
            }
          });
        });
    } catch (error) {
        console.error(error);
    }
}

async function UpdateState(ipAddress) {
  var query = {ipAddress: ipAddress};
  var newValues = {status: false};
  const target = await db.lanterns.findOneAndUpdate(query, newValues);
  console.log(`Lantern [ID: ${target.id} | IP: ${target.ipAddress} | MAC: ${target.macAddress}] is Offline!`);
}