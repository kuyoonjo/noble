const Noble = require('./unix/lib/noble');
const { EventEmitter } = require('events');
const { inherits } = require('util');
const isElectron = require('is-electron');

const type = isElectron() ? 'electron' : 'node';

switch (process.platform) {
  case 'darwin':
    const NobleMac = require(`./build/${process.platform}/${type}/${process.arch}/binding`).NobleMac;
    inherits(NobleMac, EventEmitter);
    module.exports = new Noble(new NobleMac());
    break;
  case 'win32':
    const NobleWinrt = require(`./build/${process.platform}/${type}/${process.arch}/binding`).NobleWinrt;
    inherits(NobleWinrt, EventEmitter);
    module.exports = new Noble(new NobleWinrt());
    break;
}