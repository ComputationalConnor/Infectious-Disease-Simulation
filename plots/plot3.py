import matplotlib.pyplot as plt

# 1. Data
vaccination_rates = list(range(5, 105, 5)) # 5, 10, ... 100

# Data for P=0.1
thresholds_p1 = [
    9400, 8900, 8350, 7850, 7300, 6800, 6250, 5650, 5050, 4450, 
    3850, 3150, 2400, 1550, 650, 0, 0, 0, 0, 0
]

# Data for P=0.2
thresholds_p2 = [
    9450, 8950, 8450, 7950, 7450, 6950, 6450, 5950, 5450, 4950, 
    4400, 3900, 3300, 2750, 2100, 1400, 550, 0, 0, 0
]

# Data for P=0.3
thresholds_p3 = [
    9450, 8950, 8450, 7950, 7450, 6950, 6450, 5950, 5450, 4950, 
    4450, 3950, 3450, 2900, 2350, 1750, 1100, 300, 0, 0
]

# 2. Plotting
plt.figure(figsize=(10, 6))

plt.plot(vaccination_rates, thresholds_p1, marker='o', label='P = 0.1')
plt.plot(vaccination_rates, thresholds_p2, marker='s', label='P = 0.2')
plt.plot(vaccination_rates, thresholds_p3, marker='^', label='P = 0.3')

# 3. Formatting
plt.title('Vaccination vs. Mutation Speed', fontsize=14)
plt.xlabel('Vaccination Rate (%)', fontsize=12)
plt.ylabel('Max Mutation Interval (Transmissions)', fontsize=12)
plt.grid(True, linestyle='--', alpha=0.7)
plt.legend(title='Transmission Probability')

# Optional: Add an annotation explaining the Y-axis
plt.text(5, 1000, 'Lower Y = Faster Mutation Required', fontsize=10, 
         bbox=dict(facecolor='white', alpha=0.8))

# 4. Save and Show
plt.tight_layout()
plt.savefig('mutation_vaccination_plot.png')
plt.show()
