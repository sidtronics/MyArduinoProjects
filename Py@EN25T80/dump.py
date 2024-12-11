import serial4wire as sw

flash = sw.SerialDevice("/dev/ttyACM0")
flash.stb(False)
flash.send(0x03)
flash.send(0x00)
flash.send(0x00)
flash.send(0x00)

numbers = []

for i in range(0, 8192):
    numbers += flash.recv(128)

flash.stb(True)

# Sry was too lazy to implement following trivial code myself..

# GPT:
# Convert each number to its hex representation
hex_numbers = [format(number, "02x") for number in numbers]

# Define the number of bytes per line
bytes_per_line = 256

# Create lines with the specified number of bytes
lines = []
for i in range(0, len(hex_numbers), bytes_per_line):
    line = " ".join(hex_numbers[i: i + bytes_per_line])
    lines.append(line)

# Join lines with newline characters
hex_output = "\n".join(lines)

# Write the hex output to a file
with open("hex_dump.txt", "w") as file:
    file.write(hex_output)

print("Hex output written to file.")
