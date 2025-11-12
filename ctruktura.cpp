#include <iostream>
#include <stdexcept>
#include <cmath>

struct UniformAccelerationMotion
{
    // Расчет конечной скорости: v = v0 + a*t
    static double finalVelocity(double initialVelocity, double acceleration, double time)
    {
        if (time < 0) {
            throw std::invalid_argument("Время не может быть отрицательным");
        }
        return initialVelocity + acceleration * time;
    }

    // Расчет перемещения: s = v0*t + (a*t²)/2
    static double displacement(double initialVelocity, double acceleration, double time)
    {
        if (time < 0) {
            throw std::invalid_argument("Время не может быть отрицательным");
        }
        return initialVelocity * time + (acceleration * time * time) / 2.0;
    }

    // Расчет времени достижения скорости: t = (v - v0)/a
    static double timeToReachVelocity(double initialVelocity, double finalVelocity, double acceleration)
    {
        if (acceleration == 0) {
            throw std::invalid_argument("Ускорение не может быть нулевым");
        }
        double time = (finalVelocity - initialVelocity) / acceleration;
        if (time < 0) {
            throw std::invalid_argument("Невозможно достичь скорости при данных параметрах");
        }
        return time;
    }

    // Расчет ускорения по перемещению: a = 2*(s - v0*t)/t²
    static double accelerationFromDisplacement(double initialVelocity, double displacement, double time)
    {
        if (time <= 0) {
            throw std::invalid_argument("Время должно быть положительным");
        }
        return 2.0 * (displacement - initialVelocity * time) / (time * time);
    }
};

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:


        TEST_METHOD(TestFinalVelocity_ValidInput_ReturnsCorrectValue)
        {
            // Arrange
            double v0 = 5.0;
            double a = 2.0;
            double t = 3.0;
            double expected = 5.0 + 2.0 * 3.0; // = 11.0

            // Act
            double result = UniformAccelerationMotion::finalVelocity(v0, a, t);

            // Assert
            Assert::AreEqual(expected, result, 0.001);
        }

        TEST_METHOD(TestDisplacement_ValidInput_ReturnsCorrectValue)
        {
            // Arrange
            double v0 = 10.0;
            double a = -2.0;
            double t = 2.0;
            double expected = 10.0 * 2.0 + (-2.0) * 2.0 * 2.0 / 2.0; // = 20 - 4 = 16.0

            // Act
            double result = UniformAccelerationMotion::displacement(v0, a, t);

            // Assert
            Assert::AreEqual(expected, result, 0.001);
        }
    }
};