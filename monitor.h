#pragma once

#include <string>
#include <vector>
#include <unordered_map>

// -----------------------------
// Vital types
// -----------------------------
enum class VitalType {
  TEMPERATURE,
  PULSE,
  SPO2
};

// -----------------------------
// Top-level function
// -----------------------------
bool vitalsOk(float temperature, float pulseRate, float spo2);

// -----------------------------
// I/O function
// -----------------------------
void showAlert(const std::string& message);

// -----------------------------
// Pure logic functions
// -----------------------------
bool isVitalCritical(VitalType type, float value);
