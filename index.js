const Noble = require('./unix/lib/noble');
const { EventEmitter } = require('events');
const { inherits } = require('util');

switch (process.platform) {
  case 'darwin':
    const NobleMac = require(`./build/${process.platform}/${process.arch}/binding`).NobleMac;
    inherits(NobleMac, EventEmitter);
    module.exports = new Noble(new NobleMac());
  case 'win32':
    const NobleWinrt = require(`./build/${process.platform}/${process.arch}/binding`).NobleWinrt;
    inherits(NobleWinrt, EventEmitter);
    module.exports = new Noble(new NobleWinrt());
}