# AutoSAR_Education_Project

# Speed Control System for Vehicle with AUTOSAR and ISO 26262

## Project Overview
This project implements a vehicle speed monitoring and fuel injection control system using AUTOSAR architecture and following ISO 26262 functional safety standards. The system monitors vehicle speed, controls fuel injection, and implements safety features to prevent overspeed conditions.

## Features
- Real-time speed monitoring
- Automatic fuel injection cut-off when speed exceeds threshold
- Error logging for diagnostics
- Maximum speed storage for each driving cycle
- Compliance with AUTOSAR architecture
- Implementation of ISO 26262 functional safety concepts

## System Architecture
Below is a simplified landscape diagram of our Speed Control System architecture using AUTOSAR:
![Screenshot 2024-06-20 204709](https://github.com/Hariharan1223/AutoSAR_Education_Project/assets/106650889/c40cef16-8c48-4d4e-ae2b-fd3fa56fa875)

This diagram illustrates the layered architecture of our AUTOSAR-based system:
- The Application Layer contains the main software components (SWCs) for speed control, 
  parameter management, and non-volatile storage.
- The RTE (Runtime Environment) Layer facilitates communication between components.
- The Basic Software Layer includes diagnostic management, ECU abstraction, and 
  the MCAL (Microcontroller Abstraction Layer) which provides standardized interfaces 
  to the hardware.
- The Hardware Layer represents the physical components like speed sensors and fuel injectors.

This architecture ensures a modular, scalable, and standardized approach to our 
vehicle speed monitoring and fuel injection control system.

## AUTOSAR Components
- Speed Control App SWC
- Parameter SWC
- NVBlock SWC 
- Diagnostic Manager SWC
- ECU Abstraction SWC
- NV Manager SWC
- CDD SWC
