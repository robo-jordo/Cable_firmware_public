import serial
import time
import re

class SerialCOm(object):
    def __init__(self,port):
        # Spin up the Serial Port
        self.tiva = serial.Serial()
        self.tiva.baudrate = 230400#1843200#115200
        self.tiva.port = port
        self.tiva.timeout = 1
        self.tiva.open()
        self.lastFb = 0
        self.fb =0
        self.fbs = [0,0,0,0]

    def writeData(self,cmd):
        # Write to uart
        self.tiva.write(cmd.encode('utf-8'))
        print("sending:",cmd)
        self.tiva.flush()
        # Print back and block for receipt
        msg = self.tiva.readline().decode('utf-8')
        print("sent:",msg)

    def writeDataPack(self,com_packet):
        #send over each command in command packet
        self.waitWriting()
        #should have some caculation here
        for cmd in com_packet:
            self.writeData(cmd)
        return self.fb

    def waitWriting(self):
        self.tiva.timeout = None
        line = self.tiva.readline().decode('utf-8')
        print("waiting:",line)
        self.lastFb =self.fb
        floatList = re.findall(r"[-+]?\d*\.\d+|\d+", line)
        if(len(floatList) !=0 and "IC" in line):
            self.fb=floatList[1]
            self.fbs[int(floatList[0])] = floatList[1]
        else:
            self.fb = self.lastFb
        self.tiva.timeout = None

    def sendStopCommand(self):
        stop_packet = [
            '0 m 0 1;',
            '1 m 0 1;',
            '2 m 0 1;',
            '3 m 0 1;',
            '4 e 0 0;']
        self.writeDataPack(stop_packet)

def testGood():
    # Communication protocol: send over an individual command for each "device" connected to Tiva
    # Format is 'device_id device_type param1 param2;'
    # device_type isn't working rn
    # semicolon (;) termination is vital

    # example command packet for 4 motors
    com_packet = ['0 m 20000 0;',
                  '1 m 20000 0;',
                  '2 m 20000 0;',
                  '3 m 20000 0;']

    stop_packet = [
        '0 m 0 1;',
        '1 m 0 1;',
        '2 m 0 1;',
        '3 m 0 1;']

    # Spin up the Serial Port
    tiva = serial.Serial()
    tiva.baudrate = 115200
    tiva.port = 'COM11'
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

        # send over each command in command packet
        for cmd in com_packet:
            # Write to uart
            tiva.write(cmd.encode('utf-8'))
            print(cmd);
            tiva.flush()
            # Print back and block for receipt
            print("received:")
            print(tiva.readline().decode('utf-8'))

    # Check time
    end_time = time.time()

    outstring = "Time: " + str(end_time - start_time)
    print(outstring)
    # Close the serial port
    tiva.close()

def test():
    # Spin up the Serial Port
    tiva = serial.Serial()
    tiva.baudrate = 115200
    tiva.port = 'COM12'
    tiva.timeout = 1
    start_time = time.time()
    tiva.open()
    while(True):
        tiva.write("test\n".encode('utf-8'))


if __name__ == '__main__':
    # test()
    tivaSerial = SerialCOm("COM13")#10
    com_packet = [
                 '0 m 10000 1;',
                '1 m 30000 1;',
                 # '2 m 40000 1;',
                 # '3 m 20000 1;',
                '4 e 1 0;'
                #'5 m 0IC;'
    ]
    startTime = time.time()

    for i in range(50):
        id = str(i%4)
        # com_packet[1] = "5 m "+id+"IC;"
        fb = tivaSerial.writeDataPack(com_packet)
        print("feedback:",fb)
        print()
    com_packet = [
                 '0 m 10000 1;',
                '1 m 30000 1;',
                 # '2 m 40000 1;',
                 # '3 m 20000 1;',
                '4 e 0 0;'
                #'5 m 0IC;'
    ]
    for i in range(50):
        id = str(i%4)
        # com_packet[1] = "5 m "+id+"IC;"
        fb = tivaSerial.writeDataPack(com_packet)
        print("feedback:",fb)
        print()

    tivaSerial.sendStopCommand()
    endTime = time.time()
    print("time:",endTime-startTime)
    print("motor currents:",tivaSerial.fbs)

