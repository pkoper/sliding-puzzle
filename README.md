## Sliding Puzzle Game

[Sliding Puzzle](http://en.wikipedia.org/wiki/Sliding_puzzle) desktop game implemented in [C++11](http://www.stroustrup.com/C++11FAQ.html) using [SFML](http://www.sfml-dev.org/).

### Features
 1. Sliding tiles using mouse or <kbd>&larr;</kbd><kbd>&uarr;</kbd><kbd>&darr;</kbd><kbd>&rarr;</kbd>.
 2. Shuffling tiles <kbd>Space</kbd> or <kbd>R</kbd>.
 3. Solving puzzle <kbd>S</kbd> using [IDA*](http://en.wikipedia.org/wiki/IDA*) or playback (as a failback).
 4. Changing matrix size <kbd>J</kbd> / <kbd>K</kbd>.
 5. Changing image <kbd>I</kbd>.
 6. Fullscreen <kbd>F</kbd> or <kbd>F11</kbd>.

### Screenshot
![](https://raw.githubusercontent.com/pkoper/sliding-puzzle/master/doc/images/screenshot.png)

## Compiling
Download and unpack [SFML 2.2](http://www.sfml-dev.org/) library. Project files for [Code::Blocks](http://www.codeblocks.org/) and [JetBrains CLion](https://www.jetbrains.com/clion/) are included.

### JetBrains CLion (CMake)
Update the `SFML_ROOT` path in `CMakeLists.txt` file, eg:
```
set(SFML_ROOT "/Libraries/SFML-2.2")
```

### Code::Blocks
Use included project files or see [SFML and Code::Blocks (MinGW)](http://www.sfml-dev.org/tutorials/2.0/start-cb.php) tutorial.

#### Static Linking
To remove any runtime dependency you can statically link SFML (see examples below), or simply use included SlidingPuzzle.cbp project file and update SMFL paths.

![](https://raw.githubusercontent.com/pkoper/sliding-puzzle/master/doc/images/codeblocks-linker.png)

#### GUI Application
In the link step add a "-mwindows" switch to the command line to remove DOS command window or set the Type to GUI application.

![](https://raw.githubusercontent.com/pkoper/sliding-puzzle/master/doc/images/codeblocks-targets.png)

