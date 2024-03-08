const Noble = require('../unix/lib/noble');
const bindings = new (require('../unix/lib/hci-socket/bindings'))({});
module.exports = new Noble(bindings);
