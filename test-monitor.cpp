#include <gtest/gtest.h>
#include "./monitor.h"

TEST(Monitor, TemperatureOutOfRange) {
    EXPECT_FALSE(checkVitals(103.0f, 80.0f, 95.0f));
    EXPECT_FALSE(checkVitals(94.0f, 80.0f, 95.0f));
}

TEST(Monitor, PulseRateOutOfRange) {
    EXPECT_FALSE(checkVitals(98.0f, 59.0f, 95.0f));
    EXPECT_FALSE(checkVitals(98.0f, 101.0f, 95.0f));
}

TEST(Monitor, OxygenLevelOutOfRange) {
    EXPECT_FALSE(checkVitals(98.0f, 80.0f, 89.0f));
}

TEST(Monitor, A
