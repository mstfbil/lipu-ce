# lipu CE

**lipu CE** is a [toki pona](https://en.wikipedia.org/wiki/Toki_Pona) dictionary for the TI-84 Plus CE calculator.

[lipu CE on Cemetech](https://www.cemetech.net/downloads/files/3103/x4221)

## Usage

Pretty simple. You can scroll through the word list with `up` and `down` arrow buttons, and see the details with `enter`. You can scroll in the word overview as well. Press `mode` in word list to see credits.

## Building

The repo uses python scripts to build the dictionary database and sitelen pona glyphs. To build, `python3` must be in PATH.
CEdev toolchain must be installed; refer to [CE installation guide](https://ce-programming.github.io/toolchain/static/getting-started.html) for details.

```bash
git clone --recurse-submodules https://github.com/mstfbil/lipu-ce.git && cd lipu-ce
pip3 install -r requirements.txt
make
```

You can make `core`, `core-common`, `core-uncommon` or `core-obscure` to build that variant. Each has their respective range of words included.

## Contributors

- [@mstfbil](https://github.com/mstfbil) voltie_dev
- [@Mirka1405](https://github.com/Mirka1405) jan Milon

##  License

This project is licensed under the MIT License.
Dictionary data is sourced from [lipu-linku/sona](https://github.com/lipu-linku/sona) and licensed under [CC-BY-SA-4.0 license](https://github.com/lipu-linku/sona/blob/main/LICENSE).
Fairfax font is licensed under SIL Open Font License 1.1.
