#include <px4_platform_common/px4_config.h>
#include <px4_platform_common/log.h>

#include <drivers/drv_hrt.h>
#include <uORB/Publication.hpp>
#include <uORB/topics/test_motor.h>
#include <uORB/topics/debug_value.h>

#define DC_MOTOR 0
#define SERVO_MOTOR 1

extern "C" __EXPORT int hello_world_main(int argc, char *argv[]);

int hello_world_main(int argc, char *argv[])
{
    px4_sleep(2);

    debug_value_s debug_data;
    int debug_handle = orb_subscribe(ORB_ID(debug_value));
    orb_set_interval(debug_handle, 500);

    test_motor_s test_motor;
    double motor_value = 0; // a number between 0 to 1

    test_motor_s servo_motor;
    double angle_value = 0.5; // a number between 0 to 1

    uORB::Publication<test_motor_s> test_motor_pub(ORB_ID(test_motor));

    int dist = 0;
    int ret = 0;

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

    while (1)
    {
      orb_copy(ORB_ID(debug_value), debug_handle, &debug_data);

       //get motor and angle values from rc_data
      if (debug_data.ind == 0) dist = debug_data.value;
      if (debug_data.ind == 1) ret = debug_data.value;

      // do something with dist and ret
      if (dist >= 50) {
    	  motor_value = 1;
      } else if ( dist >= 15 && dist < 50 ) {
    	  motor_value = 0.7;
      } else if (dist < 15) {
    	  motor_value = 0.5;
      }

      if (ret == 0) {
    	angle_value = 1;
      } else if(ret == 1){
		 angle_value = 0.5;
	  } else if(ret == 2){
		 angle_value = 0;
	  }

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