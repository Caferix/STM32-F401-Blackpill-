# STM32 Embedded Systems Studies / Gömülü Sistem Çalışmaları

> 🇬🇧 [English](#english) | 🇹🇷 [Türkçe](#türkçe)

---

## English

This repository contains embedded system projects developed with the STM32F401 series microcontroller, along with documentation of my learning process.

### 🛠️ Hardware Overview

| Component | Detail |
| :--- | :--- |
| **Development Board** | STM32 Blackpill |
| **MCU** | STM32F401CEU6 *(Despite the chip being labelled F411CEU6, SRAM and device ID checks confirmed it is an F401-series device.)* |
| **Programmer** | ST-Link V2 |
| **Operating System** | Linux / Ubuntu (ARM GCC Toolchain) |

### 📁 Project Structure

Each folder is a self-contained project with its own `Makefile`:

- **01_Blinky** — Basic GPIO configuration and LED control.
- *(Future projects will be added here: UART, ADC, I2C, etc.)*

### 🚀 Build & Flash Instructions

Navigate to the relevant project folder and run:

```bash
make        # Compiles the project
make flash  # Flashes to the board (requires st-flash)
```

---

## Türkçe

Bu depo, STM32F401 serisi mikrodenetleyici kullanarak geliştirdiğim gömülü sistem projelerini ve öğrenme sürecimi içermektedir.

### 🛠️ Donanım Bilgileri

| Bileşen | Detay |
| :--- | :--- |
| **Geliştirme Kartı** | STM32 Blackpill |
| **MCU** | STM32F401CEU6 *(Çip üzerinde F411CEU6 yazmasına rağmen, SRAM ve ID kontrolleri sonucunda F401 serisi olduğu saptanmıştır.)* |
| **Programlayıcı** | ST-Link V2 |
| **İşletim Sistemi** | Linux / Ubuntu (ARM GCC Toolchain) |

### 📁 Klasör Yapısı

Her klasör bağımsız bir proje niteliğindedir ve kendi `Makefile` dosyasına sahiptir:

- **01_Blinky** — Temel GPIO yapılandırması ve LED kontrolü.
- *(Gelecek projeler buraya eklenecektir: UART, ADC, I2C vb.)*

### 🚀 Derleme ve Yükleme Talimatı

Terminalde ilgili klasöre girip şu komutları kullanın:

```bash
make        # Derleme yapar
make flash  # Karta yükleme yapar (st-flash gerektirir)
```
