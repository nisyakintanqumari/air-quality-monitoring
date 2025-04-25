# air-quality-monitoring
A final project designed to monitor indoor air quality in hospitals using IoT sensors and real-time data processing. IoT-based Real-Time Air Quality Monitoring System for Hospital Environments using ESP32 and sensors.

# 🌬️ Air Quality Monitoring System
This project focuses on building an air quality monitoring system tailored for hospital environments. By integrating sensors with a microcontroller, the system detects harmful gases and displays the results on an LCD. The goal is to ensure a healthier and safer environment for patients, visitors, and medical staff. This project is an IoT-based air quality monitoring system designed for indoor environments, especially healthcare facilities like hospitals. It measures environmental parameters in real-time to ensure healthy indoor air.

## 📌 Features
- Real-time monitoring of temperature, humidity, and dust particles (PM2.5)
- Real-time gas detection (CO2, NH3, alcohol, etc.)
- LCD display output
- LED and buzzer alarm system for alerts
- Wi-Fi-enabled ESP32 microcontroller
- Cloud integration for data visualization
- Low-cost and compact design
- Ideal for hospitals, offices, and schools

## 🛠️ Tech Stack
- **Microcontroller:** ESP32, Arduino IDE
- **Sensors:** DHT11 (Temperature & Humidity), MQ-135 (Air Quality), PMS5003 (PM2.5)
- **Programming Language:** C/C++ (Arduino IDE)
- **Cloud:** Thingspeak / Blynk (optional)
- **Other:** OLED display / LCD Display (I2C), Jumper wires, Breadboard, Buzzer & LED indicators

## 🎯 Purpose
Hospitals need good air quality to protect vulnerable patients. This project addresses that by creating an affordable, responsive, and simple system to detect air quality issues.

## 📷 System Diagram
![image](https://github.com/user-attachments/assets/715dce21-9df2-4829-8b0e-2afcfb055d58)

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

## 📌 Status
✅ Completed – Final presentation and prototype delivered in [June, 2022].

## 🙋‍♀️ About Me

Hi! I’m **Nisya Kintan Qumari**, a Master’s graduate in Electrical Engineering from NTUST, Taiwan. I'm passionate about intelligent systems, IoT, and AI in real-world applications.

📫 [LinkedIn](https://www.linkedin.com/in/nisyakintanqumari)  
📧 nisyakintanqumari@gmail.com

## 📜 License
This project is licensed under the MIT License.
