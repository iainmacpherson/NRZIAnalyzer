# NRZI Analyzer

*Note: this was created for debugging a personal project and will likely not be updated again.*

This is a fork of the example low level analyzer from Saleae and implements a plugin for their Logic 2 software. It provides extremely bare bones decoding of NRZI data, sampled with DDR according to a paired clock signal.

Parameters:
* Clock Channel - The channel on which the clock signal is connected.
* Data Channel - The channel on which the data signal is connected.
* DDR Frequency - Double whatever the frequency of the clock is.

The README from the parent repository is [build_instructions](docs/build_instructions.md) and includes all the infomation needed to build and use this extension.

