module.exports = app => {
    const lanterns = require("../controllers/lantern.controller.js");
  
    var router = require("express").Router();
  
    // Create a new Lantern
    router.post("/register", lanterns.create);
  
    // Retrieve all Lanterns
    router.get("/", lanterns.findAll);
  
    // // Retrieve a single User with id
    // router.get("/:id", lanterns.findOne);
  
    // // Update a User with id
    // router.put("/:id", lanterns.update);
  
    // // Delete a User with id
    // router.delete("/:id", lanterns.delete);
  
    // // Create a new User
    // router.delete("/", lanterns.deleteAll);
  
    app.use('/api/lanterns', router);
  };