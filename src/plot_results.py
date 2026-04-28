import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.ticker import ScalarFormatter

try:
    df = pd.read_csv('experiment_results.csv')
except FileNotFoundError:
    print("Erro: O arquivo 'experiment_results.csv' não foi encontrado.")
    exit()

df_avg = df.groupby(['algorithm', 'data_type', 'n'])['time_sec'].mean().reset_index()

fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(16, 8))

trend_colors = {'verificaAlgo': '#ff3333', 'linearSearch': '#3333ff'}

style_map = {
    ('verificaAlgo', 'random'): {'color': '#d62728', 'marker': 'o', 'ls': '-'},
    ('verificaAlgo', 'asc'):    {'color': '#ff7f0e', 'marker': 's', 'ls': '--'},
    ('verificaAlgo', 'desc'):   {'color': '#8c564b', 'marker': '^', 'ls': ':'},
    ('linearSearch', 'random'): {'color': '#1f77b4', 'marker': 'o', 'ls': '-'},
    ('linearSearch', 'asc'):    {'color': '#2ca02c', 'marker': 's', 'ls': '--'},
    ('linearSearch', 'desc'):   {'color': '#9467bd', 'marker': '^', 'ls': ':'}
}

def plot_trendline(ax, x, y, color, algo_name):
    log_x = np.log10(x)
    log_y = np.log10(y)
    
    coeffs = np.polyfit(log_x, log_y, 1)
    slope = coeffs[0]
    
    x_trend = np.linspace(min(x), max(x), 100)
    y_trend = 10**coeffs[1] * (x_trend**slope)
    
    ax.loglog(x_trend, y_trend, color=color, linestyle='--', alpha=0.6, 
              label=f"Tendência {algo_name} (Inclinação: {slope:.2f})")
    return slope

for (algo, dt), style in style_map.items():
    subset = df_avg[(df_avg['algorithm'] == algo) & (df_avg['data_type'] == dt)]
    if not subset.empty:
        ax1.plot(subset['n'], subset['time_sec'], label=f"{algo} ({dt})", 
                 color=style['color'], marker=style['marker'], alpha=0.7)
        
        ax2.loglog(subset['n'], subset['time_sec'], label=f"{algo} ({dt})", 
                   color=style['color'], marker=style['marker'], linestyle='-')

#for algo in ['verificaAlgo', 'linearSearch']:
#    sample = df_avg[(df_avg['algorithm'] == algo) & (df_avg['data_type'] == 'random')]
#    if not sample.empty:
#        plot_trendline(ax2, sample['n'], sample['time_sec'], trend_colors[algo], algo)

ax1.set_title('Escala Linear', fontweight='bold')
ax1.grid(True, ls='--', alpha=0.5)

ax2.set_title('Escala Log-Log', fontweight='bold')
ax2.grid(True, which="both", ls='--', alpha=0.4)
ax2.xaxis.set_major_formatter(ScalarFormatter())
ax2.set_xticks(sorted(df_avg['n'].unique()))

def custom_formatter(x, pos):
    return f'{x:g}' if x >= 0.001 else f'{x:.8f}'.rstrip('0')
ax2.yaxis.set_major_formatter(plt.FuncFormatter(custom_formatter))

plt.suptitle('Análise Comparativa de Desempenho: Escala Linear vs. Log-Log', fontsize=16, y=0.95)
handles, labels = ax2.get_legend_handles_labels()
fig.legend(handles, labels, loc='lower center', ncol=3, fontsize=9)
plt.subplots_adjust(bottom=0.22, top=0.85, wspace=0.25)

plt.show()