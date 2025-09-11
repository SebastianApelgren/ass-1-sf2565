import numpy as np
import matplotlib.pyplot as plt

# Load the data from files
h = np.loadtxt("cmake-build-debug/step_sizes.txt")
errors = np.loadtxt("cmake-build-debug/errors.txt")

# Make a log-log plot
plt.figure(figsize=(6, 4))
plt.loglog(h, errors, marker="o", linestyle="-", label="RMS error")

# Add labels and grid
plt.xlabel("Step size h")
plt.ylabel("Error")
plt.title("Convergence of numerical method")
plt.grid(True, which="both", ls="--", alpha=0.7)
plt.legend()

plt.tight_layout()
plt.show()