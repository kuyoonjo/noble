const { EventEmitter } = require('events');
const { inherits } = require('util');
const { NobleWinrt } = require('./noble');

inherits(NobleWinrt, EventEmitter);
const Noble = require('../unix/lib/noble');
const bindings = new NobleWinrt();
module.exports = new Noble(bindings);
