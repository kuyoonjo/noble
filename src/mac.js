const { EventEmitter } = require('events');
const { inherits } = require('util');
const { NobleMac } = require('./noble');

inherits(NobleMac, EventEmitter);
const Noble = require('../unix/lib/noble');
const bindings = new NobleMac();
module.exports = new Noble(bindings);
