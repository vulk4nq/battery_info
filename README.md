## Project Description
### I created it for use in i3-wm because i hate bars
This is a C program that utilizes the GTK library to display battery information in a dialog window. The program retrieves battery information from the system and presents it in a dialog window, which automatically closes after n second.

## Features
- Retrieves battery information from the system
- Displays battery information in a GTK dialog window
- Automatically closes the dialog window after n second

## Getting Started
To run the program, you'll need to have the GTK development libraries installed on your system. Follow the instructions below to get started:

1. Clone the repository:
   ```bash
   git clone https://github.com/vulk4nq/battery_info.git
   cd battery_info
2. Compile the program:
   ```bash
   gcc -o battery_info battery_info.c `pkg-config --cflags --libs gtk+-3.0`
3. Bind binary to hotkey or run the program
   ```bash
   ./battery_info

## Requirements
- GTK 3.0 or higher
