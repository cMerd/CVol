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
make # Build 
make configure # Create default configuration
make install # Add executable to path
```

### Usage
Just execute `cvol` to run it.
`cvol --help` for more.

### Configuration
After installing the program the default configuration should be: `~/.config/cvol/config.json`.
And it looks like this:
```json
{
  // Default window configuration
  "window": {
    "bg": "#FFFFFF",
    "fg": "#000000",
    "width": 700,
    "height": 400,
  },

  // Slider (or volume selector)
  "slider": {
    "xPos": 100,
    "yPos": 100,
    "width": 500,
    "height": 80,
    "radius": 0.2, // radius will be applied to button too

    "disabled_bg": "#000000",
    "enabled_bg": "#0000FF",

    // slider button
    "button": {

      "seperator_width": 15,
      "seperator_color": "#111111",
      "seperator_margin": 15,
      // seperator_margin is the space between seperators by pixels
      // a seperator is the little lines on button

      "bg": "#999999",
      "hover_bg": "#BBBBBB", // background when hovered
      "click_bg": "#777777", // background when clicked

      // hover animation
      "animation": {
        "enabled": true,
        "scale": 0.1, // how much will it get bigger
        "speed": 0.1
      }
    }
  },

  // Text that shows the volume
  "volume_text": {
    "volume_label": "Volume: ",
    "xPos": 20,
    "yPos": 350,
    "font_size": 35,
    // specify the FULL path
    "font_path": "/usr/share/fonts/gnu-free/FreeMono.otf"
  }
}
```

You can edit this in any way you want.

### Thanks for using!

