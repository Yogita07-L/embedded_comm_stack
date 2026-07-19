# Embedded Communication Stack

A hands-on embedded communication framework developed on ESP32 using ESP-IDF.

This project focuses on understanding embedded communication architecture by building a layered communication stack from hardware abstraction to application-level packet handling.

The implementation is developed incrementally, starting with UART communication and extending towards a reusable embedded communication framework.

---

# Goal

The goal of this project is to design and implement a reliable embedded communication stack while gaining practical experience with:

- Embedded software architecture
- UART communication
- Driver abstraction
- Packet protocol design
- CRC-based error detection
- Buffer handling
- Embedded debugging and testing

---

# Hardware

## Development Board

ESP32 DevKitC V4

## Communication Interface

UART2

## GPIO Configuration

| Signal | ESP32 GPIO |
|--------|------------|
| TX     | GPIO 17    |
| RX     | GPIO 16    |

## Development Environment

- ESP-IDF v6.x
- VS Code
- Git
- Windows

---

# System Architecture

The communication stack follows a layered architecture:

```

Application Layer

```
    |
    v
```

Packet Layer
(Create / Encode / Decode)

```
    |
    v
```

CRC8 Error Detection

```
    |
    v
```

UART Driver Abstraction

```
    |
    v
```

ESP-IDF UART Driver

```
    |
    v
```

ESP32 UART Peripheral

```

The application layer interacts with the custom driver and protocol layers instead of directly accessing ESP-IDF UART APIs.

---

# Implemented Features

## UART Driver Abstraction

Implemented a UART driver wrapper around ESP-IDF UART APIs.

Features:

- UART peripheral initialization
- UART parameter configuration
- TX/RX GPIO configuration
- UART transmit function
- UART receive function
- Software buffer configuration

The driver hides hardware-specific ESP-IDF implementation details from the application layer.

---

# Custom Packet Protocol

A custom packet format was designed for reliable communication.

Packet structure:

```

+------------+--------+-------------+------+
| Start Byte | Length | Payload     | CRC8 |
+------------+--------+-------------+------+

|  1 byte    | 1 byte | N bytes     |1 byte|

```

Example packet:

```

AA 03 41 42 43 68

```

Description:

```

AA        -> Start byte
03        -> Payload length
41 42 43  -> Payload data
68        -> CRC8 checksum

```

---

# Packet Handling

## Packet Creation

Creates a packet structure from application data.

Example:

Input:

```

41 42 43

```

Generated packet:

```

Start Byte : AA
Length     : 3
Payload    : 41 42 43

```

---

## Packet Encoding

Converts the packet structure into a byte stream suitable for transmission.

Example:

```

packet_t structure

```
    |
    v
```

Encoded UART buffer

AA 03 41 42 43 68

```

---

## Packet Decoding

The decoder validates received packets by:

- Checking start byte
- Extracting payload length
- Extracting payload data
- Calculating CRC8
- Comparing received and calculated CRC values

A packet is accepted only when CRC validation succeeds.

---

# CRC8 Error Detection

Implemented CRC8 checksum generation for packet integrity verification.

Configuration:

```

Polynomial : 0x07
Initial CRC: 0x00

```

CRC is calculated over:

```

Length + Payload

```

Example:

Input:

```

03 41 42 43

```

Calculated CRC:

```

68

```

During reception:

```

Received CRC == Calculated CRC

```
    |
    v
```

Packet valid

```

If the CRC values differ, the packet is rejected.

---

# Hardware Validation

The communication stack was tested using ESP32 UART2 loopback.

Connection:

```

ESP32 GPIO17 (TX)
|
|
v
ESP32 GPIO16 (RX)

```

Transmitted packet:

```

AA 03 41 42 43 68

```

Received packet:

```

AA 03 41 42 43 68

```

Validation:

```

Packet OK

Payload:
41 42 43

```

---

# Project Structure

```

embedded_comm_stack/

├── components/
│
├── packet/
│   ├── packet.c
│   └── packet.h
│
├── uart_driver/
│   ├── uart.c
│   └── uart_driver.h
│
├── main/
│   └── main.c
│
└── tests/
└── packet_test.c

```

---

# Testing

Host-based testing was implemented for packet layer validation.

Tested:

- Packet creation
- Packet encoding
- CRC8 calculation
- Packet decoding
- CRC validation

Host compiler:

```

MSYS2 GCC

```

Hardware validation:

```

ESP32 UART2 Loopback

```

---

# Current Status

Completed:

✅ UART driver abstraction  
✅ ESP32 UART communication  
✅ Custom packet format  
✅ Packet creation  
✅ Packet encoding  
✅ Packet decoding  
✅ CRC8 error detection  
✅ Host-based packet testing  
✅ ESP32 hardware loopback testing  

---

<!-- # Future Improvements

Planned extensions:

- UART receive state-machine parser
- Continuous packet reception handling
- Command-response protocol
- Improved error reporting
- Transport layer abstraction
- SPI communication framework with FPGA

--- -->

# Learning Outcomes

Through this project, practical experience was gained in:

- Embedded C development
- ESP-IDF framework
- UART peripheral communication
- Driver abstraction design
- Communication protocol implementation
- CRC error detection
- Embedded debugging
- Hardware/software integration



