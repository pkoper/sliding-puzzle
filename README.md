## Sliding Puzzle Game (SFML/C++11)

[Sliding Puzzle](http://en.wikipedia.org/wiki/Sliding_puzzle) desktop game implemented in C++ using [SFML](http://www.sfml-dev.org/).

### Features
 1. Sliding tiles using mouse or keyboard arrows.
 2. Shuffling tiles <kbd>Space</kbd> or <kbd>R</kbd>.
 3. Solving puzzle <kbd>S</kbd> using [IDA*](http://en.wikipedia.org/wiki/IDA*) or playback (as a failback).
 4. Changing matrix size <kbd>J</kbd> / <kbd>K</kbd>.
 5. Changing image <kbd>I</kbd>.
 6. Fullscreen <kbd>F</kbd> or <kbd>F11</kbd>.

### Screenshot
![](https://raw.githubusercontent.com/pkoper/sliding-puzzle/master/doc/images/screenshot.png)

## Compiling
Download and unpack [SFML 2.2](http://www.sfml-dev.org/) library. Project files for [Code::Blocks](http://www.codeblocks.org/) and [JetBrains CLion](https://www.jetbrains.com/clion/) are included.

### Code::Blocks
Use included project files or see [SFML and Code::Blocks (MinGW)](http://www.sfml-dev.org/tutorials/2.0/start-cb.php) tutorial.

#### Static Linking
To remove any runtime dependency you can statically link SFML (see examples below), or simply use included SlidingPuzzle.cbp project file and update SMFL paths.

![](https://raw.githubusercontent.com/pkoper/sliding-puzzle/master/doc/images/codeblocks-linker.png)

#### GUI Application
In the link step add a "-mwindows" switch to the command line to remove DOS command window or set the Type to GUI application.

![](https://raw.githubusercontent.com/pkoper/sliding-puzzle/master/doc/images/codeblocks-target.png)

### JetBrains CLion
Update the SFML_ROOT in `CMakeLists.txt` file, eg:

```
set(SFML_ROOT "/Libraries/SFML-2.2")
```
