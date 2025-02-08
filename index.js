const native = require("./build/Release/hmoog-native.node");

module.exports = {
    init: native.init,
    sendKeystrokes: native.sendKeystrokes,
    sendMouseClick: native.sendMouseClick,
};
