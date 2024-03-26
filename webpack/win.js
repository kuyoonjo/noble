const { resolve } = require('path');
const p = require('../package.json');

module.exports = {
  target: 'node',
  externalsPresets: { node: true },
  entry: {
    win32: ['./src/win.js'],
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
    './noble': './noble.node',
  },
};