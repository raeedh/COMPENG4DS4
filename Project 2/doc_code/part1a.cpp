#include <px4_platform_common/px4_config.h>
#include <px4_platform_common/log.h>

#include <drivers/drv_hrt.h>
#include <uORB/Publication.hpp>
#include <uORB/topics/test_motor.h>
#include <uORB/topics/sensor_combined.h>
#include <uORB/topics/input_rc.h>

#define DC_MOTOR 0
#define SERVO_MOTOR 1

extern "C" __EXPORT int hello_world_main(int argc, char *argv[]);

int hello_world_main(int argc, char *argv[])
{
    test_motor_s test_motor;
    double motor_value = 0; // a number between 0 to 1
    uORB::Publication<test_motor_s> test_motor_pub(ORB_ID(test_motor));

    test_motor_s servo_motor;
    double angle_value = 0; // a number between 0 to 1
    uORB::Publication<test_motor_s> servo_motor_pub(ORB_ID(servo_motor));

    while (1)
    {
        PX4_INFO("Enter speed value (0 to 1) and servo value (0 to 1). If you enter a value outside the range, the motor and servo will be stopped and the application will be terminated.");
        scanf("%lf %lf", &motor_value, &angle_value);
        if(motor_value > 1.0 || motor_value < 0)
            break;
        if(angle_value > 1.0 || angle_value < 0)
            break;

        PX4_INFO("Motor speed is %f", motor_value);
        test_motor.timestamp = hrt_absolute_time();
        test_motor.motor_number = DC_MOTOR;
        test_motor.value = (float)motor_value;
        test_motor.action = test_motor_s::ACTION_RUN;
        test_motor.driver_instance = 0;
        test_motor.timeout_ms = 0;

        test_motor_pub.publish(test_motor);

        PX4_INFO("Servo angle is %f", angle_value);
        servo_motor.timestamp = hrt_absolute_time();
        servo_motor.motor_number = SERVO_MOTOR;
        servo_motor.value = (float)angle_value;
        servo_motor.action = test_motor_s::ACTION_RUN;
        servo_motor.driver_instance = 0;
        servo_motor.timeout_ms = 0;

        servo_motor_pub.publish(servo_motor);
    }

    PX4_INFO("The motor will be stopped");
    test_motor.timestamp = hrt_absolute_time();
    test_motor.motor_number = DC_MOTOR;
    test_motor.value = 0.5;
    test_motor.driver_instance = 0;
    test_motor.timeout_ms = 0;

    test_motor_pub.publish(test_motor);

    PX4_INFO("The servo motor will be stopped");
    servo_motor.timestamp = hrt_absolute_time();
    servo_motor.motor_number = SERVO_MOTOR;
    servo_motor.value = 0.5;
    servo_motor.driver_instance = 0;
    servo_motor.timeout_ms = 0;

    servo_motor_pub.publish(servo_motor);

    return 0;
}