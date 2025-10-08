#include "./monitor.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <vector>

using namespace std::chrono_literals;
using std::cout, std::flush, std::string, std::vector;

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
    for (int i = 0; i < 6; ++i) {
        cout << "\r* " << flush;
        std::this_thread::sleep_for(1s);
        cout << "\r *" << flush;
        std::this_thread::sleep_for(1s);
    }
}

// ============================
// Pure functional logic
// ============================
bool isVitalCritical(VitalType type, float value) {
    const auto& t = thresholds.at(type);
    return value < t.low || value > t.high;
}

// This function is pure: only computes results
std::vector<std::string> getCriticalVitals(float temperature, float pulse, float spo2) {
    std::vector<std::string> alerts;

    if (isVitalCritical(VitalType::TEMPERATURE, temperature))
        alerts.push_back("Temperature is critical!");
    if (isVitalCritical(VitalType::PULSE, pulse))
        alerts.push_back("Pulse Rate is out of range!");
    if (isVitalCritical(VitalType::SPO2, spo2))
        alerts.push_back("Oxygen Saturation is out of range!");

    return alerts;
}

// ============================
// Top-level function with I/O
// ============================
bool vitalsOk(float temperature, float pulseRate, float spo2) {
    auto alerts = getCriticalVitals(temperature, pulseRate, spo2);

    for (const auto& msg : alerts)
        showAlert(msg);

    return alerts.empty();
}
