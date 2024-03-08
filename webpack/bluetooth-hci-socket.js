const { resolve } = require('path');
const p = require('../package.json');

module.exports = {
  target: 'node',
  externalsPresets: { node: true },
  entry: {
    'bluetooth-hci-socket': ['./node-bluetooth-hci-socket/lib/native.js'],
  },
  devtool: false,
  mode: 'production',
  module: {},
  resolve: {
    extensions: ['.json', '.js'],
    plugins: [],
  },
  output: {
    library: p.name,
    libraryTarget: 'umd',
    filename: '[name].js',
    path: resolve('build', 'noble'),
  },
  externals: {
    '../build/Release/bluetooth_hci_socket.node': './noble',
  },
};