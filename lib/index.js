import { createRequire } from 'node:module';
const require = createRequire(import.meta.url);
const native = require('../build/Release/hmoog-native.node');

export const init = native.init;
export const getInfo = native.getInfo;
export const sendKeystrokes = native.sendKeystrokes;
export const sendMouseClick = native.sendMouseClick;
