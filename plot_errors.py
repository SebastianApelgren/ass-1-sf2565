import numpy as np
import matplotlib.pyplot as plt

stepsVec = np.loadtxt("cmake-build-debug/stepsVec.txt")
errors = np.loadtxt("cmake-build-debug/errors.txt")

plt.figure(figsize=(6, 4))
plt.loglog(stepsVec, errors, marker="o", linestyle="-", label="error")

ref_h = stepsVec[0]
ref_e = errors[0]
ref_line = ref_e * (stepsVec / ref_h)**(-2)

plt.loglog(stepsVec, ref_line, "--", label="slope -2")

ref_h_1 = stepsVec[0]
ref_e_1 = errors[0]
ref_line_1 = ref_e_1 * (stepsVec / ref_h_1)**(-1)

plt.loglog(stepsVec, ref_line_1, "--", label="slope -1")

plt.xlabel("M")
plt.ylabel("Error")
plt.title("Convergence of numerical method")
plt.grid(True, which="both", ls="--", alpha=0.7)
plt.legend()
plt.tight_layout()

a = np.loadtxt("cmake-build-debug/aVec.txt")
aErrors = np.loadtxt("cmake-build-debug/aErrors.txt")

plt.figure(figsize=(6, 4))
plt.plot(a, aErrors, marker="o", linestyle="-", label="aErrors")

plt.xlabel("a")
plt.ylabel("error")
plt.title("mean error vs a")
plt.grid(True, which="both", ls="--", alpha=0.7)
plt.legend()
plt.tight_layout()

plt.show()  