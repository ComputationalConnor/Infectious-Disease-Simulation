# 🦠 Agent-Based Infectious Disease & Mutation Simulation

An agent-based C++ simulation designed to model the epidemiological dynamics of infectious disease transmission, herd immunity thresholds, and evolutionary mutation pressure across a network-structured population.

Built as an exploration of disease transmission mechanics, this application simulates how vaccination rates, contagiousness ($P_{\text{trans}}$), contact networks, and viral mutations interact over time within a matrix-structured population.

---

## 📸 Key Simulation Insights

| 1. Disease Duration vs. Vaccination Rate | 2. Herd Immunity Thresholds | 3. Mutation Pressure & Endemic Survival |
| :--- | :--- | :--- |
| Demonstrates how low-to-mid vaccination rates temporarily lengthen disease duration by creating "transmission mazes" before crashing at herd immunity. | Maps the non-linear, logarithmic relationship between transmission probability and required vaccination rates for 95% protection. | Identifies critical mutation intervals required for viral variants to achieve endemic persistence under varying vaccination coverage. |

---

## 🛠️ Tech Stack & Key Concepts

- **Language & Build System:** C++17, CMake
- **Testing Framework:** Catch2 (unit tests and sanity checks)
- **C++ Concepts & Features:** Object-Oriented Programming (OOP), Custom Vector/Matrix Mapping, Enum Classes, `std::optional`, Parallel/Randomized Index Shuffling
- **Analysis & Visualization:** Python 3 (`matplotlib`)

---

## 🏗️ Architecture & Code Structure

The simulation engine is built around four primary C++ classes working in tandem:
