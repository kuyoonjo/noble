const os = require('os');

const m = os.platform() === 'win32' ? '@kuyoonjo/noble-winrt' : '@kuyoonjo/noble-unix';
module.exports = require(m);