# Contributing

## How to contribute

Everyone is welcome to contribute to the project. If you want to contribute, please follow these guidelines:

- [Fork the repository](https://help.github.com/articles/fork-a-repo/)
- When you are done, [create a pull request](https://help.github.com/articles/creating-a-pull-request/) on
  branch `develop`:
    - Add a full description of your changes in the pull request comment.
- If you want to add a new algorithm :
    - Please write it in a `.hpp` file in `src/algorithm/algos`.
    - Add this file in `CMakeLists.txt` sorted by name.
    - If you need several file, create a folder with the name of the algorithm in the same directory.
    - Then include your `.hpp` file in `src/algorithm/algorithms.hpp` with the other algorithms, please sort the
      includes. And add your algorithm in the `algorithms` list, same as usual, sort it by name.