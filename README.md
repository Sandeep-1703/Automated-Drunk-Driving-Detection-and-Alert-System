Here's a `README.md` file based on your project description:

---

# Automated Drunk Driving Detection and Alert System

**Project by:** Sandeep Kumar (220958)
**Course:** EE381 - Project
**Date:** April 2025

## Table of Contents

1. [Introduction](#introduction)
2. [Problem Statement](#problem-statement)
3. [Existing Solutions](#existing-solutions)
4. [System Overview](#system-overview)
5. [Resources Required](#resources-required)
6. [System Architecture](#system-architecture)
7. [Results and Future Improvements](#results-and-future-improvements)
8. [References](#references)

## Introduction

This project aims to develop an **Automated Drunk Driving Detection and Alert System** to prevent drunk driving accidents, which are a major cause of road fatalities. Our solution automates the detection of alcohol in a driver’s breath, locks the vehicle ignition, and sends real-time location alerts to a predefined contact via a Telegram chatbot. This ensures timely intervention and improves road safety.

## Problem Statement

Drunk driving continues to be a significant problem globally, causing numerous road accidents and fatalities each year. Current methods to prevent drunk driving, such as breathalyzer tests, rely on manual intervention and law enforcement, which can be impractical and ineffective in real-time. This project seeks to solve this problem by creating an automated, cost-effective system that detects alcohol in the driver’s breath and prevents the car from starting if intoxication is detected.

## Existing Solutions

Several solutions currently attempt to address drunk driving, but each has its limitations:

1. **Traditional Breathalyzer Tests:**

   * Requires manual operation and law enforcement involvement.
   * Not suitable for real-time prevention.

2. **Ignition Interlock Devices (IID):**

   * Only used for convicted offenders.
   * Expensive and requires professional installation.

3. **Mobile Apps for Alcohol Detection:**

   * Often inaccurate, easy to bypass, and require user participation.
   * Lack integration with vehicle control systems.

Our system is unique in its approach as it:

* Uses an **MQ-135 gas sensor** to detect alcohol in the driver's breath.
* **Prevents vehicle ignition** by blocking the ignition switch using an **SG90 servo motor**.
* Sends **real-time location alerts** to a **Telegram chatbot** using an **ESP32 Wi-Fi module**.
* Allows **remote ignition unlocking** via Telegram commands.
* Is **fully automated**, **non-bypassable**, and **cost-effective**.

## System Overview

The system is designed to:

1. Detect alcohol in the driver’s breath using the **MQ-135 gas sensor**.
2. Prevent the car from starting by **locking the ignition** through an **SG90 servo motor**.
3. Send **real-time location alerts** to a predefined contact through a **Telegram chatbot**, using an **ESP32 Wi-Fi module**.
4. Enable **remote ignition unlocking** via a command sent through Telegram.

### Key Components:

* **MQ-135 Gas Sensor**: Detects alcohol in the air.
* **Arduino Microcontroller**: Controls the system logic and interfaces with other components.
* **ESP32 Wi-Fi Module**: Sends alerts and interacts with the Telegram chatbot.
* **Ublox NEO-6M GPS Module**: Tracks location.
* **SG90 Servo Motor**: Controls ignition lock mechanism.

### Software Tools:

* **Arduino IDE** for programming the microcontroller.
* **Telegram Bot API** for sending messages and receiving commands.
* **Google Maps API** for location sharing.

## Resources Required

### Hardware:

* MQ-135 Gas Sensor (Alcohol Detection)
* Arduino Microcontroller (e.g., Arduino Uno)
* ESP32 Wi-Fi Module (Communication & Alerts)
* Ublox NEO-6M GPS Module (Location Tracking)
* SG90 Servo Motor (Ignition Control)
* Power Supply and Connecting Wires
* Breadboard

### Software:

* **Arduino IDE**: For writing and uploading code to the Arduino.
* **Telegram Bot API**: For creating a bot to interact with the system and send alerts.
* **Google Maps API**: For generating real-time location links.

## System Architecture

The core system is built around the **ESP32**, which acts as the central controller. It connects and controls:

* The **MQ-135 sensor** for alcohol detection.
* The **SG90 servo motor** for locking/unlocking the ignition.
* The **NEO-6M GPS module** for tracking the vehicle’s location.
* The **Telegram Bot API** to send real-time location alerts and to receive remote commands for unlocking the ignition.

The system works as follows:

1. The **MQ-135 sensor** continuously monitors the air for alcohol vapors.
2. When the alcohol concentration exceeds a set threshold, the system locks the vehicle ignition by rotating the **SG90 servo motor**.
3. The **GPS module** retrieves the vehicle’s location, and the **ESP32** sends a message to the Telegram bot with the location link.
4. The vehicle owner or a predefined contact can send the command **“On”** via Telegram to unlock the ignition remotely.

## Results and Future Improvements

### Results:

* **Accurate Alcohol Detection**: The MQ-135 sensor successfully detected alcohol with minimal delay (\~1-2 seconds).
* **Ignition Control**: The SG90 servo motor effectively locked the ignition when alcohol was detected.
* **Real-Time Alerts**: Telegram alerts with accurate location links were sent within 5 seconds of detection.
* **Remote Unlocking**: The ignition unlocking feature worked as expected, responding to the Telegram **“On”** command.

### Limitations and Future Improvements:

1. **Detection Accuracy**: Environmental factors (e.g., humidity) can affect the sensor’s readings. Future versions could:

   * Integrate additional sensors for confirmation.
   * Use machine learning models to refine alcohol detection.

2. **Power Management**: The current prototype relies on USB power. Future designs could incorporate:

   * A **battery backup** with low-power modes.
   * **Solar charging** for sustainable operation.

3. **Scalability**: The current system is designed for a single vehicle. Future expansions could include:

   * A **centralized server** for fleet management.
   * **Improved GPS tracking** for multiple vehicles.

4. **Additional Features**: Potential enhancements include:

   * **Voice command** support via Telegram.
   * **Smart vehicle integration** for more seamless operation.
   * **Predictive analytics** to assess driver behavior.

## References

1. Arduino Official Documentation - [Arduino Docs](https://www.arduino.cc/reference/en/)
2. ESP32 Documentation - [Espressif Docs](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/)
3. TinyGPS++ Library - [TinyGPS++ on GitHub](https://github.com/mikalhart/TinyGPSPlus)
4. Telegram Bot API - [Telegram Bot API Docs](https://core.telegram.org/bots/api)
5. World Health Organization - [Road Safety Statistics](https://www.who.int/news-room/fact-sheets/detail/road-traffic-injuries)

---

This README provides a concise overview of your project, its goals, system architecture, and results. You can expand on specific areas if required, like the integration of sensors or details about system testing.
