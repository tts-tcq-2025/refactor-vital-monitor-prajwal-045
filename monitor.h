#pragma once
#include <string>
#include <vector>
#include <unordered_map>

enum class VitalType {
    TEMPERATURE,
    PULSE,
    SPO2
};

bool vitalsOk(float temperature, float pulseRate, float spo2);

// I/O function
void showAlert(const std::string& message);

// Pure logic
bool isVitalCritical(VitalType type, float value);
std::vector<std::string> getCriticalVitals(float temperature, float pulse, float spo2);
