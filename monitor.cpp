#include "./monitor.h"
#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <string>
using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

constexpr float TEMP_LOW = 95.0f;
constexpr float TEMP_HIGH = 102.0f;
constexpr int PULSE_LOW = 60;
constexpr int PULSE_HIGH = 100;
constexpr int SPO2_LOW = 90;

void showAlert(const std::string& message) {
    cout << message << '\n';
    for (int i = 0; i < 6; i++) {
        cout << "\r* " << flush;
        sleep_for(seconds(1));
        cout << "\r *" << flush;
        sleep_for(seconds(1));
    }
}

bool isTemperatureCritical(float temperature) {
    return temperature < TEMP_LOW || temperature > TEMP_HIGH;
}

bool isPulseRateCritical(float pulseRate) {
    return pulseRate < PULSE_LOW || pulseRate > PULSE_HIGH;
}

bool isSpo2Critical(float spo2) {
    return spo2 < SPO2_LOW;
}

struct VitalCheck {
    bool (*check)(float);
    const char* message;
};

int vitalsOk(float temperature, float pulseRate, float spo2) {
    VitalCheck checks[] = {
        { isTemperatureCritical, "Temperature is critical!" },
        { isPulseRateCritical,   "Pulse Rate is out of range!" },
        { isSpo2Critical,        "Oxygen Saturation out of range!" }
    };

    float values[] = { temperature, pulseRate, spo2 };

    for (size_t i = 0; i < 3; ++i) {
        if (checks[i].check(values[i])) {
            showAlert(checks[i].message);
            return 0;
        }
    }

    return 1;
}
