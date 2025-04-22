# air-quality-monitoring
IoT-based Real-Time Air Quality Monitoring System for Hospital Environments using ESP32 and sensors.
# 🌬️ Air Quality Monitoring System

This project is an IoT-based air quality monitoring system designed for indoor environments, especially healthcare facilities like hospitals. It measures environmental parameters in real-time to ensure healthy indoor air.

## 📌 Features

- Real-time monitoring of temperature, humidity, CO₂, and dust particles (PM2.5)
- Wi-Fi-enabled ESP32 microcontroller
- Cloud integration for data visualization
- Low-cost and compact design
- Ideal for hospitals, offices, and schools

## 🛠️ Tech Stack

- **Microcontroller:** ESP32
- **Sensors:** DHT11 (Temperature & Humidity), MQ-135 (Air Quality), PMS5003 (PM2.5)
- **Programming Language:** C++ (Arduino IDE)
- **Cloud:** Thingspeak / Blynk (optional)
- **Other:** OLED display, Jumper wires, Breadboard

## 📷 System Diagram

![System Diagram](images/system-diagram.png)

## 🗂️ Folder Structure

| Folder | Description |
|--------|-------------|
| `/code` | Source code for ESP32 |
| `/images` | Diagrams or screenshots |
| `/docs` | Final project report or slides |
| `/data` | Sample sensor data |
| `/LICENSE` | Project license |

## 📋 How It Works

1. Sensors collect real-time air data
2. ESP32 processes and sends data to cloud platform
3. User can monitor from dashboard (e.g., Thingspeak, Blynk)

## 📈 Sample Data

| Time        | Temp (°C) | Humidity (%) | CO₂ (ppm) | PM2.5 |
|-------------|-----------|---------------|-----------|--------|
| 09:00:00 AM | 27.5      | 65            | 412       | 35     |
| 09:05:00 AM | 28.0      | 63            | 450       | 42     |

## 🧠 Future Improvements

- Add CO sensor and VOC sensor
- Create mobile dashboard for real-time alerts
- Solar-powered version

## 🙋‍♀️ About Me

Hi! I’m **Nisya Kintan Qumari**, a Master’s graduate in Electrical Engineering from NTUST, Taiwan. I'm passionate about intelligent systems, IoT, and AI in real-world applications.

📫 [LinkedIn](https://www.linkedin.com/in/nisyakintanqumari)  
📧 nisyakintanqumari@gmail.com

## 📜 License

This project is licensed under the MIT License.
