# 🚀 Quick Start Guide

Get up and running with Todo App in minutes!

## Prerequisites

Ensure you have the following installed on your Linux system:

### Debian/Ubuntu
```bash
sudo apt-get update
sudo apt-get install build-essential git make gcc libglfw3-dev libgl1-mesa-dev libxcb1-dev
```

### Fedora
```bash
sudo dnf install gcc git make glfw-devel mesa-libGL-devel libxcb-devel
```

### Arch Linux
```bash
sudo pacman -S base-devel git make gcc glfw-ogl mesa libxcb
```

## Installation Methods

### Option 1: Automated Install (Recommended)

The fastest way to get started:

```bash
git clone https://github.com/AbinVarghexe/Todo-App-In-C.git
cd Todo-App-In-C
chmod +x install.sh
./install.sh
```

### Option 2: Manual Install

For more control over the installation process:

```bash
# 1. Install system dependencies (Debian/Ubuntu example)
sudo apt-get install build-essential libglfw3-dev libgl1-mesa-dev libxcb1-dev

# 2. Clone the repository
git clone https://github.com/AbinVarghexe/Todo-App-In-C.git
cd Todo-App-In-C

# 3. Install Leif UI framework
git clone https://github.com/cococry/leif.git
cd leif && make && sudo make install && cd ..

# 4. Build the application
make

# 5. Run the application
./todo
```

### Option 3: Custom Compilation

For developers who want to customize the build:

```bash
gcc -o todo todo.c -lglfw -lGL -lleif -lclipboard -lm -lxcb
```

**Linked Libraries:**
- `-lglfw` - GLFW window management
- `-lGL` - OpenGL graphics
- `-lleif` - Leif UI framework
- `-lclipboard` - Clipboard functionality
- `-lm` - Math library
- `-lxcb` - X protocol C-language binding

## First Run

After installation, launch the app:

```bash
./todo
```

## Basic Usage

| Action | How To |
|--------|--------|
| **Add Task** | Click the "Add" button and enter your task description |
| **Complete Task** | Check the checkbox next to the task |
| **Delete Task** | Click the delete button (🗑️) on the task |
| **Filter Tasks** | Use filter buttons: All, Pending, or Completed |

## Testing

To test the logic module separately:

```bash
cd logic
gcc logic.c -o logic
./logic
```

## Troubleshooting

### Common Issues

**Build errors about missing libraries**
- Ensure all prerequisites are installed
- Run `ldconfig` after installing Leif

**Application doesn't launch**
- Verify you're running on a Linux system
- Check OpenGL support: `glxinfo | grep "OpenGL version"`

**Permission denied**
- Make install script executable: `chmod +x install.sh`
- Ensure you have write permissions in the directory

## Next Steps

- 📖 Read the [full documentation](DOCUMENTATION.md) for detailed information
- ✨ Explore [features](FEATURES.md) to learn what the app can do
- 🤝 Check out [contributing guidelines](../Readme.md#contributing) to help improve the project

---

Need help? [Open an issue](https://github.com/AbinVarghexe/Todo-App-In-C/issues) on GitHub.
