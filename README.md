# Read arrow keys from a POSIX terminal in C++

The answer to the questions:

> "How do I read individual key presses in the terminal using C++ without needing ncurses?"

> "How do I read arrow keys in C++?"

## Usage

### Copy these files

Put the files `TerminalController.h` and `TerminalController.c++` with your other C++ code.

### Compile this code

Compile `TerminalController.c++` into `TerminalController.o`:

```bash
g++ -c TerminalController.c++
```

### Use this code

In your own C++ code, include this header:

```c++
#include "TerminalController.h"
```

In your own C++ code, run this function:

```c++
TTY::recognizeIndividualKeyPresses(true);
```

### What now?

After you run `TTY::recognizeIndividualKeyPresses(true)`, the following code will just work without having to press Enter:

```c++

  std::cerr << "Enter a single character, but do not press Enter: ";

  std::cin >> c;

  std::cout << "You pressed the character with underlying representation " << int{c} << "\n";  
```
