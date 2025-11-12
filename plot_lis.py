import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('data/timings_lis.csv')
g = df.groupby('n')['time_ms'].median().reset_index()

plt.figure()
plt.plot(g['n'], g['time_ms'], marker='o')
plt.xlabel('Размер массива n')
plt.ylabel('Время выполнения (мс)')
plt.title('Зависимость времени работы LIS от размера входных данных')
plt.grid(True)
plt.tight_layout()
plt.savefig('data/lis_time.png')
plt.show()