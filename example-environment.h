struct Network {
  const char* ssid;
  const char* password;
};

struct Button {
  const String title;
  const uint8_t pin;
};

const Network network_credentials[] = {
  { "YOUR_SSID_1", "YOUR_PASSWORD_1" },
  { "YOUR_SSID_2", "YOUR_PASSWORD_2" },
};

const Button buttons[] = {
  { "power", D1 },
  { "speed", D2 },
  { "mode", D3 },
  { "eco", D4 },
  { "time", D5 },
  { "up", D6 },
  { "down", D7 },
};
