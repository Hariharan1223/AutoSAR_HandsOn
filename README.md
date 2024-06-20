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
+------------------------------+
|      Application Layer       |
+------------------------------+
| +-------------------------+ |
| |  Speed Control App SWC  | |
| |   - SpeedMonitoring     | |
| |   - SpeedCalculation    | |
| |   - InjectionCutoff     | |
| |   - DataStorage         | |
| +-------------------------+ |
|                             |
| +-------------------------+ |
| |    Parameter SWC        | |
| +-------------------------+ |
|                             |
| +-------------------------+ |
| |    NVBlock SWC          | |
| +-------------------------+ |
+==============================+
|        RTE Layer             |
+==============================+
+------------------------------+
|     Basic Software Layer     |
+------------------------------+
| +-------------------------+ |
| | Diagnostic Manager SWC  | |
| +-------------------------+ |
|                             |
| +-------------------------+ |
| |  ECU Abstraction SWC    | |
| +-------------------------+ |
|                             |
| +-------------------------+ |
| |   MCAL (Drivers)        | |
| |   - ADC, GPIO, CAN, etc.| |
| +-------------------------+ |
+==============================+
|      Hardware Layer          |
+==============================+
| Speed Sensor | Fuel Injector |
+-------------+----------------+
[diagram.txt](https://github.com/user-attachments/files/15916159/diagram.txt)



## AUTOSAR Components
- Speed Control App SWC
- Parameter SWC
- NVBlock SWC (optional)
- Diagnostic Manager SWC
- ECU Abstraction SWC
