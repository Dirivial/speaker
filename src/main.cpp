#include <Arduino.h>
#include "BluetoothA2DPSink.h"
#include "driver/i2s.h"

// We will use the sink (ESP32 receives audio from phone)
BluetoothA2DPSink a2dp_sink;

// Use internal DAC on GPIO25 / GPIO26 (mono mix to both)
void setup() {
  Serial.begin(115200);
  delay(1000);

  // I2S config for internal DAC
  i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX | I2S_MODE_DAC_BUILT_IN),
    .sample_rate = 44100,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
    .communication_format = I2S_COMM_FORMAT_I2S_MSB,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 8,
    .dma_buf_len = 64,
    .use_apll = false,
    .tx_desc_auto_clear = true,
    .fixed_mclk = 0
  };

  // Use I2S0 with internal DAC
  a2dp_sink.set_i2s_port(I2S_NUM_0);
  a2dp_sink.set_i2s_config(i2s_config);

  // Start Bluetooth A2DP sink
  a2dp_sink.set_volume(127);                 // 0–127
  a2dp_sink.start("ESP32-BT-Speaker");

  // Enable both internal DAC channels (GPIO25 & GPIO26)
  i2s_set_dac_mode(I2S_DAC_CHANNEL_BOTH_EN);

  Serial.println("A2DP sink started");
}

void loop() {
  // nothing needed; A2DP runs in background
}


