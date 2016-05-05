NVidia Jetson TX1 Companion Board
=================================

__Project: IR&D Stereo Cameras__

__A. Marburg__


Introduction
------------

The 2016 SEG IR&D Stereo Camera project is supporting the development of a low-cost
stereo camera head in a shallow water enclosure.   The sensor head
will provide stereo video including a dense depth estimate and will include
sufficient on-board processing power for realtime 3D reconstruction.

The sensor head consists of a [Stereolabs
Zed](https://www.stereolabs.com/zed/specs/) USB3 stereo camera and an [NVIdia
Jetson TX1](http://www.nvidia.com/object/jetson-tx1-module.html) embedded
computer.   The Zed consists of a two-camera USB3 sensor unit and a proprietary
set of software libraries for interfacing with the sensor and generating
realtime dense stereo.  These libraries are accelerated using NVidia's CUDA
technology.  The Jetson TX1 computer module contains four 64-bit ARM processor
cores as well as a 256-CUDA core GPU, which allows the Jetson TX1 to run the Zed
processing library.

![Jetson TX1 base board](jetson_tx1.jpg)

The Jetson itself lives on a small (approx. credit card) carrier board, but for
development purposes a mini-itx 5" x 5" motherboard is provided which includes a
number of standardized connectors (SATA, Ethernet, SD card, PCI-E, mini-PCI-E)
as well as expansion and debug pin headers.   While the 5"x5" form factor is
somewhat awkward for packaging, the motherboard greatly simplifies the
bootstrapping of new projects.   Given that complete schematics for the
motherboard are available, more application-specific host boards are
theoretically possible.

The underwater enclosure package has a single Subconn 8-pin connector which
provides Cat6 UTP to the sensor head.  This cabling provides gigabit ethernet as
well as 60W power-over-ethernet (PoE).  Note 60W PoE is non-standard. This
connector allows reuse of existing subsea ethernet cables but prevents and
supplemental functions going over the same cable (unless we put an Ethernet hub
in the box).      The package also includes two [BlueRobotic Lumen
1](https://www.bluerobotics.com/store/electronics/lumen-light-r1/) submersible
LED lights.

The standard motherboard has a number of features which are inconvenient when
the board is enclosed with limited access.  A companion board has been designed
to deal with some of these inconveniences, to provide an alternate RF connection
into the Jetson, and to provide a breakout for some of the more common expansion
headers on the Jetson motherboard.

Specification
-------------

The functional spec is:

* **Manage Jetson Power/state**
	* *Enable auto power-on.*	 Press power button a fixed delay after startup.   Interfaces directly with the power button.  The power control is an open-drain output on the Jetson (check on schematic).   The existing power switch on baseboard is mechanical switch to ground.   Use enhancement N-MOSFET as equivalent to pull bus to ground.
	* *Provide an out-of-band (OOB) way to reset the Jetson.* Uses reset button, see notes above about power button.
	* *Deadman timer.*  Reset if no communications from Jetson after period of time.  Requires the micro to communicate with the Jetson --- will use I2C bus.
* **Provide OOB communications.**  Use [Digi XBee](http://www.digi.com/products/xbee-rf-solutions/modules/xbee-802-15-4) (which happen to have sitting around).
	* *Reset the Jetson remotely.*  Use digital I/O on XBee to trigger the microcontroller.
	* *OOB mechanism to manual disable the deadman.*  Use digital I/O on XBee.
	* *Access Jetson serial console.*  Connection is via a 3v3 UART is 115200, with 8 bits, no parity, and 1 stop bit (115200 8N1), RTS/CTS.  It's on J21 pins 8,10 (Jetson pins UART0_*).  N.b. the Xbee has a nominal 250kbps data rate over-the-air.
* **Host supplemental sensors**
	* *Pressure / temp sensor.*  Bosch BMP280 on [Adafruit breakut board](https://www.adafruit.com/products/2651) with I2C interface.  The breakout includes a voltage regulator and level shifters which we can bypass.   Note this sensor connects to to I2C on the *Jetson*, not the micro.
	* *Headers for supplemental temp sensors?* 4 pin headers for VDD/Gnd/SDA/SCL for add'l I2C sensors
* **Break out Jetson baseboard pin headers**
	* *GPIO Header (J26).*
	* *Expansion Header (J21).*
	* *Serial port (J17).* Jetson TX1 USART1_* at 3V3
	* *Debug header (J10)*   Uses dense Samtec connector, see below.
* **Support electronics for MSP430 microcontroller**
	* *Header for in-circuit programming.*
* **LED Indicators.**
	* Deadman/heartbeat?
	* Communications received?
* **Board should be able to run standalone for debugging.**
	* LEDs for status/debug?
	* Power from debugger?
* **Power board from Jetson?**  Have checked, 3v3 is on all the time.
* **Control BlueRobotics lights**
	* *Generate PWM.* Standard firmware in lights (they run Atmegas, btw) are off when signal line is pulled down, servo PWM for dimming, and on full when pulled high.

Electrical Design
------

The board accomplishes two primary functions.  First, it mates to and provide
breakouts for four of the expansion headers on the Jetson board:

![Jetson TX1 base board](jetson_tx1_carrier_board_diagram.png)

Very briefly:

 * Debug connector (J10).   ~~Power and reset, as well as JTAG, UART and I2C (not used), primarily at 1v8.   This is a high density 0.5mm connector (Samtec QSH-30-01-L-D-A-TR).  The simplest interface appears to be putting the same connector on the companion board and using pre-made jumper cable from baseboard to companion board.~~  *Scratch that.  Too hard.  Use J6/J3 instead.*

The other three connectors are standard 0.1" pin headers.  The board will mount directly on these with female pinheaders on the bottom of the companion board.

* **Expansion header** (J21).  I2C, I2S, SPI, UART at 3v3.
* **GPIO** (J26).   GPIOs, mostly, some I2S
* **Serial Port** (J17).   Supplemental UART.  Notably, not the Jetson's console (this is on J21).  Not using, just breaking out.
* **Power switch** (J6).   Two-pin 0.1" connector with power-on signal and ground.  Short momentarily to power board on.
* **Reset** (J3).   Two-pin 0.1" connector with reset signal and ground.  Short momentarily to reset.


The companion board also hosts a MSP430 microprocessor.  As per the spec, this micro will:

 * Turns the Jetson on when power is applied
 * Provides an OOB connection to reset the Jetson
 * Provide PWM signals to the two Blue Robotics lights (under control of the Jetson)

The board also hosts a pressure/temperature sensor (Bosch BMP280), which interfaces to the
I2C on the Jetson (not on the microprocessor) and an XBee radio.  The XBee provides
wireless connectivity to the Jetson's serial console.  It can also communicate to the microcontroller via digital I/O (no serial interface to the micro).

Firmware Design
-----



Software Interface on Jetson
------