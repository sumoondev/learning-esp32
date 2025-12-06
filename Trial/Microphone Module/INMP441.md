Here is a complete, clean guide for interfacing an **I2S microphone (INMP441, ICS-43434, SPH0645, etc.)** with the **ESP32 DevKit V1**, and a simple test program to verify that it works.

---

# 🎤 **1. I2S Microphone Pinout**

Most I2S microphones have:

| Mic Pin        | Meaning                        |
| -------------- | ------------------------------ |
| **VCC**        | Power (usually 3.3V)           |
| **GND**        | Ground                         |
| **SCK / BCLK** | Bit clock                      |
| **LRCL / WS**  | Word select (left/right clock) |
| **DOUT**       | Digital audio output           |
| **SEL / L/R**  | Select left or right channel   |

For INMP441:

* **L/R = GND → LEFT**
* **L/R = VCC → RIGHT**

I’ll assume LEFT channel (recommended).

---

# 🔌 **2. Wiring I2S Mic to ESP32 DevKit V1**

Use safe pins for I2S (ESP32 supports flexible mapping).

## ✔ Recommended Wiring (Works reliably)

| I2S Mic       | ESP32 Pin |
| ------------- | --------- |
| **VCC**       | 3.3V      |
| **GND**       | GND       |
| **BCLK**      | GPIO 26   |
| **L/R**       | GND       |
| **WS (LRCL)** | GPIO 25   |
| **DOUT**      | GPIO 22   |

These pins avoid ESP32 boot issues and work with Arduino I2S examples.

---

# 📌 **3. ESP32 I2S Microphone Test Code (Working Example)**

This program prints raw audio levels so you can test the microphone easily.

### ▶ Upload → Open Serial Plotter → Observe waveform

(Arduino IDE: **Tools → Serial Plotter**)

---

## ✅ **📄 Code: Basic I2S Audio Level Test**

```cpp
#include <driver/i2s.h>

#define SAMPLE_RATE     44100
#define I2S_WS          25
#define I2S_SD          22
#define I2S_SCK         26

void setup() {
  Serial.begin(115200);
  delay(500);

  // I2S config
  i2s_config_t i2s_config = {
    mode: (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    sample_rate: SAMPLE_RATE,
    bits_per_sample: I2S_BITS_PER_SAMPLE_32BIT,
    channel_format: I2S_CHANNEL_FMT_ONLY_LEFT,
    communication_format: I2S_COMM_FORMAT_I2S,
    intr_alloc_flags: 0,
    dma_buf_count: 8,
    dma_buf_len: 64,
    use_apll: false
  };

  // Pin mapping
  i2s_pin_config_t pin_config = {
    bck_io_num: I2S_SCK,
    ws_io_num: I2S_WS,
    data_out_num: I2S_PIN_NO_CHANGE,
    data_in_num: I2S_SD
  };

  // Install and start I2S driver
  i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_NUM_0, &pin_config);

  Serial.println("I2S Microphone Test Started...");
}

void loop() {
  int32_t sample = 0;
  size_t bytes_read;

  // Read 1 sample (4 bytes) from I2S
  i2s_read(I2S_NUM_0, &sample, sizeof(sample), &bytes_read, portMAX_DELAY);

  // Convert to 16-bit usable audio amplitude
  int16_t audio = sample >> 14;  // scale raw data

  Serial.println(audio);
}
```

---

# 🔍 **4. What You Should See (Serial Plotter)**

* Quiet room: small noisy line
* Clap or speak: big peaks
* Tap mic lightly: large spikes

Works like this:

```
  2000 |          /\     /\
       |         /  \   /  \__  Speaking
       |  __    /    \_/      \_____
       |_/  \__/                     
 -2000 |
```

If the plot reacts to sound, **your I2S microphone works**.

---

# ⚠ Important Notes

### ✔ Power from **3.3V only**

Most I2S mics are not 5V tolerant.

### ✔ Left/right selection

For **INMP441**:

* **L/R to GND → LEFT**
* ESP32 code above expects **LEFT**.

### ✔ Use Serial Plotter (not monitor)

Plotter shows waveform visually.

---

# 🎁 Optional Extras

Tell me if you want:

✅ FFT spectrum analyzer (frequency display)
✅ Real-time dB sound meter
✅ ESP-IDF version
✅ Save audio to SD card as WAV
✅ Stream audio over WiFi

Just say the word!
