import matplotlib.pyplot as plt

# 1. Your Data
transmission_probs = [0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 
                      0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95]

required_vax_rates = [57.0, 76.5, 84.5, 88.0, 90.0, 92.0, 92.5, 93.5, 94.0, 94.5, 
                      95.0, 95.5, 96.0, 96.0, 96.5, 96.5, 97.0, 97.0, 97.0]

# 2. Setup Plot
plt.figure(figsize=(10, 6))

# 3. Draw Line
# marker='o' puts dots on the data points
# linewidth=2 makes the line thick and visible
plt.plot(transmission_probs, required_vax_rates, marker='o', linestyle='-', color='#1f77b4', linewidth=2)

# 4. Labels and Title
plt.title('Herd Immunity Threshold vs. Disease Contagiousness', fontsize=14)
plt.xlabel('Transmission Probability (P)', fontsize=12)
plt.ylabel('Required Vaccination Rate (%)', fontsize=12)

# 5. Grid and Limits
plt.grid(True, linestyle='--', alpha=0.6) # Light grid lines
plt.ylim(50, 105) # Start Y-axis at 50% so the curve looks dramatic
plt.xlim(0, 1.05)

# 6. Save
plt.tight_layout()
plt.savefig('herd_immunity_curve.png')
plt.show()
