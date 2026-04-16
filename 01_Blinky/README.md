# 01_Blinky — Hardware Hello World / Donanımın Merhaba Dünyası

> 🇬🇧 [English](#english) | 🇹🇷 [Türkçe](#türkçe)

---

## English

This project blinks the onboard user LED (PC13) on the STM32F401 microcontroller at regular intervals.

### 🎯 Goals

- Set up a `Makefile`-based build pipeline.
- Control GPIO using the STM32 HAL library.
- Understand the pin configuration of the Blackpill board.

### 🔍 Technical Note (Debugging)

The board initially failed to run with F411 linker script settings. By inspecting `st-flash` logs, the reported **96 KiB of SRAM** revealed the device is actually an **STM32F401**. The project was updated to use the correct F401 memory layout and has been stable since.

### 🔧 Wiring

| ST-Link V2 | Blackpill |
| :--- | :--- |
| 3.3V | 3.3V |
| GND | GND |
| SWDIO | SWDIO |
| SWCLK | SWCLK |

### 💻 Tools Used

| Tool | Detail |
| :--- | :--- |
| **Language** | C |
| **Framework** | STM32 HAL |
| **Build System** | Makefile |
| **Flash Tool** | st-flash v1.7.0 |

---

## Türkçe

Bu proje, STM32F401 mikrodenetleyicisi üzerinde dahili kullanıcı LED'ini (PC13) belirli aralıklarla yakıp söndürmeyi amaçlar.

### 🎯 Hedefler

- `Makefile` tabanlı derleme sürecini yapılandırmak.
- STM32 HAL kütüphaneleri ile GPIO kontrolü sağlamak.
- Blackpill kartının pin konfigürasyonunu anlamak.

### 🔍 Teknik Detay (Debugging Notu)

Proje başlangıcında F411 linker script ayarlarıyla çalışmayan kartın, `st-flash` loglarından okunan **96 KiB SRAM** verisi sayesinde **STM32F401** olduğu doğrulanmıştır. Proje, doğru bellek adreslerine erişim sağlanması için F401 konfigürasyonuna güncellenerek kararlı hale getirilmiştir.

### 🔧 Bağlantı Şeması

| ST-Link V2 | Blackpill |
| :--- | :--- |
| 3.3V | 3.3V |
| GND | GND |
| SWDIO | SWDIO |
| SWCLK | SWCLK |

### 💻 Kullanılan Araçlar

| Araç | Detay |
| :--- | :--- |
| **Dil** | C |
| **Framework** | STM32 HAL |
| **Build System** | Makefile |
| **Flash Tool** | st-flash v1.7.0 |
