import serial
import serial.tools.list_ports

import keyboard

import matplotlib.pyplot as plt

arduino = ""

for port, desc, hwid in sorted(serial.tools.list_ports.comports()):
        if "Arduino" in desc:
            print("Found an arduino on port: " + port)
            arduino = port

if arduino == "":
    print("No arduino found")
    exit()

ser = serial.Serial(port, 115200)

print("Connected")
print("Press enter to start the test")

# Print out the incoming data while also waiting for a key to be pressed
keyPressed = False
while not keyPressed:
    if ser.in_waiting > 0:
        print(ser.readline().decode("utf-8")[:-2])
    if keyboard.is_pressed("enter"):
        keyPressed = True

ser.write(b"Start")

completedData=[]

while True:
    data = ser.readline().decode("utf-8")[:-2]
    if data == "Done":
        break

    print("Data received: ", data)

    if data == "":
        continue
    elif "," not in data:
        continue
    
    seperated_data = data.split(",")
    completedData.append(seperated_data)

    print("Data received: ", data)

ser.close()
print("Connection closed, all data has been received. Plotting data. This may take a while")

with open("data.txt", "w") as file:
    for data in completedData:
        file.write(str(data) + "\n")

plt.style.use('default')

time = [int(x[2]) / 1000 for x in completedData]
temperature = [float(x[0]) for x in completedData]
target_temperature = [float(x[1]) for x in completedData]

plt.plot(time, temperature, label="Temperature")
plt.plot(time, target_temperature, label="Target Temperature")

plt.xlabel("Time (s)")
plt.ylabel("Temperature (°C)")
plt.title("Temperature over time")
plt.legend()

plt.show()