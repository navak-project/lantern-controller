module.exports = mongoose => {
    const Lantern = mongoose.model(
      "lantern",
      mongoose.Schema({
        id: {
            type: String,
            required: false,
            default: "0000"
        },
        hostName: {
            type: String,
            required: true
        },
        macAddress: {
            type: String,
            required: true
        },
        ipAddress: {
            type: String,
            required: true,
        },
        startUniverse: {
            type: Number,
            required: false,
            default: 0
        },
        cardID:{
            type: String,
            required: false,
            default: "00000000"
        },
        status:{
            type: Boolean,
            required: false,
            default: false
        }
      })
    );
    return Lantern;
  };