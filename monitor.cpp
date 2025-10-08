#include "./monitor.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using std::cout;
using std::string;
using std::vector;

// ============================
// Configurable thresholds
// ============================
struct VitalThreshold {
    float low;
    float high;
};

// Thresholds for various vitals
static const std::unordered_map<VitalType, VitalThreshold> thresholds = {
    { VitalType::TEMPERATURE, {95.0f, 102.0f} },
    { VitalType::PULSE,       {60.0f, 100.0f} },
    { VitalType::SPO2,        {90.0f, 100.0f} }
};

// ============================
// I/O separation (side effect)
// ============================
void showAlert(const std::string& message) {
    cout << message << '\n';
}

// ============================
// Pure functional logic
// ============================
bool isVitalCritical(VitalType type, float value) {
    const auto& t = thresholds.at(type);
    return value < t.low || value > t.high;
}

std::vector<std::string> getCriticalVitals(float temperature, float pulse, float spo2) {
    struct VitalInfo {
        VitalType type;
        float value;
        const char* message;
    };

    const VitalInfo vitalChecks[] = {
        { VitalType::TEMPERATURE, temperature, "Temperature is critical!" },
        { VitalType::PULSE,       pulse,       "Pulse Rate is out of range!" },
        { VitalType::SPO2,        spo2,        "Oxygen Saturation is out of range!" }
    };

    std::vector<std::string> alerts;
    alerts.reserve(3);

    for (const auto& v : vitalChecks) {
        if (isVitalCritical(v.type, v.value)) {
            alerts.emplace_back(v.message);
        }
    }

    return alerts;
}

// ============================
// Top-level function with I/O
// ============================
bool vitalsOk(float temperature, float pulseRate, float spo2) {
    const auto alerts = getCriticalVitals(temperature, pulseRate, spo2);

    for (const auto& msg : alerts) {
        showAlert(msg);
    }

    return alerts.empty();
}
