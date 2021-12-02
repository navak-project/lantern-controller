const db = require("../models");
const Lantern = db.lanterns;

// Create and Save a new user
exports.create = async (req, res) => {
    // Validate request
    if (!req.body) {
        res.status(400).send({ message: "Content can not be empty!" });
        return;
    }

    try {
        const element = await Lantern.findOne({ macAddress: req.body.macAddress });
        // console.log(test);
        if (element != null) {
            console.log("Exists!")
            res.send(element);
        } else {
            const lantern = new Lantern({
                hostName: req.body.hostName,
                macAddress: req.body.macAddress,
                ipAddress: req.body.ipAddress,
            });

            await lantern.save(lantern);
            res.send(lantern);
            console.log("CREATED LANTERN");
        }

    } catch (error) {
        console.error(error);
        res.status(500).send({
            message: error
        });
    }
};

// Retrieve all Lanterns from the database.
exports.findAll = async (req, res) => {
    const title = req.query.title;
    var condition = title ? { title: { $regex: new RegExp(title), $options: "i" } } : {};
    try {
        const data = await Lantern.find(condition);
        res.send(data);
    } catch (error) {
        res.status(500).send({
            message: error
        });
    }
};

exports.findActive = async (req, res) => {
    var query = {status : true};
    try {
        const allActive = await Lantern.find(query);
        console.log(allActive);
        res.send(allActive);
    } catch (error) {
        console.error(error);
        res.status(500).send({
            message: error
        });
    }
};

  // Find a single User with an id
//   exports.findOne = async (req, res) => {
//     const id = req.params.id;
//     try {
//       const user = await Lantern.findById(id);
//       client.send('/base_data,', JSON.stringify(user), (err) =>{
//         if(err) console.log(err);
//       })
//       res.send(user);
//     } catch (error) {
//       res.status(500).send({
//         message: error
//       });
//     }
//   };

//   // Update a User by the id in the request
//   exports.update = async (req, res) => {
//     console.log('req', req.body);
//     if (!req.body) {
//       return res.status(400).send({
//         message: "Data to update can not be empty!"
//       });
//     }
//     const id = req.params.id;
//     try {
//       await User.findByIdAndUpdate(id, req.body, { useFindAndModify: false })
//         res.send(`User ${id} updated successful!`);
//     } catch (error) {
//       console.log('error', error);
//       res.status(500).send({
//         message: error
//       });
//     }
//   };

//   // Delete a User with the specified id in the request
//   exports.delete = async (req, res) => {
//     const id = req.params.id;
//     try {
//       await User.findByIdAndRemove(id)
//         res.send(`User ${id} deleted successful!`);
//     } catch (error) {
//       console.log('error', error);
//       res.status(500).send({
//         message: error
//       });
//     }
//   };

//   // Delete all Users from the database.
//   exports.deleteAll = async (req, res) => {
//     try {
//       await User.deleteMany({})
//         res.send(`Database deleted successful!`);
//     } catch (error) {
//       console.log('error', error);
//       res.status(500).send({
//         message: error
//       });
//     }
//   };