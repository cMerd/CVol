# CVol
Cvol is a simple and configurable volume controller.

### Dependencies
Here are the list of tools you'll need:

 - `gcc/g++`
 - `alsalib`
 - `jsoncpp`
 - `raylib`

You probably can find these in your package manager.
For example in `pacman`:
```bash
sudo pacman -S gcc
sudo pacman -S alsa-lib alsa-utils
sudo pacman -S jsoncpp
sudo pacman -S raylib
```

### Installation 
Run below commands to install CVol:
```bash
git clone https://github.com/cMerd/CVol.git # Clone repo
cd CVol # change directory to cloned repo
mkdir build # Create build directory
make # Build 
make configure # Create default configuration
make install # Add executable to path
```

to uninstall
```bash
make uninstall
```

### Usage
Just execute `cvol` to run it.
`cvol --help` for more.

### Configuration
After installing the program the default configuration should be: `~/.config/cvol/config.json`.
You can edit this in any way you want. (Comments are ignored)

### Thanks for using!

