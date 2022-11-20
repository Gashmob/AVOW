# Changelog

## 0.2.0

- `Blank` generate a blank image (transparent), not white
- Add some algorithm :
    - `Random`
    - `Color`
- Executable use a config file instead of command line arguments
- The config file can be generated with `-g [file]`
- Can obtain list and description of algorithm with `-l` and `-d`

## 0.1.0

*2022-11-10*

- Add abstract class `Algorithm` to define several algorithms.
- Add a first algorithm `Blank` which generate a white image.
- Add basic main with options for input, output and algorithms selection.