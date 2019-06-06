#include <pigpio.h>
#include <iostream>

using namespace std;


// pin sterujacy serwem
const int servoPin = 25;

// parametry pracy PWM
const int pwmFrequency = 50;
const int pwmRange = 1000;

// zakres pracy serwa
const double minPwm = 2.3; // 2.3% PWM -> wychylenie serwa 0 %
const double maxPwm = 12.5; // 12.5% PWM -> wychylenie serwa 100 %


void initaliseServo()
{
    gpioSetPWMfrequency(servoPin, pwmFrequency);
    gpioSetPWMrange(servoPin, pwmRange);

    cout << "Servo PWM range: <" << minPwm << ", " << maxPwm << "> [%]" << endl;
}

/**
 * @brief setServo porusza serwem
 * @param anglePercent from 0 to 100
 */
void setServo(double anglePercent)
{
    double pwmPercent = (maxPwm - minPwm) * (0.01 * anglePercent) + minPwm; // % PWM
    double pwmValue = (0.01 * pwmPercent) * pwmRange; // wartosc dla PWM

    gpioPWM(servoPin, (int)pwmValue);

    cout << "Servo PWM value: " << pwmPercent << " [%]" << endl;
}

int main()
{
    if(gpioInitialise() < 0)
        cout << "Initialisation error." << endl;

    else
    {
        initaliseServo();

        cout << "Type negative angle to break program." << endl;

        while(true)
        {
            double anglePercent;

            cout << "Angle <0, 100> [%]: ";
            cin >> anglePercent;

            if(anglePercent < 0.0)
                break;

            if(anglePercent > 100.0)
                anglePercent = 100.0;

            setServo(anglePercent);
        }

        gpioTerminate();
    }

    return 0;
}
