const { cpSync } = require('fs');
const { join } = require('path');

const filename = 'noble.node';
const source = (() => {
  switch (process.platform) {
    case 'win32':
      return join(__dirname, 'build', 'noble', 'x86_64-pc-windows-msvc', filename);
    case 'darwin':
      if (process.arch === 'arm64')
        return join(__dirname, 'build', 'noble', 'aarch64-apple-darwin', filename);
      return join(__dirname, 'build', 'noble', 'x86_64-apple-darwin', filename);
    case 'linux':
      if (process.arch === 'arm')
        return join(__dirname, 'build', 'noble', 'arm-linux-gnueabihf', filename);
      if (process.arch === 'arm64')
        return join(__dirname, 'build', 'noble', 'aarch64-linux-gnu', filename);
      return join(__dirname, 'build', 'noble', 'x86_64-linux-gnu', filename);
  }
})();

if (source) {
  const dist = join(__dirname, 'build', 'noble', filename);
  cpSync(source, dist);
} else {
  console.warn('Unsupported platform:', process.platform, process.arch);
}
