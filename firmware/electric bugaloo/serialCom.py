import serial
import time



if __name__ == '__main__':
    
    # Communication protocol: send over an individual command for each "device" connected to Tiva
    # Format is 'device_id device_type param1 param2;' 
    # device_type isn't working rn
    # semicolon (;) termination is vital

    #example command packet for 4 motors
    com_packet = ['0 m 20000 1;',
                '1 m 20001 2;',
                '2 m 20002 3;',
                '3 m 20003 4;']

    stop_packet = [
                '0 m 0 1;',
                '1 m 0 2;',
                '2 m 0 3;',
                '3 m 0 4;']

    # Spin up the Serial Port
    tiva = serial.Serial()
    tiva.baudrate = 115200
    tiva.port = 'COM20'
    tiva.timeout = 1



    start_time = time.time()


    tiva.open()

    for i in range(100):
        # Print out what its sending at the start
        outstring = str(i) + ": " + str(com_packet[0])
        print(outstring)

        # Block progress with timeouts, In future, should do try-catch for failure states
        tiva.timeout = None
        print(tiva.readline().decode('utf-8'));

        
        tiva.timeout = None

        #send over each command in command packet
        for cmd in com_packet:

            # Write to uart
            tiva.write(cmd.encode('utf-8'))
            print(cmd);
            tiva.flush()
            # Print back and block for receipt
            print("received:")
            print(tiva.readline().decode('utf-8'))
        
    #Check time
    end_time = time.time()

    outstring = "Time: " + str(end_time - start_time)
    print(outstring)

    #Close the serial port
    tiva.close()

