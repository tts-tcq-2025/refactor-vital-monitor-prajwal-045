#include <gtest/gtest.h>
#include "./monitor.h"

TEST(Monitor, DetectsCriticalTemperature) {
    EXPECT_TRUE(isVitalCritical(VitalType::TEMPERATURE, 94.0f));
    EXPECT_TRUE(isVitalCritical(VitalType::TEMPERATURE, 103.0f));
    EXPECT_FALSE(isVitalCritical(VitalType::TEMPERATURE, 98.0f));
}

TEST(Monitor, DetectsCriticalPulseRate) {
    EXPECT_TRUE(isVitalCritical(VitalType::PULSE, 50.0f));
    EXPECT_TRUE(isVitalCritical(VitalType::PULSE, 110.0f));
    EXPECT_FALSE(isVitalCritical(VitalType::PULSE, 80.0f));
}

TEST(Monitor, DetectsCriticalSpo2) {
    EXPECT_TRUE(isVitalCritical(VitalType::SPO2, 85.0f));
    EXPECT_FALSE(isVitalCritical(VitalType::SPO2, 95.0f));
}

TEST(Monitor, ReportsMultipleCriticalVitals) {
    auto alerts = getCriticalVitals(104.0f, 55.0f, 85.0f);
    EXPECT_EQ(alerts.size(), 3);
}

TEST(Monitor, AllVitalsOkReturnsTrue) {
    EXPECT_TRUE(vitalsOk(98.0f, 75.0f, 97.0f));
}

TEST(Monitor, AnyCriticalReturnsFalse) {
    EXPECT_FALSE(vitalsOk(104.0f, 80.0f, 96.0f));
    EXPECT_FALSE(vitalsOk(98.0f, 105.0f, 98.0f));
    EXPECT_FALSE(vitalsOk(97.0f, 70.0f, 88.0f));
}



