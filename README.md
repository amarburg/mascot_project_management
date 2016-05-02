NVidia Jetson TX1 Companion Board
=================================

__Project: IRD Stereo Cameras__

__A. Marburg__


Introduction
------------

The 2016 SEG IRD Stereo Camera project is supporting the development of a low-cost
stand-alone stereo sensing head in a shallow water enclosure.   The sensor head
will provide stereo video including a dense depth estimate and will include
sufficient on-board processing power for realtime 3D reconstruction.

The sensor head consists for a [Stereolabs Zed](https://www.stereolabs.com/zed/specs/) USB3 stereo camera
and an [NVIdia Jetson TX1](http://www.nvidia.com/object/jetson-tx1-module.html)
embedded computer.   The Zed consists of a two-camera USB3 sensor unit and a
proprietary set of software libraries for interfacing with the sensor and
generating realtime dense stereo.  These libraries are accelerated using NVidia's CUDA technology.  The Jetson TX1 computer module contains four 64-bit ARM processor cores as well as a
256-CUDA core GPU, which allows the Jetson TX1 to run the Zed processing library.

The Jetson itself lives on a small (approx. credit card) carrier board, but for
development purposes a mini-itx 5" x 5" motherboard is provided which includes a number of
standardized connectors as well as expansion and debug headers.   While the 5"x5" form factor
is somewhat awkward for packaging, the motherboard greatly simplifies the bootstrapping of new projects.   Given complete schematics for the motherboard, more application-specific host boards
are theoretically possible.

The sensor package has a single connector which provides Cat6 UTP to the sensor head.  This cabling provides gigabit ethernet as well as 60W power-over-ethernet (PoE).  Note 60W PoE is
non-standard.

The standard motherboard has a number of features which are inconvenient when the board
is enclosed with limited access.  A companion board has been designed to
deal with some of these inconveniences and to provide a breakout for some of the more common
expansion headers on the Jetson motherboard.

Specification
-------------

The functional spec is outlined below:

* Manage Jetson Power/state
	* **Enable auto power-on.**	 Press power button a fixed delay after startup.   Interfaces directly with the power button.  This is an open-drain input on the Jetson with a pull-up to 1v8 (check on schematic).   Power switch on baseboard is mechanical switch to ground.   Use enhancement N-FET as equivalent to pull bus to ground.
	* **Provide an OOB way to reset the Jetson.** Uses reset button, see notes above about power button.
	* Deadman timer.  Reset if no communications (I2C?) after period of time. Manual disable/override on deadman?
* Provide OOB communications
	* Reset the Jetson remotely. OOB connection to microcontroller?  Maybe magic pattern (break) to serial port?  Reset or power on.
	* Access serial console. Wireless or IR?. Connection speed is 115200, with 8 bits, no parity, and 1 stop bit (115200 8N1). Flow control will be RTS/CTS.  3v3.  Apparently it's on J21 pins 8,10 (Jetson pins UART0_*), board siganls UART1_*_HDR_3V3.   J17 hosts TX1 signals UART1_*
* Host supplemental sensors
	* Pressure / temp sensor.  Bosch BMP280.  Adafruit (https://www.adafruit.com/products/2651) includes vreg and level shifters.  Don't need.
	* Headers for supplemental temp sensors? 4 pin headers for VDD/Gnd/SDA/SCL for add'l I2C sensors
* Break out supplemental signals
	* GPIO Header (J26). Pin headers
	* Expansion Header (J21). Serial port (J17). Jetson TX1 USART1_* at 3V3
* Support for MSP430
	* Programming header
* LED Indicators.
	* Deadman?
	* Communications received?
* Standalone version of board for debugging.  LEDs for status/debug?
* Power board from Jetson?  3v3 is on all the time.
* Control BlueRobotics lights
	* Generate PWM. Turn off lights?

Electrical Design
------

The board accomplishes two primary functions.  First, it mates and provide breakouts to four of the expansion headers on the Jetson board:

![Jetson TX1 base board](jetson_tx1_carrier_board.png)

Very briefly:

 * Debug connector (J10).   Power and reset, as well as JTAG, UART and I2C (not used).  Primarily at 1v8.   This is a high density 0.5mm connector (Samtec QSH-30-01-L-D-A-TR).  The simplest interface appears to be putting the same connector on the companion board and using pre-made jumper cable from baseboard to companion board.

The other three connectors are standard 0.1" pin headers.  The board will mount directly on these with female pinheaders on the bottom of the companion board.

 * Expansion header (J21).  I2C, I2S, SPI, UART at 3v3.
 * GPIO (J26).   GPIOs, mostly, some I2S
 * Serial Port (J17).   Supplemental UART.  Notably, not the Jetson's console (this is on J21).

The companion board also hosts a MSP430 microprocessor.  As per the spec, this micro will:

 * Turns the Jetson on when power is applied
 * Provides an OOB connection to reset the Jetson
 * Provide PWM signals to the two Blue Robotics lights (under control of the Jetson)

The board also hosts a pressure/temperature sensor (Bosch BMP280), which interfaces to the
I2C on the Jetson (not on the microprocessor) and an XBee radio.  The XBee provides
wireless connectivity to the Jetson's console and OOB to the microcontroller via DIO.

Firmware Design
-----



Software Interface on Jetson
------
