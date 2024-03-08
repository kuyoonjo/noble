const { LLVM } = require('@smake/llvm');
const { NodeAddon } = require('@smake/node-addon');
const { vscode } = require('@smake/llvm-vscode');
const { LibBuffer } = require('@smake/buffer');
const { Shell, Fn } = require('@smake/utils');
const { mkdir, cp } = require('fs/promises');

const package = require('./package.json');
const { basename } = require('path');
const NODE_VERSION = 'v' + package.nodeVersion;

const targets = [
  'aarch64-apple-darwin',
];

const libs = targets.map(target => {
  const lib = new LLVM('cble', target);
  lib.type = 'static';
  lib.files = [
    'cble/src/macos/cble.m',
  ];
  lib.includedirs = [
    ...lib.includedirs,
    'cble/include',
  ];
  lib.cxflags = [
    ...lib.cxflags,
    '-fobjc-arc',
  ];
  LibBuffer.config(lib);
  vscode(lib);

  const test = new LLVM('cble-test', target);
  test.files = ['cble/src/test.c'];
  test.libs = [
    ...test.libs,
    lib,
  ];
  test.includedirs = [
    ...test.includedirs,
    'cble/include',
  ];
  test.ldflags = [
    ...test.ldflags,
    '-fobjc-arc -framework Foundation -framework CoreBluetooth',
  ];
  test.cxflags = [
    ...test.cxflags,
    '-fobjc-arc',
  ];
  vscode(test);
  return { name: target, targets: [lib, test] };
});

const commonJsFiles = [
  ...[
    'characteristic.js',
    'service.js',
    'characteristics.json',
    'peripheral.js',
    'services.json',
    'descriptor.js',
    'descriptors.json',
    'noble.js',
  ].map(n => [`./unix/lib/` + n, n]),
  ['./unix/index.d.ts', 'index.d.ts'],
];

const nobleMacNode = [
  'aarch64-apple-darwin',
  'x86_64-apple-darwin',
].map(target => {
  const lib = new NodeAddon('noble', target);
  lib.NODE_VERSION = NODE_VERSION;
  lib.files = [
    'unix/lib/mac/src/noble_mac.mm',
    'unix/lib/mac/src/napi_objc.mm',
    'unix/lib/mac/src/ble_manager.mm',
    'unix/lib/mac/src/objc_cpp.mm',
    'unix/lib/mac/src/callbacks.cc',
  ];
  lib.cxflags = [
    ...lib.cxflags,
    '-fobjc-arc',
  ];
  lib.shflags = [
    ...lib.shflags,
    '-fobjc-arc -framework CoreBluetooth',
  ];
  lib.outputDir = `./build/noble/${target}`;
  return lib;
});
const nobleMacJs = new Shell(`noble-mac-js`, 'npx',
  'webpack --config webpack/mac.js'.split(' '),
);
const nobleMac = {
  name: 'mac',
  targets: [
    ...nobleMacNode,
    nobleMacJs,
  ],
};

const nobleWinNode = [
  new Shell('noble-x86_64-pc-windows-msvc-download', 'wget', [
    'https://github.com/kuyoonjo/noble-winrt/releases/download/v0.1.3/noble-winrt-v0.1.3-napi-v6-win32-x64.tar.gz',
    '-P', './download'
  ]),
  new Shell('noble-x86_64-pc-windows-msvc-extract', 'tar', [
    '-xf', './download/noble-winrt-v0.1.3-napi-v6-win32-x64.tar.gz'
  ]),
  new Shell('noble-x86_64-pc-windows-msvc-mkdir', 'mkdir', [
    '-p', './build/noble/x86_64-pc-windows-msvc'
  ]),
  new Shell('noble-x86_64-pc-windows-msvc-move', 'mv', [
    './build/Release/noble_winrt.node', './build/noble/x86_64-pc-windows-msvc/noble.node'
  ]),
]
const nobleWinJs = new Shell(`noble-win-js`, 'npx',
  'webpack --config webpack/win.js'.split(' '),
);
const nobleWin = {
  name: 'win',
  targets: [
    ...nobleWinNode,
    nobleWinJs,
  ],
};

const nobleLinuxNode = [
  'x86_64-linux-gnu',
  'aarch64-linux-gnu',
  'arm-linux-gnueabihf',
].map(target => {
  const lib = new NodeAddon('noble', target);
  lib.NODE_VERSION = NODE_VERSION;
  lib.files = [
    'node-bluetooth-hci-socket/src/BluetoothHciSocket.cpp',
  ];

  lib.shflags = [
    ...lib.shflags,
    '-static-libstdc++',
  ];
  lib.outputDir = `./build/noble/${target}`;
  return lib;
});
const nobleLinuxJs = [
  new Shell(`noble-linux-js-bluetooth-hci-socket`, 'npx',
    'webpack --config webpack/bluetooth-hci-socket.js'.split(' '),
  ),
  new Shell(`noble-linux-js-main`, 'npx',
    'webpack --config webpack/linux.js'.split(' '),
  ),
  new Shell(`noble-linux-js-clear`, 'rm',
    '-f ./build/noble/bluetooth-hci-socket.js'.split(' '),
  ),
];

const nobleLinux = {
  name: 'linux',
  targets: [
    ...nobleLinuxNode,
    ...nobleLinuxJs,
  ],
};

const builds = [
  {
    name: 'napi',
    targets: [
      nobleMac,
      nobleWin,
      nobleLinux,
    ],
  },
];

module.exports = builds;