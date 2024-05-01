# Cubic Hex
My implementation of the hexagonal grid library described in this excellent resource: <https://www.redblobgames.com/grids/hexagons/>

## Quick start
### Build the library - TODO
```bash
make lib
```
Will output `libhex.a` in the bin directory.

```bash
make dylib
```
Will output `libhex.so` in the bin directory.

### Use the library
Move the `libhex.a` or `libhex.so` to your project directory and include the header file `hex.h` in your source code.


## Tests
Build the tests:
```
./test.sh
```

Run the tests:
```
./tests/bin/test
```

