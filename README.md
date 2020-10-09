# memtest - An ANSI C Conformant memtest Library.

memtest is a small memory test library made for embedded systems. It
provides functions to test the data bus, the address bus as well as the
whole memory device.

The source code is heavily based on Michael Barrs code published
[here](https://barrgroup.com/embedded-systems/how-to/memory-test-suite-c).
So most of the credits go there.

## License
Copyright (c) 2020 Stephan Gatzka. See the [LICENSE](LICENSE) file for license rights and
limitations (MIT).

## Howto Build
memtest lets you choose if you want to build a static or dynamic library.
The default is static. If you want a shared library, execute:
```
cmake -DBUILD_SHARED_LIBS=ON <path-to-memtest-project>
```

