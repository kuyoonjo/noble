const { resolve } = require('path');
const p = require('../package.json');

module.exports = {
  target: 'node',
  externalsPresets: { node: true },
  entry: {
    linux: ['./src/linux.js'],
  },
  devtool: false,
  mode: 'production',
  module: {},
  resolve: {
    extensions: ['.json', '.js'],
    plugins: [],
    alias: {
      '@abandonware/bluetooth-hci-socket': resolve(__dirname, '../build/noble/bluetooth-hci-socket'),
    },
  },
  output: {
    library: p.name,
    libraryTarget: 'umd',
    filename: '[name].js',
    path: resolve('build', 'noble'),
  },
  externals: {
    './noble': './noble',
  },
};