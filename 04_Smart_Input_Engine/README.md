# 04\_Smart\_Button — Single Button FSM / Tek Buton Durum Makinesi

> 🇬🇧 [English](#english) | 🇹🇷 [Türkçe](#türkçe)

---

## English

This project implements a software debounce and short/long press detection system for a single button, controlling 5 LEDs through 5 animation modes — all without a single `HAL_Delay` in the main loop.

### 💬 What I Learned

> *I have realized that the HAL_Delay() function, which I used for delay control in previous projects, locks the processor for the specified duration—a practice that is strictly undesirable in the world of embedded software. Considering scenarios where the processor must handle multiple tasks simultaneously, it is clear how such a hardware-locking function can degrade system performance and efficiency. Instead of locking the hardware, I learned to manage software delays using the HAL_GetTick() function, which acts like a stopwatch starting from the moment the system boots. For instance, by calculating the difference between the time a button press is detected and the time 50ms later, I can guarantee that the button state is filtered from mechanical noise (debounce).*

> *I have also been introduced to FSM (Finite State Machine) design. Since the primary goal of this project was managing software debounce, I utilized AI assistance for specific parts of the logic. While I understand the code line-by-line, I believe true mastery of FSM requires writing several implementations from scratch by hand.*

> *Despite being new to FSM, I have gained insight into the concept of "State Leak." I learned that if variables are not reset during state transitions, the next state might inherit stale values from the previous one, leading to logical errors and preventing the system from functioning correctly.*

### 🎯 Goals

- Replace blocking `HAL_Delay` debounce with a proper FSM-based approach.
- Implement non-blocking LED animations using `HAL_GetTick()` delta timing.
- Distinguish between short press (cycle modes) and long press (reset to ALL\_OFF).
- Understand edge detection and state leak prevention in bare-metal C.

### 🕹️ How It Works

A single button drives the entire system through two layers:

**Button FSM** — 4-state machine handling debounce and press classification:

| State | Description |
| :--- | :--- |
| `BTN_IDLE` | Waiting for input |
| `BTN_DEBOUNCE` | Signal detected — waiting 50 ms to confirm |
| `BTN_PRESSED` | Confirmed press — watching for release or 3s timeout |
| `BTN_WAIT_RELEASE` | Long press fired — waiting for finger off before re-arming |

**Short press** → cycles through LED modes (0 → 1 → 2 → 3 → 4 → 0 …)

**Long press (3 s)** → forces `ALL_OFF` regardless of current mode

**Animation Engine** — each mode runs non-blocking via `HAL_GetTick()` delta checks:

| # | Mode | Timing |
| :--- | :--- | :--- |
| 0 | ALL\_OFF | Immediate |
| 1 | ALL\_ON | Immediate |
| 2 | ALL\_TOGGLE | Every 200 ms |
| 3 | KNIGHT\_RIDER | Every 100 ms per step |
| 4 | RANDOM | Every 150 ms |

### 🔧 Wiring

| ST-Link V2 | Blackpill |
| :--- | :--- |
| 3.3V | 3.3V |
| GND | GND |
| SWDIO | SWDIO |
| SWCLK | SWCLK |

GPIO assignments are configured in CubeMX — see `gpio.c` for pin details.

### 💻 Tools Used

| Tool | Detail |
| :--- | :--- |
| **Language** | C |
| **Framework** | STM32 HAL |
| **Build System** | Makefile |
| **Flash Tool** | st-flash v1.7.0 |
| **System Clock** | 84 MHz (HSI, PLL: M=8 N=84 P=2) |

### 🔍 Key Concepts

- **FSM debounce** — `BTN_IDLE → BTN_DEBOUNCE → BTN_PRESSED → BTN_WAIT_RELEASE`
- **Non-blocking timing** — `if (HAL_GetTick() - lastTick >= period)` pattern throughout
- **Edge detection** — reaction fires on the falling edge, not while held
- **State leak prevention** — `animStep = 0` on every mode transition
- **Modular counter** — `(currentMode + 1) % 5` wraps cleanly without conditionals

---

## Türkçe

Bu proje, tek bir buton için yazılımsal debounce ve kısa/uzun basış tespiti uygular. Tek bir `HAL_Delay` kullanmadan, `HAL_GetTick()` tabanlı zamanlama ile 5 LED'i 5 farklı animasyon modunda yönetir.

### 💬 Öğrendiklerim

> *Önceki projelerde gecikme kontrolü için kullandığım HAL_Delay() fonksiyonunun, belirtilen süre boyunca işlemciyi kilitlediğini ve bu yaklaşımın gömülü yazılım dünyasında kesinlikle istenmeyen bir durum olduğunu öğrendim. İşlemcinin aynı anda birden fazla görev yapması gerektiği durumları düşündüğümüzde, kodun içinde kullandığımız ve donanımı tamamen kilitleyen bu fonksiyonun sistemin performansını ve verimliliğini ne kadar düşürebileceğini anlayabiliriz. Bu fonksiyon yerine, sistem başladığı andan itibaren çalışan bir kronometre gibi düşünülebilecek sistem saatinin o anki değerini getiren HAL_GetTick() fonksiyonunu kullanarak, donanımı kilitlemek yerine yazılımsal olarak gecikmeleri yönetmeyi öğrendim. Örneğin bir butona basıldığı anda alınan zaman verisi ve 50ms sonra alınan zaman verisi arasındaki farkı kontrol ederek butona basılma durumunun gürültülerden etkilenmemesini garanti altına almış oldum.*

> *FSM yani Finite State Machine konusuna da giriş yapıp durum makinesi yazmayla ilgili de ön bilgi edindim. Bu projede asıl amacım software debounce yönetimi olduğu için kodun o kısımlarında yapay zekadan yardım aldım. Neyin nasıl çalıştığının satır satır anlamış olmamla birlikte, kendi elimle birkaç kez FSM yazmadan bu konuyu tam olarak öğrendiğimi söyleyemeyeceğim.*

> *FSM çalışmamış olmama rağmen ön bilgi olarak "State Leak" konusunda fikir sahibi oldum. State'ler arası geçişlerde değişkenlerin resetlenmediği durumlarda diğer durumların başlangıç değeri olarak önceki durumdan kalan değişkenleri kullanacağnı ve bunun da doğru çalışmayı engelleyeceğini öğrendim. (Durum sızıntısı)*

### 🎯 Hedefler

- Bloklayıcı `HAL_Delay` debounce'ı doğru bir FSM yaklaşımıyla değiştirmek.
- `HAL_GetTick()` delta zamanlamasıyla non-blocking LED animasyonları uygulamak.
- Kısa basış (mod ilerleme) ile uzun basışı (ALL\_OFF'a sıfırlama) ayırt etmek.
- Bare-metal C'de kenar tespiti ve state leak önlemeyi anlamak.

### 🕹️ Nasıl Çalışır?

Tek buton, iki katmanlı bir yapıyla tüm sistemi yönetir:

**Buton FSM** — debounce ve basış sınıflandırmasını yöneten 4 durumlu makine:

| Durum | Açıklama |
| :--- | :--- |
| `BTN_IDLE` | Girdi bekleniyor |
| `BTN_DEBOUNCE` | Sinyal tespit edildi — 50 ms onay bekleniyor |
| `BTN_PRESSED` | Basış onaylandı — bırakma veya 3 sn zaman aşımı izleniyor |
| `BTN_WAIT_RELEASE` | Uzun basış tetiklendi — yeniden etkinleşmeden önce bırakma bekleniyor |

**Kısa basış** → LED modunu döngüsel olarak ilerletir (0 → 1 → 2 → 3 → 4 → 0 …)

**Uzun basış (3 sn)** → hangi modda olursa olsun `ALL_OFF`'a geçer

**Animasyon Motoru** — her mod, `HAL_GetTick()` delta kontrolü ile non-blocking çalışır:

| # | Mod | Zamanlama |
| :--- | :--- | :--- |
| 0 | ALL\_OFF | Anlık |
| 1 | ALL\_ON | Anlık |
| 2 | ALL\_TOGGLE | Her 200 ms |
| 3 | KNIGHT\_RIDER | Her 100 ms'de bir adım |
| 4 | RANDOM | Her 150 ms |

### 🔧 Bağlantı Şeması

| ST-Link V2 | Blackpill |
| :--- | :--- |
| 3.3V | 3.3V |
| GND | GND |
| SWDIO | SWDIO |
| SWCLK | SWCLK |

GPIO atamaları CubeMX'te yapılandırılmıştır — detaylar için `gpio.c` dosyasına bakın.

### 💻 Kullanılan Araçlar

| Araç | Detay |
| :--- | :--- |
| **Dil** | C |
| **Framework** | STM32 HAL |
| **Build System** | Makefile |
| **Flash Tool** | st-flash v1.7.0 |
| **Sistem Saati** | 84 MHz (HSI, PLL: M=8 N=84 P=2) |

### 🔍 Temel Kavramlar

- **FSM debounce** — `BTN_IDLE → BTN_DEBOUNCE → BTN_PRESSED → BTN_WAIT_RELEASE`
- **Non-blocking zamanlama** — her yerde `if (HAL_GetTick() - lastTick >= period)` deseni
- **Kenar tespiti (edge detection)** — tepki düşen kenarda tetiklenir, basılı tutma değil
- **State leak önleme** — her mod geçişinde `animStep = 0`
- **Modüler sayaç** — `(currentMode + 1) % 5` koşulsuz sarmalama
