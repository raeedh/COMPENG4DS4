#include <px4_platform_common/px4_config.h>
#include <px4_platform_common/log.h>

#include <drivers/drv_hrt.h>
#include <uORB/Publication.hpp>
#include <uORB/topics/test_motor.h>
#include <uORB/topics/rc_channels.h>


#define DC_MOTOR 0
#define SERVO_MOTOR 1

extern "C" __EXPORT int hello_world_main(int argc, char *argv[]);

int hello_world_main(int argc, char *argv[])
{
	px4_sleep(2);

    test_motor_s test_motor;
    double motor_value_final = 0; // a number between 0 to 1

    test_motor_s servo_motor;
    double angle_value = 0; // a number between 0 to 1

    double rc_channel_handle;
    double run_direc;
    rc_channels_s rc_channel_data;
    rc_channel_handle = orb_subscribe(ORB_ID(rc_channels));
    orb_set_interval(rc_channel_handle, 500);

    uORB::Publication<test_motor_s> test_motor_pub(ORB_ID(test_motor));

    while (1)
    {
		orb_copy(ORB_ID(rc_channels), rc_channel_handle, &rc_channel_data);

		run_direc = double(rc_channel_data.channels[4]);

		if (run_direc < 0.5){
		motor_value_final = (double(rc_channel_data.channels[3])  + 0.96)/1.96/2.0;
		} else {
		motor_value_final = 0.5 - (double(rc_channel_data.channels[3]) + 0.96)/1.96/2.0;
		}

		angle_value = double(rc_channel_data.channels[1])/2.0 + 0.5;

		PX4_INFO("Motor speed is %f", motor_value_final);
		test_motor.timestamp = hrt_absolute_time();
		test_motor.motor_number = DC_MOTOR;
		test_motor.value = (float)motor_value_final;
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

		px4_usleep(20000);
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
