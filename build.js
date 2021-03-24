const { execSync } = require('child_process');

function darwin() {
  execSync('rm -rf unix/prebuilds');
  execSync('prebuild -t 15.11.0 -r node -p unix', { stdio: 'inherit' });
  execSync(`mkdir -p build/darwin/${process.arch}`);
  execSync(`mv unix/lib/mac/native/binding.node build/darwin/${process.arch}`);
}

if (process.platform === 'darwin')
  darwin();