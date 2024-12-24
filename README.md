# AHT20-UART-PC with Serial in Python

This project demonstrates how to read and display data from an AHT20 sensor using Python's `serial` library. The AHT20 sensor communicates with an STM32 microcontroller via I2C, and the data is transmitted to a PC over UART. The PC processes and displays the received data in real-time.

The project includes:
- STM32 code (`AHT20.c`, `AHT20.h`, `main.c`) for reading data from the AHT20 sensor via I2C and sending data over UART.
- Python script (`main.py`) for receiving and displaying the data over UART.

## Features
- Reads temperature and humidity data from the AHT20 sensor.
- Displays the data in real-time on the PC.

## Requirements

To run this project, ensure you have the following:

### Hardware:
- AHT20 sensor
- STM32F446RE microcontroller (or compatible)
- Wires for connecting the sensor to the STM32
- Data cable to connect the STM32 to the PC (UART)
- PC with Python installed

### Software:
- Python 3.7 or higher
- `pyserial` library

You can install the `pyserial` library using `pip`:
```bash
pip install pyserial
STM32 Firmware:
You need to flash the STM32 microcontroller with the provided main.c, AHT20.c, and AHT20.h files. These files configure the microcontroller to read data from the AHT20 sensor via I2C and send the data over UART to the PC.

Usage
STM32 Setup:

Flash the STM32 with the code from the main.c, AHT20.c, and AHT20.h files. Ensure the STM32 is properly connected to the AHT20 sensor via I2C.
The STM32 should send temperature and humidity data over UART to the connected PC.
Configure Python Script:

Open the main.py file and configure the serial port and baud rate to match your setup:
python
Copy code
SERIAL_PORT = 'COM7'  # Replace with your serial port on the PC
BAUD_RATE = 115200    # Default baud rate for UART on STM32
Make sure your STM32 is connected to the PC via UART (USB or other interface).
Run the Python Script:

In the terminal, navigate to the directory containing main.py and run:
bash
Copy code
python main.py
The script will display the real-time temperature and humidity data in the terminal window.
Additional Notes:
Make sure the STM32 is correctly configured to communicate with the AHT20 sensor over I2C and transmit the data over UART.
Adjust the serial port setting in the Python script based on your operating system:
For Windows, it's typically something like COM3, COM4, etc.
For Linux/macOS, it's typically /dev/ttyUSB0, /dev/ttyACM0, etc.
