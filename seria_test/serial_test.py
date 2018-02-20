import serial

ser = serial.Serial('USB\VID_03EB&PID_2157&MI_01\6&33263669&0&0001',9600)
s = [0]
while True:
	read_serial=ser.readline()
	s[0] = str(int (ser.readline(),16))
	print(s[0])
	print(read_serial)
