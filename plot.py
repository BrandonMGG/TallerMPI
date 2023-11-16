import re
import matplotlib.pyplot as plt

# Function to extract message size and execution time from a line
def extract_info(line):
    size_match = re.search(r'Message Size: (\d+)', line)
    time_match = re.search(r'Execution Time: (\d+\.\d+)', line)
    
    if size_match and time_match:
        message_size = int(size_match.group(1))
        execution_time = float(time_match.group(1))
        return message_size, execution_time
    else:
        return None

# Read data from the file and extract information
file_path = 'output.txt'  # Replace with the actual path to your file
message_sizes = []
execution_times = []

with open(file_path, 'r') as file:
    for line in file:
        info = extract_info(line)
        if info:
            message_size, execution_time = info
            message_sizes.append(message_size)
            execution_times.append(execution_time)

# Plotting
plt.plot(message_sizes, execution_times, marker='o', linestyle='-', color='b')
plt.xlabel('Message Size')
plt.ylabel('Execution Time (seconds)')
plt.title('Message Size vs. Execution Time')
plt.grid(True)
plt.savefig('outputplot.png')