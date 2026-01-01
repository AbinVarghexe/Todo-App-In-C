<div align="center">

# 📝 Todo-new-app

A lightweight task management app built with C and OpenGL

[![C](https://img.shields.io/badge/C-00599C?logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Linux](https://img.shields.io/badge/Linux-FCC624?logo=linux&logoColor=black)](https://www.linux.org/)
[![OpenGL](https://img.shields.io/badge/OpenGL-5586A4?logo=opengl&logoColor=white)](https://www.opengl.org/)
[![GLFW](https://img.shields.io/badge/GLFW-3.3-blue)](https://www.glfw.org/)
[![License](https://img.shields.io/badge/License-MIT-green)](LICENSE)

</div>

> **⚠️ Linux Only** - This application runs exclusively on Linux systems

## Overview

A high-performance todo app using C, OpenGL, GLFW, and the Leif UI framework for task management with a modern GUI.

## Features

- ✅ Add, delete, and complete tasks
- 🔍 Filter tasks (All, Pending, Completed)
- ⚡ Real-time UI updates
- 📋 Linked list data structure
- 🎨 Interactive UI with Leif framework

## Screenshots

| Task List View | Adding New Task |
|----------------|-----------------|
| ![Task List](images/1731266201874.png) | ![Add Task](images/1731266080148.png) |

## 📦 Installation

### Prerequisites

Before you begin, ensure you have the following installed on your Linux system:

```bash
# Debian/Ubuntu
sudo apt-get update
sudo apt-get install build-essential git make gcc libglfw3-dev libgl1-mesa-dev libxcb1-dev

# Fedora
sudo dnf install gcc git make glfw-devel mesa-libGL-devel libxcb-devel

# Arch Linux
sudo pacman -S base-devel git make gcc glfw-ogl mesa libxcb
```
Installation

### Quick Start

```bash
git clone https://github.com/AbinVarghexe/Todo-new-app.git
cd Todo-new-app
chmod +x install.sh
./install.sh
```

### Manual Install

```bash
# Install dependencies (Debian/Ubuntu)
sudo apt-get install build-essential libglfw3-dev libgl1-mesa-dev libxcb1-dev

# Clone and build
git clone https://github.com/AbinVarghexe/Todo-new-app.git
cd Todo-new-app
make

# Install Leif
git clone https://github.com/cococry/leif.git
cd leif && make && sudo make install && cd ..

# Compile--|-------------|
| **Add Task** | Click the "Add" button and enter task description |
| **Complete Task** | Check the checkbox next to the task |
| **Delete Task** | Click the delete button on the task |
| **Filter Tasks** | Use filter buttons (All/Pending/Completed) |

### Command-line Compilation

For custom builds or modifications:

```bash
gcc -o todo todo.c -lglfw -lGL -lleif -lclipboard -lm -lxcb
```

**Linked Libraries:**
- `-lglfw` - GLFW library
- `-lGL` - OpenGL library
- `-lleif` - Leif UI framework
- `-lclipboard` - Clipboard functionality
- `-lm` - Math library
- `-lxcb` - X protocol library

## 📁 Project Structure

```
Todo-new-app/
├──Usage

Run the application:

```bash
./todo
```

### Testing Logic Module

```bash
cd logic
gcc logic.c -o logic
./logic
```
- ✅ Follow C coding standards
- ✅ Add comments for complex logic
- ✅ Test on Linux before submitting
- ✅ Update documentation as needed
- ✅ Keep commits atomic and descriptive

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- **[Leif](https://github.com/cococry/leif)** - For the excellent lightweight UI framework
- **GLFW Team** - For cross-platform OpenGL window management
- **Contributors** - Thank you to all who have contributed to this project!

---

<div align="center">

**Made with ❤️ using C and OpenGL**

[⬆ Back to Top](#-todo-new-app)

</div>
Contributing

Contributions are welcome! 

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## License

MIT License - see [LICENSE](LICENSE) file for details.

## Acknowledgments

- [Leif](https://github.com/cococry/leif) - Lightweight UI framework
- GLFW Team - OpenGL window management

---

<div align="center">

Made with ❤️ using C and OpenGL
