import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# ��ȡ����
data = pd.read_csv('backtest_results.csv')
data['date'] = pd.to_datetime(data['date'])

# ����ͼ��
fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(12, 10))

# �����ʲ�����
ax1.plot(data['date'], data['total_value'])
ax1.set_title('Portfolio Value Over Time')
ax1.set_ylabel('Portfolio Value')

# ���������
buy_signals = data[data['action'] == 0]  # ����0��������
sell_signals = data[data['action'] == 1] # ����1��������

ax1.scatter(buy_signals['date'], buy_signals['total_value'], 
           color='green', marker='^', s=100, label='Buy')
ax1.scatter(sell_signals['date'], sell_signals['total_value'], 
           color='red', marker='v', s=100, label='Sell')
ax1.legend()

# ���ƻس�����
peak = data['total_value'].cummax()
drawdown = (data['total_value'] - peak) / peak
ax2.plot(data['date'], drawdown)
ax2.set_title('Drawdown Curve')
ax2.set_ylabel('Drawdown')
ax2.set_xlabel('Date')

plt.tight_layout()
plt.savefig('backtest_analysis.png', dpi=300)
plt.show()