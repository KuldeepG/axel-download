##axel-download

Node bindings for Axel (A lighter download accelerator for Linux and other Unices.)

###Setup

Compile the code to get the node module

With npm
```
npm install
```
With node-gyp:
```
node-gyp configure build
```

###Example Usage

After compilation the node module will be in build/Release folder.

```
var axel = require('./build/Release/axelBinding')

axel.download(URL_TO_DOWNLOAD)
```
