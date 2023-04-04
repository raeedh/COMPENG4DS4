from pymavlink import mavutil


# Start a connection
the_connection = mavutil.mavlink_connection('/dev/ttyACM0')

# Wait for the first heartbeat
# This sets the system and component ID of remote system for the link
the_connection.wait_heartbeat()
print("Heartbeat from system (system %u component %u)" % (the_connection.target_system, the_connection.target_component))

# Once connected, use ’the_connection’ to get and send messages
while 1:
    msg = the_connection.recv_match(blocking=True)
    # msg = the_connection.recv_match(type='ATTITUDE', blocking=True)
    print(msg)