const os = require('os');

const m = os.platform() === 'win32' ? 'noble-winrt' : 'noble-unix';
module.exports = require(m);