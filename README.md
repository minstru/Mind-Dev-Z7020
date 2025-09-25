# Mind-Dev-Z7020 Development Board Resources

The **Mind-Dev-Z7020** repository provides comprehensive resources for the Mind-Dev-Z7020 development board.  
It includes **Vivado hardware designs**, **Vitis application examples**, and **Linux-based experiments**, enabling users to quickly get started with development and explore a wide range of peripherals and system features.

This repository is intended as both a learning resource and a reference collection for developers working with the Mind-Dev-Z7020 platform. Tutorials, example projects, and supporting files cover essential interfaces such as GPIO, UART, CAN, Ethernet (TCP/UDP), USB, audio (WM8960), RGB LCD with LVGL, and dual OV5640 cameras.

For detailed tutorials, schematics, and hardware documentation, please visit: [www.minstru.com](http://www.minstru.com).

![Mind-Z7020 Board](image.png)

---

## 📚 Tutorials and Example Projects

The `TutorialsCode` directory contains ready-to-use example projects for different peripherals and use cases. Each project includes both **Vivado hardware design files** and **Vitis software projects**, with some examples based on **FreeRTOS**.

| Example Project                          | Description                                                  |
| ---------------------------------------- | ------------------------------------------------------------ |
| **Mind-Z7020_Vitis_Example**             | Basic peripheral examples, covering GPIO, UART, CAN, TCP/UDP communication, and USB |
| **Mind-Z7020_Vitis_AUDIO_Example**       | Audio example using WM8960 audio codec module with FreeRTOS  |
| **Mind-Z7020_Vitis_LVGL_Example**        | RGB LCD display example using FreeRTOS + LVGL 9.2.2          |
| **Mind-Z7020_Vitis_Dual_OV5640_Example** | Dual OV5640 camera example                                   |
| **Mind-Z7020_linux_Example**             | Linux peripheral test examples, running under PetaLinux/Zynq Linux |

---

## 🚀 Getting Started

### Clone the Repository
```bash
git clone https://github.com/minstru/Mind-Dev-Z7020.git
cd Mind-Dev-Z7020
