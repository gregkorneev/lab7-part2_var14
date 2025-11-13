import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("data/timings_lis.csv")

# медиана времени по каждому n и методу
g = df.groupby(["method", "n"])["time_ms"].median().reset_index()

plt.figure()
for m in ["bruteforce", "dp"]:
    part = g[g["method"] == m].sort_values("n")
    if len(part) > 0:
        plt.plot(part["n"], part["time_ms"], marker="o", label=m)

plt.xlabel("Размер массива n")
plt.ylabel("Время (мс)")
plt.title("Сравнение методов LIS")
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.savefig("data/lis_time.png")
plt.close()
