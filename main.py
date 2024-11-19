import pandas as pd
import matplotlib.pyplot as plt

# Загрузка данных
data = pd.read_csv("monte_carlo_results.csv")

# График 1: Изменение приближённого значения площади
plt.figure(figsize=(10, 5))
plt.plot(data["Points"], data["EstimatedArea"], label="Estimated Area", color="blue")
plt.axhline(y=0.44380799999999998, color="red", linestyle="--", label="Exact Area")
plt.title("Estimated Area vs Number of Points")
plt.xlabel("Number of Points")
plt.ylabel("Area")
plt.legend()
plt.grid()
plt.savefig("area_estimation.png")

# График 2: Относительное отклонение
plt.figure(figsize=(10, 5))
plt.plot(data["Points"], data["RelativeError"], label="Relative Error (%)", color="green")
plt.title("Relative Error vs Number of Points")
plt.xlabel("Number of Points")
plt.ylabel("Relative Error (%)")
plt.legend()
plt.grid()
plt.savefig("relative_error.png")

plt.show()
