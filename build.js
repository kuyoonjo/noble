const { execSync, spawnSync } = require('child_process');

function darwin() {
  execSync('rm -rf unix/prebuilds');
  execSync('prebuild -t 15.11.0 -r node -p unix', { stdio: 'inherit' });
  execSync(`mkdir -p build/darwin/${process.arch}`);
  execSync(`mv unix/lib/mac/native/binding.node build/darwin/${process.arch}`);
}

function win32() {
  spawnSync(process.env.comspec, ['/c', 'rmdir', '/s', '/q', 'winrt\\prebuilds'], { stdio: 'inherit' });
  execSync('prebuild -t 15.11.0 -r node -p winrt', { stdio: 'inherit' });
  spawnSync(process.env.comspec, ['/c', 'mkdir', `build\\win32\\${process.arch}`]);
  spawnSync(process.env.comspec, ['/c', 'move', 'winrt\\build\\Release\\noble_winrt.node', `build\\win32\\${process.arch}\\binding.node`]);
}

if (process.platform === 'darwin')
  darwin();
else if (process.platform === 'win32')
  win32();