#pragma once

// -----------------------------
// Vital range check functions
// -----------------------------
bool isTempNormal(float temp);
bool isHeartRateNormal(float heartRate);
bool isOxygenLevelNormal(float spo2);

// -----------------------------
// Top-level vitals check
// -----------------------------
bool checkVitals(float temperature, float heartRate, float spo2);

// -----------------------------
// Alert display
// -----------------------------
void displayAlert(const char* message);
