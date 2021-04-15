# thermo-pico
A program for the Raspberry Pi Pico written in C to output the current temperature in Celsius as binary numbers.

## pico setup
The LEDs must be connected to the following pins:

- For the integer digits: `0, 1, 2, 5, 6, 7`
- For the decimal decimal places: `10, 13, 14, 15`

## compilation
To compile the program properly you need the raspberry-pico-sdk (it's also available in the AUR) and cmake.
Create a folder for the build and make the program like this:
```
mkdir build
cd build
cmake ..
make
```

## installation
To install it, simply connect the pico to your PC while pressing the button on the pico,
mount it and copy the `.uf2` file into the mount directory.
Now you can `sync` and `umount /path/to/mnt/dir`.
The thermometer will start automatically if you don't press the button on startup.
