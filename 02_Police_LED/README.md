# 02_Police_Blinker — Dual LED Siren Effect / Çift LED Polis Çakarı

> 🇬🇧 [English](#english) | 🇹🇷 [Türkçe](#türkçe)

---

## English

This project creates a police siren (strobe) effect using two external LEDs (Red and Blue) controlled by an STM32 microcontroller and the HAL library.

### 🎯 Goals

- Implement a rhythmic strobe pattern using loops and delays.
- Use **User Labels** in STM32CubeMX for better code readability.
- Control multiple GPIO pins simultaneously.

### 🔍 Technical Note (Labels)

To maintain clean code, pins are defined as `LED_BLUE` and `LED_RED` using User Labels in the `.ioc` file. This allows the code to remain functional even if the physical pins are moved to different ports in the future.

### 🔧 Wiring

| Component | STM32 Pin (Label) | Note |
| :--- | :--- | :--- |
| **Blue LED** | `LED_BLUE` | Connect with 220Ω Resistor |
| **Red LED** | `LED_RED` | Connect with 220Ω Resistor |
| **Common GND** | GND | Ground rail |

### 💻 Tools Used

| Tool | Detail |
| :--- | :--- |
| **Language** | C |
| **Framework** | STM32 HAL |
| **Build System** | Makefile / STM32CubeIDE |
| **Flash Tool** | st-flash / STM32 Programmer |

---

## Türkçe

Bu proje, STM32 mikrodenetleyicisi ve HAL kütüphanesi kullanarak harici iki LED (Kırmızı ve Mavi) üzerinden polis sireni (çakar) efekti oluşturmayı amaçlar.

### 🎯 Hedefler

- Döngüler ve gecikmeler (delays) kullanarak ritmik çakar deseni oluşturmak.
- Daha okunabilir kod için STM32CubeMX üzerinde **Kullanıcı Etiketleri (User Labels)** kullanmak.
- Birden fazla GPIO pinini senkronize bir şekilde kontrol etmek.

### 🔍 Teknik Detay (Etiketleme)

Kodun temiz kalması için, `.ioc` dosyasında pinler `LED_BLUE` ve `LED_RED` olarak etiketlenmiştir. Bu sayede fiziksel pinler gelecekte farklı portlara taşınsa bile ana kod bloğunun değiştirilmesine gerek kalmaz.

### 🔧 Bağlantı Şeması

| Bileşen | STM32 Pini (Etiket) | Not |
| :--- | :--- | :--- |
| **Mavi LED** | `LED_BLUE` | 220Ω Direnç ile bağlayın |
| **Kırmızı LED** | `LED_RED` | 220Ω Direnç ile bağlayın |
| **Ortak GND** | GND | Toprak hattı |

### 💻 Kullanılan Araçlar

| Araç | Detay |
| :--- | :--- |
| **Dil** | C |
| **Framework** | STM32 HAL |
| **Build System** | Makefile / STM32CubeIDE |
| **Flash Tool** | st-flash / STM32 Programmer |