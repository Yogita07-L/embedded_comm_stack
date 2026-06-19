# Embedded Communication Stack

A hands-on embedded systems project built on ESP32 using ESP-IDF.

## Goal

The goal of this project is to learn and demonstrate:

- Embedded software architecture
- UART communication
- Driver development concepts
- Buffer management
- Interrupt-driven communication
- Communication protocol design
- Embedded debugging and testing

The project is implemented incrementally, starting from UART and expanding into a reusable communication framework.

---

## Hardware

### Development Board

ESP32 DevKitC V4

### USB Interface

CP2102 USB-to-UART Bridge

### Development Environment

- ESP-IDF v6.x
- VS Code
- Git
- Windows

---

## Current Scope

Phase 1 focuses on understanding and implementing UART communication.

Objectives:

- Configure UART
- Transmit data
- Receive data
- Build a UART driver wrapper
- Understand ESP32 UART hardware

---

## Planned Architecture

Application Layer

↓

UART Driver

↓

ESP-IDF UART APIs

↓

ESP32 UART Peripheral

↓

CP2102 USB-UART Bridge

↓

PC Serial Monitor

---



## Learning Outcomes

This project aims to develop practical experience with:

- Embedded C
- ESP-IDF
- UART communication
- Interrupts
- Buffers and queues
- Driver architecture
- Embedded debugging
- Git-based development

---

## Status

Current Phase:

Phase 1 - UART Driver Development