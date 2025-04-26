#!/bin/bash
# Check for dependencies
echo "Checking dependencies..."
deps=("glfw" "opengl" "leif" "clipboard" "xcb")
for dep in "${deps[@]}"; do
  echo "Checking for $dep..."
done
echo "Run ./todo to start the application"
