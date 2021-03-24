switch (process.platform) {
  case 'darwin':
    const events = require('events');
    const util = require('util');
    const NobleMac = require(`./build/${process.platform}/${process.arch}/binding`).NobleMac;
    util.inherits(NobleMac, events.EventEmitter);
    const Noble = require('./unix/lib/noble');
    module.exports = new Noble(new NobleMac());
}