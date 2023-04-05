#include <px4_platform_common/px4_config.h>
#include <px4_platform_common/log.h>

#include <uORB/topics/sensor_combined.h>
#include <uORB/topics/input_rc.h>

extern "C" __EXPORT int hello_world_main(int argc, char *argv[]);

int hello_world_main(int argc, char *argv[])
{
    int rc_combined_handle;
	input_rc_s rc_data;

	rc_combined_handle = orb_subscribe(ORB_ID(input_rc));
	orb_set_interval(rc_combined_handle, 200);

    while (1)
    {
        orb_copy(ORB_ID(input_rc), rc_combined_handle, &rc_data);
    
        // Change to RC values
        PX4_INFO("header = %f, ch1 = %f, ch2 = %f, ch3 = %f, ch4 = %f, ch5 = %f, ch6 = %f, ch7 = %f, ch8 = %f",
                 (double)rc_data.values[0],
                 (double)rc_data.values[1],
                 (double)rc_data.values[2],
                 (double)rc_data.values[3],
                 (double)rc_data.values[4],
                 (double)rc_data.values[5],
                 (double)rc_data.values[6],
                 (double)rc_data.values[7],
                 (double)rc_data.values[8]);

        px4_usleep(200000);
    }

    return 0;
}