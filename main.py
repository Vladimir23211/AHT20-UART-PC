# This is a sample Python script.
#import serial


# serialInst = serial.Serial()
# serialInst.baudrate = 115200
# serialInst.port = 'COM7'
# serialInst.open()
# print(serialInst.is_open)
#
# while True:
#     if serialInst.in_waiting > 0:
#         data = serialInst.readline()
#         print(data.decode('utf-8'))

import tkinter as tk
import serial
import threading

# Configure serial connection
serialInst = serial.Serial()
serialInst.baudrate = 115200
serialInst.port = 'COM7'
serialInst.open()


# Function to read serial data
def read_serial():
    while True:
        if serialInst.in_waiting > 0:
            data = serialInst.readline().decode('utf-8').strip()
            if "Temperature" in data and "Humidity" in data:
                temp_str, hum_str = data.split(", ")
                temp = float(temp_str.split(":")[1].strip().replace("C", ""))
                hum = float(hum_str.split(":")[1].strip().replace("%", ""))

                # Update GUI elements
                update_gui(temp, hum)


# Function to update GUI
def update_gui(temp, hum):
    temp_label.config(text=f"{temp:.2f}°C")
    hum_label.config(text=f"{hum:.2f}%")
    temp_bar.config(width=int(temp * 4))
    hum_bar.config(width=int(hum * 4))


# Create the main GUI window
root = tk.Tk()
root.title("Temperature and Humidity Monitor")
root.geometry("400x300")
root.configure(bg="#333")

# Title
title_label = tk.Label(root, text="Environment Monitor", font=("Helvetica", 20), bg="#333", fg="white")
title_label.pack(pady=10)

# Temperature Display
temp_frame = tk.Frame(root, bg="#333")
temp_frame.pack(pady=10)
temp_title = tk.Label(temp_frame, text="Temperature:", font=("Helvetica", 14), bg="#333", fg="white")
temp_title.grid(row=0, column=0, padx=5)
temp_label = tk.Label(temp_frame, text="--°C", font=("Helvetica", 14), bg="#333", fg="red")
temp_label.grid(row=0, column=1)
temp_bar = tk.Canvas(temp_frame, height=20, width=0, bg="red", highlightthickness=0)
temp_bar.grid(row=0, column=2, padx=5)

# Humidity Display
hum_frame = tk.Frame(root, bg="#333")
hum_frame.pack(pady=10)
hum_title = tk.Label(hum_frame, text="Humidity:", font=("Helvetica", 14), bg="#333", fg="white")
hum_title.grid(row=0, column=0, padx=5)
hum_label = tk.Label(hum_frame, text="--%", font=("Helvetica", 14), bg="#333", fg="blue")
hum_label.grid(row=0, column=1)
hum_bar = tk.Canvas(hum_frame, height=20, width=0, bg="blue", highlightthickness=0)
hum_bar.grid(row=0, column=2, padx=5)

# Start serial reading thread
thread = threading.Thread(target=read_serial, daemon=True)
thread.start()

# Run the Tkinter event loop
root.mainloop()
