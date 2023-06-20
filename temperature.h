#define TEMPERATURE_PIN A0

// The last 2.5 seconds of sensed temperature values.
float temperature_history[5] = {21.0, 21.0, 21.0, 21.0, 21.0};

/**
 * Push a value to the history.
 */
void addToHistory(float value) {
    temperature_history[4] = temperature_history[3];
    temperature_history[3] = temperature_history[2];
    temperature_history[2] = temperature_history[1];
    temperature_history[1] = temperature_history[0];
    temperature_history[0] = value;
}

/**
 * Probe the current temperature value in celsius, and add it to the history.
 */
void probeTemperature() {
  float value = (analogRead(TEMPERATURE_PIN) * (3300 / 1024));
  
  // Degress = ((voltage) - 500mV) x 100)
  value = (value - 500) / 10;
  
  addToHistory(value);
}

/**
 * Get the average temperature within the last few seconds.
 */
int getTemperature() {
  float sum = 0.0;
  for (int i = 0 ; i < 5 ; i++) sum += temperature_history[i];
  return round(sum / 5.0);
}

/**
 * Handle the probing of the temperature every 500ms.
 */
void handleTemperatureProbe() {
    static int check = 0;
    int now = millis();
    if (now >= check) {
        probeTemperature();
        check = now + 500;
    }
}
