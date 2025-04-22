#define CATCH_CONFIG_MAIN   // This tells Catch to provide a main() - only do this in one cpp file for multiple test files
#include <catch2/catch.hpp> // Catch2 header-only library
#include "../include/PIDController.hpp"

// TestCase 1 -- Verify the constructor and get functions work correctly.
TEST_CASE("PID Controller Initialization", "[PID]")
{
    PID pid(1.0, 0.1, 0.01); // Example PID gains

    REQUIRE(pid.getKp() == Approx(1.0));
    REQUIRE(pid.getKi() == Approx(0.1));
    REQUIRE(pid.getKd() == Approx(0.01));
}

// TestCase 2 -- Verify the output calculation behavior of the compute() method when given different conditions.
TEST_CASE("PID Compute Output", "[PID]")
{
    PID pid(1.0, 0.1, 0.01);
    pid.setSetpoint(10.0);

    // Test for 0 error
    SECTION("Zero error produces zero output")
    {
        double output = pid.compute(10.0, 0.1);
        // Assertion statement that checks if test fails
        REQUIRE(output == Approx(0.0));
    }

    // Test for positive error
    SECTION("Positive error produces positive output")
    {
        double output = pid.compute(8.0, 0.1);
        REQUIRE(output > 0.0);
    }

    // Test for negative error
    SECTION("Negative error produces negative output")
    {
        double output = pid.compute(12.0, 0.1); // Current value above setpoint
        REQUIRE(output < 0.0);
    }
}

// TestCase 3 -- Ensure the controller respects output limits.
TEST_CASE("PID Integral Windup Prevention", "[PID]")
{
    PID pid(1.0, 0.1, 0.01);
    pid.setSetpoint(10.0);
    pid.setOutputLimits(-5.0, 5.0); // Output limits

    for (int i = 0; i < 100; ++i)
    {
        pid.compute(0.0, 0.1); // Simulate large error over time
    }

    double output = pid.compute(0.0, 0.1);
    REQUIRE(output <= 5.0);
    REQUIRE(output >= -5.0);
}