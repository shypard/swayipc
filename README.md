# swayipc

A pure c99 helper library for interacting with the `sway` window manager via
IPC.

## Building and Installing

`swayipc` can be build via the Meson build system. The needed dependencies can
be installed (on Red Hat based distros) as follows:

```bash
sudo dnf -y install meson                       # install build tools
sudo dnf -y install libcmocka-devel cjson-devel # install external libraries
```

To build and install the library, run the following commands:

```bash
meson setup build
meson compile -C build
sudo meson install -C build
```

This will build the library and install it to the default location
(`/usr/local/lib64`) along with the header files (`/usr/local/include`).

The Unit tests are written with the `cmocka` library, run them as follows:

```bash
meson setup build
meson test -C build
```

## Contributing

If you would like to contribute to `swayipc`, please fork the repository and
submit a pull request. If you find any bugs, please submit an issue. Please
add a unit test for any new features you add, make sure to run the unit tests
with `meson setup build && meson test -C build` and stay to the coding style of
the project (use `clang-format`).

The following Todos are left for implementation:

- Implement the following commands:
    - send_tick
- Add github pipeline for building and testing
