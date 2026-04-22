import matplotlib.pyplot as plt

# 1. Define the Data
vaccination_rates = [0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100]

# Duration data for each probability
duration_p1 = [32.47, 33.28, 34.54, 36.85, 37.27, 39.21, 42.23, 45.03, 46.98, 52.21, 53.25, 60.46, 64.41, 65.66, 68.18, 73.74, 27.72, 11.82, 10.07, 7.87, 0.0]
duration_p2 = [19.75, 20.48, 21.20, 21.87, 22.80, 23.88, 24.8, 26.48, 27.94, 29.61, 31.42, 34.06, 37.35, 39.21, 45.96, 51.93, 57.43, 70.27, 17.73, 9.19, 0.0]
duration_p3 = [15.64, 16.32, 16.65, 17.19, 17.81, 18.64, 19.06, 20.25, 21.23, 22.36, 23.85, 25.4, 27.39, 30.54, 33.85, 39.29, 45.36, 52.74, 58.82, 9.69, 0.0]

# 2. Create the Plot
plt.figure(figsize=(10, 6)) # Set size (width, height)

# Plot each line
plt.plot(vaccination_rates, duration_p1, marker='o', label='P = 0.1')
plt.plot(vaccination_rates, duration_p2, marker='s', label='P = 0.2')
plt.plot(vaccination_rates, duration_p3, marker='^', label='P = 0.3')

# 3. Formatting
plt.title('Vaccination Rate vs. Disease Duration', fontsize=14)
plt.xlabel('Vaccination Rate (%)', fontsize=12)
plt.ylabel('Average Duration (Days)', fontsize=12)
plt.xticks(vaccination_rates, rotation=45) 
plt.grid(True, linestyle='--', alpha=0.7) # Add a light grid
plt.legend(title='Transmission Prob') # Add legend

# 4. Save and Show
plt.tight_layout()
plt.savefig('vaccination_vs_duration_plot.png')
plt.show()
