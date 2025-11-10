#define LEDPIN            4         // 蜂鸣器接到 GPIO4
#define CHANNEL           0         // 使用通道0
#define FREQUENCY         5000      // 基础PWM频率
#define RESOLUTION        10        // 分辨率10位
#define BEATS_PER_MINUTE  115       // 节拍速度

typedef struct {
  uint8_t Solfege;   // 唱名（1-7，对应do-re-mi-fa-so-la-si，0为休止）
  uint8_t Region;    // 音区（0低音，1中音，2高音）
  uint8_t Rhythm;    // 节拍（如16表示16分音符，8表示8分音符）
} MusicNote_TypeDef;

// 🎵 示例旋律：《小星星》
MusicNote_TypeDef song[] = {
  {1, 1, 8}, {1, 1, 8}, {5, 1, 8}, {5, 1, 8},
  {6, 1, 8}, {6, 1, 8}, {5, 1, 4}, {0, 0, 8},
  {4, 1, 8}, {4, 1, 8}, {3, 1, 8}, {3, 1, 8},
  {2, 1, 8}, {2, 1, 8}, {1, 1, 4}, {0, 0, 8}
};

// 🎼 音高表
uint16_t MusicalNote_GetFrequency(MusicNote_TypeDef *MusicNote) {
  uint16_t FREQ[3][8] = {
    {0, 262, 294, 330, 349, 392, 440, 494},     // 低音区
    {0, 523, 587, 659, 698, 784, 880, 988},     // 中音区
    {0, 1046, 1175, 1318, 1397, 1568, 1760, 1976} // 高音区
  };
  return FREQ[MusicNote->Region][MusicNote->Solfege];
}

// 🕒 节拍换算
uint16_t MusicalNote_GetDuration(MusicNote_TypeDef *MusicNote) {
  float s = (MusicNote->Rhythm / 16.0) * (60.0 / BEATS_PER_MINUTE); // 秒
  return (uint16_t)(1000 * s); // 转成毫秒
}

// 🔊 播放单个音符
void playNote(MusicNote_TypeDef *MusicNote) {
  uint16_t duration = MusicalNote_GetDuration(MusicNote);
  uint16_t frequency = MusicalNote_GetFrequency(MusicNote);

  if (MusicNote->Solfege == 0) {
    ledcWriteTone(CHANNEL, 0);  // 休止
    delay(duration);
  } else {
    ledcWriteTone(CHANNEL, frequency); // 发声
    delay(duration);
  }
}

// ⚙️ 初始化
void setup() {
  ledcSetup(CHANNEL, FREQUENCY, RESOLUTION);
  ledcAttachPin(LEDPIN, CHANNEL);
  delay(1000);
}

// 🔁 主循环
void loop() {
  uint8_t len = sizeof(song) / sizeof(MusicNote_TypeDef);
  for (uint8_t i = 0; i < len; i++) {
    playNote(&song[i]);
  }
  delay(2000);
}
