#include <px4_platform_common/px4_config.h>
#include <px4_platform_common/log.h>

#include <uORB/topics/rc_channels.h>

extern "C" __EXPORT int hello_world_main(int argc, char *argv[]);

int hello_world_main(int argc, char *argv[])
{
	double rc_channel_handle;
	rc_channels_s rc_channel_data;
	rc_channel_handle = orb_subscribe(ORB_ID(rc_channels));
	orb_set_interval(rc_channel_handle, 500);

	while (1)
	{
		orb_copy(ORB_ID(rc_channels), rc_channel_handle, &rc_channel_data);

		PX4_INFO("header = %f, ch1 = %f, ch2 = %f, ch3 = %f, ch4 = %f, ch5 = %f, ch6 = %f, ch7 = %f, ch8 = %f",
				double(rc_channel_data.channels[0]),
				double(rc_channel_data.channels[1]),
				double(rc_channel_data.channels[2]),
				double(rc_channel_data.channels[3]),
				double(rc_channel_data.channels[4]),
				double(rc_channel_data.channels[5]),
				double(rc_channel_data.channels[6]),
				double(rc_channel_data.channels[7]),
				double(rc_channel_data.channels[8]));

		px4_usleep(200000);
	}

	return 0;
}
