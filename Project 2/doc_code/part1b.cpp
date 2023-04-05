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
    int rc_combined_handle;
	input_rc_s rc_data;

	rc_combined_handle = orb_subscribe(ORB_ID(input_rc));
	orb_set_interval(rc_combined_handle, 200);

    test_motor_s test_motor;
    double motor_value = 0; // a number between 0 to 1

    test_motor_s servo_motor;
    double angle_value = 0; // a number between 0 to 1

    uORB::Publication<test_motor_s> test_motor_pub(ORB_ID(test_motor));

    while (1)
    {
        orb_copy(ORB_ID(input_rc), rc_combined_handle, &rc_data);
        // get motor and angle values from rc_data
        // motor_value = rc_data.
        // angle_value = rc_data.

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

        test_motor_pub.publish(servo_motor);

        px4_usleep(200000);
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

    test_motor_pub.publish(servo_motor);

    return 0;
}