import subprocess
import random
import matplotlib.pyplot as plt

# List of n values (you can modify these as needed)
N_VALUES = list(range(10, 300011, 30000))
print(N_VALUES)
num_trials = 5

# Dictionary to store T values for each n
T_values = {n: [] for n in N_VALUES}

# Loop over each value of n and run the experiment num_trials times
for n in N_VALUES:
    for trial in range(num_trials):
        # Generate n random points and write to input.txt
        with open("input.txt", "w") as infile:
            infile.write(f"{n}\n")
            for _ in range(n):
                # Generate random integers in range 0 to 1000 (modify range if needed)
                x = random.randint(0, 1000)
                y = random.randint(0, 1000)
                infile.write(f"{x} {y}\n")
        
        # Run the compiled C++ executable (it will read input.txt and write T.txt)
        run_result = subprocess.run(["./code"])
        if run_result.returncode != 0:
            raise RuntimeError("Execution of code failed.")
        
        # Read the T value from T.txt
        with open("T.txt", "r") as t_file:
            T_val = int(t_file.read().strip())
        T_values[n].append(T_val)
        print(f"n={n}, trial={trial+1}, T={T_val}")

# Calculate average T for each n
avg_T = [sum(T_values[n]) / len(T_values[n]) for n in N_VALUES]

# Plot the results: n on the x-axis and average T on the y-axis
plt.figure(figsize=(10, 8))
plt.plot(N_VALUES, avg_T, marker='o', linestyle='-')
plt.xlabel("Number of Points (n)")
plt.ylabel("Average T")
plt.title("Relationship between n and T")
plt.savefig("plot.png")