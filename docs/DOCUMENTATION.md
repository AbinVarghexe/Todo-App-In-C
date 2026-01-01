# 📚 Documentation

Complete technical documentation for Todo App.

## Table of Contents

- [Architecture](#architecture)
- [Project Structure](#project-structure)
- [Technical Stack](#technical-stack)
- [Building from Source](#building-from-source)
- [API Reference](#api-reference)
- [Development Guide](#development-guide)
- [Contributing](#contributing)
- [Troubleshooting](#troubleshooting)

## Architecture

### Overview

Todo App is built using a modular architecture that separates UI rendering from business logic:

```
┌─────────────────┐
│   UI Layer      │  (OpenGL + Leif Framework)
│   todo.c        │
└────────┬────────┘
         │
┌────────▼────────┐
│  Logic Layer    │  (Core Task Management)
│  logic/logic.c  │
└─────────────────┘
```

### Design Principles

1. **Separation of Concerns** - UI and logic are decoupled
2. **Performance First** - C language for maximum speed
3. **Minimal Dependencies** - Only essential libraries
4. **Linux Native** - Optimized for Linux ecosystem

## Project Structure

```
Todo-App-In-C/
├── Readme.md              # Project overview
├── todo.c                 # Main application file
├── todo                   # Compiled binary
├── install.sh             # Automated installation script
│
├── docs/                  # Documentation
│   ├── DOCUMENTATION.md   # This file
│   ├── QUICKSTART.md      # Getting started guide
│   └── FEATURES.md        # Feature documentation
│
├── logic/                 # Business logic module
│   └── logic.c            # Core task management logic
│
├── fonts/                 # Custom font files
├── icons/                 # Application icons
├── images/                # Screenshots and assets
│
└── release/               # Release builds
    └── Todo-App/
        ├── todo           # Compiled binary
        ├── install.sh     # Installation script
        ├── Readme.md      # Release notes
        ├── fonts/         # Bundled fonts
        └── icons/         # Bundled icons
```

## Technical Stack

### Core Technologies

| Component | Technology | Version | Purpose |
|-----------|-----------|---------|---------|
| Language | C | C99+ | Core application |
| Graphics | OpenGL | 3.3+ | Rendering |
| Windowing | GLFW | 3.3+ | Window management |
| UI Framework | Leif | Latest | User interface |
| Protocol | X11/XCB | - | Linux integration |

### Libraries & Dependencies

**Required Libraries:**
```c
#include <GLFW/glfw3.h>    // Window & input handling
#include <GL/gl.h>         // OpenGL graphics
#include <leif/leif.h>     // UI framework
#include <clipboard.h>     // Clipboard support
#include <math.h>          // Math operations
#include <xcb/xcb.h>       // X11 protocol
```

**Installation via Package Manager:**

```bash
# Debian/Ubuntu
sudo apt-get install libglfw3-dev libgl1-mesa-dev libxcb1-dev

# Fedora
sudo dnf install glfw-devel mesa-libGL-devel libxcb-devel

# Arch Linux
sudo pacman -S glfw-ogl mesa libxcb
```

## Building from Source

### Standard Build

Using the provided Makefile:

```bash
make          # Build the application
make clean    # Clean build artifacts
make install  # Install systemwide (requires sudo)
```

### Manual Compilation

Full compilation command with all flags:

```bash
gcc -o todo todo.c \
    -lglfw \       # GLFW library
    -lGL \         # OpenGL library
    -lleif \       # Leif UI framework
    -lclipboard \  # Clipboard functionality
    -lm \          # Math library
    -lxcb          # X protocol library
```

### Build Options

**Debug Build:**
```bash
gcc -g -O0 -o todo todo.c -lglfw -lGL -lleif -lclipboard -lm -lxcb
```

**Release Build (Optimized):**
```bash
gcc -O3 -march=native -o todo todo.c -lglfw -lGL -lleif -lclipboard -lm -lxcb
```

**With Warnings:**
```bash
gcc -Wall -Wextra -o todo todo.c -lglfw -lGL -lleif -lclipboard -lm -lxcb
```

## API Reference

### Data Structures

```c
// Task node in linked list
typedef struct Task {
    char description[256];
    bool completed;
    struct Task* next;
} Task;

// Application state
typedef struct AppState {
    Task* head;
    int taskCount;
    FilterMode currentFilter;
} AppState;
```

### Core Functions

**Task Management:**
```c
Task* createTask(const char* description);
void addTask(AppState* state, const char* description);
void deleteTask(AppState* state, Task* task);
void toggleTaskComplete(Task* task);
```

**Filtering:**
```c
void setFilter(AppState* state, FilterMode mode);
Task* getFilteredTasks(AppState* state);
```

**UI Rendering:**
```c
void renderTaskList(AppState* state);
void renderAddButton(void);
void renderFilterButtons(AppState* state);
```

## Development Guide

### Setting Up Development Environment

1. **Install Development Tools:**
```bash
sudo apt-get install build-essential git gdb valgrind
```

2. **Clone Repository:**
```bash
git clone https://github.com/AbinVarghexe/Todo-App-In-C.git
cd Todo-App-In-C
```

3. **Install Dependencies:**
```bash
# Install Leif framework
git clone https://github.com/cococry/leif.git
cd leif && make && sudo make install && cd ..

# Install other dependencies
sudo apt-get install libglfw3-dev libgl1-mesa-dev libxcb1-dev
```

### Code Style Guidelines

**Naming Conventions:**
- Variables: `camelCase`
- Functions: `camelCase`
- Structs: `PascalCase`
- Constants: `UPPER_SNAKE_CASE`

**Example:**
```c
#define MAX_TASKS 1000

typedef struct Task {
    char description[256];
    bool isCompleted;
} Task;

void addNewTask(Task* taskList, const char* description) {
    // Implementation
}
```

### Testing

**Unit Testing Logic Module:**
```bash
cd logic
gcc -o logic_test logic.c -DTEST_MODE
./logic_test
```

**Memory Leak Detection:**
```bash
valgrind --leak-check=full ./todo
```

### Debugging

**Using GDB:**
```bash
gcc -g -o todo todo.c -lglfw -lGL -lleif -lclipboard -lm -lxcb
gdb ./todo
```

**Common GDB Commands:**
```
break main           # Set breakpoint
run                  # Run program
next                 # Step over
step                 # Step into
print variableName   # Print variable
continue             # Continue execution
```

## Contributing

### Contribution Guidelines

✅ **Do:**
- Follow the existing code style
- Add comments for complex logic
- Test on Linux before submitting
- Keep commits atomic and descriptive
- Update documentation as needed

❌ **Don't:**
- Submit untested code
- Break existing functionality
- Add unnecessary dependencies
- Include platform-specific code (non-Linux)

### Pull Request Process

1. **Fork the Repository**
```bash
# Fork on GitHub, then clone your fork
git clone https://github.com/YOUR_USERNAME/Todo-App-In-C.git
```

2. **Create Feature Branch**
```bash
git checkout -b feature/AmazingFeature
```

3. **Make Changes**
- Write code
- Add tests if applicable
- Update documentation

4. **Commit Changes**
```bash
git add .
git commit -m "Add: Brief description of changes"
```

5. **Push to Branch**
```bash
git push origin feature/AmazingFeature
```

6. **Open Pull Request**
- Go to GitHub
- Click "New Pull Request"
- Fill in template
- Submit for review

### Commit Message Format

```
Type: Brief description

Detailed description if needed

Fixes #123
```

**Types:**
- `Add:` New feature
- `Fix:` Bug fix
- `Update:` Improve existing feature
- `Docs:` Documentation changes
- `Refactor:` Code restructuring
- `Test:` Add tests

## Troubleshooting

### Build Issues

**Error: `leif.h: No such file or directory`**
```bash
# Install Leif framework
git clone https://github.com/cococry/leif.git
cd leif && make && sudo make install
sudo ldconfig
```

**Error: `cannot find -lglfw`**
```bash
# Install GLFW development files
sudo apt-get install libglfw3-dev
```

### Runtime Issues

**Application doesn't start**
```bash
# Check OpenGL support
glxinfo | grep "OpenGL version"

# Should show OpenGL 3.3 or higher
```

**Segmentation fault**
```bash
# Run with GDB to find the issue
gdb ./todo
run
backtrace  # After crash
```

### Performance Issues

**High CPU usage**
- Check if VSync is enabled
- Verify GPU drivers are up to date
- Monitor with `htop` or `top`

**Memory leaks**
```bash
# Use Valgrind
valgrind --leak-check=full --show-leak-kinds=all ./todo
```

## License

This project is licensed under the MIT License. See the [LICENSE](../LICENSE) file for details.

## Additional Resources

- **Leif UI Framework:** [github.com/cococry/leif](https://github.com/cococry/leif)
- **GLFW Documentation:** [glfw.org/documentation](https://www.glfw.org/documentation.html)
- **OpenGL Tutorial:** [learnopengl.com](https://learnopengl.com/)

## Support

- 🐛 **Report bugs:** [GitHub Issues](https://github.com/AbinVarghexe/Todo-App-In-C/issues)
- 💬 **Ask questions:** [GitHub Discussions](https://github.com/AbinVarghexe/Todo-App-In-C/discussions)
- 📧 **Contact:** Open an issue for support

---

[← Back to README](../Readme.md) | [View Quickstart →](QUICKSTART.md) | [Explore Features →](FEATURES.md)
