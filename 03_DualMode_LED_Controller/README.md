# 03_DualMode_LED_Controller / Çift Modlu LED Kontrolü

> 🇬🇧 [English](#english) | 🇹🇷 [Türkçe](#türkçe)

---

## English

This project drives 5 LEDs connected to GPIOA using two push buttons. It implements two top-level control modes — **Automatic** and **Manual** — switchable at runtime.

### 🎯 Goals

- Manage multiple LEDs with array-based GPIO control.
- Implement a state machine using `enum` for clean mode management.
- Handle button debouncing and simultaneous key detection in bare-metal C.
- Explore different LED animation patterns.

### 🔧 Hardware

| Component | Detail |
| :--- | :--- |
| **LEDs** | 5× on GPIOA (LED0–LED4) |
| **Buttons** | LEFT\_BUTTON, RIGHT\_BUTTON |
| **System Clock** | 84 MHz (HSI + PLL) |

**ST-Link V2 → Blackpill wiring:**

| ST-Link V2 | Blackpill |
| :--- | :--- |
| 3.3V | 3.3V |
| GND | GND |
| SWDIO | SWDIO |
| SWCLK | SWCLK |

### 🕹️ Control Modes

#### Automatic Mode (default)
The LEDs cycle through 5 effects. Use the buttons to switch between them:

| Button | Action |
| :--- | :--- |
| RIGHT | Next effect → |
| LEFT  | Previous effect ← |

| # | Effect | Description |
| :--- | :--- | :--- |
| 0 | ALL\_OFF | All LEDs off |
| 1 | ALL\_ON | All LEDs on |
| 2 | ALL\_TOGGLE | All LEDs blink together (200 ms) |
| 3 | KNIGHT\_RIDER | Sweeping single LED, left → right → left |
| 4 | RANDOM | Random LED flashes |

#### Manual Mode
Press **both buttons simultaneously** to enter Manual Mode. In this mode, a single LED is lit at a time:

| Button | Action |
| :--- | :--- |
| RIGHT | Select next LED → |
| LEFT  | Select previous LED ← |
| LEFT + RIGHT | Return to Automatic Mode |

### 💡 Implementation Notes

- **Debouncing:** A `HAL_Delay(50–100 ms)` software debounce is applied on all button events.
- **Simultaneous press detection:** When one button is detected, the firmware waits 100 ms and then polls the other; if both are active, the mode switches.
- **`rand()` seeding:** The random effect uses `rand() % 5` without a seed, so the sequence is deterministic across resets. Consider seeding with a timer value for true randomness.
- **`led_delay` constant:** Knight Rider and Random effects use a 20 ms step delay (`#define led_delay 20`). Adjust to taste.

### 💻 Tools Used

| Tool | Detail |
| :--- | :--- |
| **Language** | C |
| **Framework** | STM32 HAL |
| **Build System** | Makefile |
| **Flash Tool** | st-flash v1.7.0 |
| **System Clock** | 84 MHz (HSI, PLL: M=8 N=84 P=2) |

---

## Türkçe

Bu proje, GPIOA'ya bağlı 5 LED'i iki buton aracılığıyla yönetir. Çalışma zamanında geçiş yapılabilen **Otomatik** ve **Manuel** olmak üzere iki ana kontrol modu sunar.

### 🎯 Hedefler

- Dizi tabanlı GPIO kontrolüyle birden fazla LED yönetmek.
- Temiz mod yönetimi için `enum` kullanan bir durum makinesi oluşturmak.
- Bare-metal C'de buton debounce ve eş zamanlı tuş algılamayı gerçeklemek.
- Farklı LED animasyon desenlerini keşfetmek.

### 🔧 Donanım

| Bileşen | Detay |
| :--- | :--- |
| **LED'ler** | 5× GPIOA üzerinde (LED0–LED4) |
| **Butonlar** | LEFT\_BUTTON, RIGHT\_BUTTON |
| **Sistem Saati** | 84 MHz (HSI + PLL) |

**ST-Link V2 → Blackpill bağlantısı:**

| ST-Link V2 | Blackpill |
| :--- | :--- |
| 3.3V | 3.3V |
| GND | GND |
| SWDIO | SWDIO |
| SWCLK | SWCLK |

### 🕹️ Kontrol Modları

#### Otomatik Mod (varsayılan)
LED'ler 5 efekt arasında döngü yapar. Efektler arasında geçiş için butonları kullanın:

| Buton | Eylem |
| :--- | :--- |
| SAĞ | Sonraki efekt → |
| SOL | Önceki efekt ← |

| # | Efekt | Açıklama |
| :--- | :--- | :--- |
| 0 | ALL\_OFF | Tüm LED'ler kapalı |
| 1 | ALL\_ON | Tüm LED'ler açık |
| 2 | ALL\_TOGGLE | Tüm LED'ler birlikte yanıp söner (200 ms) |
| 3 | KNIGHT\_RIDER | Tek LED sağa-sola süpürme hareketi |
| 4 | RANDOM | Rastgele LED yanması |

#### Manuel Mod
**İki butona aynı anda basarak** Manuel Mod'a geçilir. Bu modda tek bir LED yanar:

| Buton | Eylem |
| :--- | :--- |
| SAĞ | Sonraki LED'i seç → |
| SOL | Önceki LED'i seç ← |
| SOL + SAĞ | Otomatik Mod'a dön |

### 💡 Uygulama Notları

- **Debounce:** Tüm buton olaylarında `HAL_Delay(50–100 ms)` ile yazılımsal debounce uygulanmaktadır.
- **Eş zamanlı tuş algılama:** Bir buton algılandığında firmware 100 ms bekler ve ardından diğer butonu okur; her ikisi de aktifse mod değişir.
- **`rand()` seed sorunu:** Rastgele efekt, seed verilmemiş `rand() % 5` kullanır; bu nedenle sıralama her sıfırlamada aynıdır. Gerçek rastgelelik için bir timer değeriyle seed'lemeyi düşünebilirsin.
- **`led_delay` sabiti:** Knight Rider ve Rastgele efektler 20 ms adım gecikmesi kullanır (`#define led_delay 20`). İsteğe göre değiştirilebilir.

### 💻 Kullanılan Araçlar

| Araç | Detay |
| :--- | :--- |
| **Dil** | C |
| **Framework** | STM32 HAL |
| **Build System** | Makefile |
| **Flash Tool** | st-flash v1.7.0 |
| **Sistem Saati** | 84 MHz (HSI, PLL: M=8 N=84 P=2) |
