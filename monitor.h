#pragma once

#ifdef __cplusplus
extern "C++" {
#endif

#include <string>
#include <vector>
#include <unordered_map>

enum class VitalType {
    TEMPERATURE,
    PULSE,
    SPO2
};

bool vitalsOk(float temperature, float pulseRate, float spo2);

void showAlert(const std::string& message);

bool isVitalCritical(VitalType type, float value);

std::vector<std::string> getCriticalVitals(float temperature,
                                           float pulse,
                                           float spo2);

#ifdef __cplusplus
}
#endif
