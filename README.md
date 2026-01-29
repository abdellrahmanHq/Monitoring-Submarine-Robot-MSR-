# MSR: Monitoring Submarine Robot 🌊🪸

The **Monitoring Submarine Robot (MSR)** is a graduation project designed to monitor and protect the coral reefs in the **Gulf of Aqaba**. It combines marine robotics with artificial intelligence to provide real-time health assessments of underwater ecosystems.

---

## 🔗 Project Resources
* **Presentation Slides:** https://prezi.com/p/edit/4d6mk_edajb5/
* **AI Model Weights:** **Download best.pt from Google Drive**
* https://drive.google.com/file/d/1-qZXFiPcpG4b0AOHDcyOHuMH1okulJI2/view?usp=drive_link 🧠

---

## 🚀 Overview
The MSR system utilizes a "split-brain" architecture to handle complex environment monitoring:
* **Underwater Hardware:** An Arduino-based system controlling three brushless motors for precise movement and a CSI camera for high-quality visuals.
* **Surface Processing:** A **Jetson Nano** connected via a Cat 6 tether, running a **YOLOv11** object detection model.
* **Software Stack:** ROS2 for robotics communication, InfluxDB for data logging, and Grafana for professional visualization.

## ✨ Key Features
* **Real-time Detection:** Classifies coral status (Healthy, Bleached, etc.) using YOLOv11.
* **Interactive Dashboard:** A **Streamlit** web application for live monitoring and control.
* **Environmental Logging:** Integration with InfluxDB to track reef health over time.

---

## 📂 Repository Structure
| File | Description |
| :--- | :--- |
| `app.py` | The Streamlit dashboard and AI inference code. |
| `MSR.ino` | Firmware for controlling the submarine's brushless motors. |
| `MSR.pdf` | The complete graduation project technical report. |
| `MSR.mp4` | Video showing the submarine's operation and testing. |

---

## 🛠️ Installation & Setup

### 1. Download the AI Model
Because the `best.pt` file (YOLOv11 weights) exceeds GitHub's file size limit, you must download it manually from the link in the **Project Resources** section above and place it in the root directory of this project.

### 2. Install Dependencies
Ensure you have Python installed, then run:
```bash
pip install streamlit ultralytics influxdb-client
