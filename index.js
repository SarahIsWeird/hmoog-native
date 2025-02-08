const native = require("./build/Release/hmoog-native.node");

module.exports = {
    init: native.init,
    getInfo: native.getInfo,
    sendKeystrokes: native.sendKeystrokes,
    sendMouseClick: native.sendMouseClick,
};
