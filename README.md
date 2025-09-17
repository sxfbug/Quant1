# Quant1
我的思路笔记：https://olivine-rainbow-fd2.notion.site/C-MA-2587c8e38f9180e0be2ddf3658947f67?source=copy_link  

文件结构：  
func_declare 函数声明文件  
support 辅助函数  
financial indicators 金融指标，如MA  
strategy 量化策略  
stimulated trading 模拟交易，回测  
evaluate 评估  
main 函数入口  

  
更新日志：  

17/9/2025  
make this code enable to run in Linux-vscode
Future development will based on Linux and vscode  

10/9/2025  
补了之前的更新  
添加full_strategy.cpp，包含高度封装的完整策略  
  
25/8/2025  
添加夏普比率计算  
优化cpp文件结构

  
24/8/2025  
已实现的功能：  
1.逐行读取csv文件并获取date,open,close,high,low等信息。之后可以用模版类进行优化，实现用户自定义内容读取  
2.根据用户的参数i，计算MAi。目前我做的是MA5和MA20  
3.通过shortMA和longMA实现了双均线策略（全仓操作）的交易行为集合，“金叉买入，死叉卖出”  
4.通过交易行为集合进行策略回测，得到账户集合  
5.通过账户集合实现了总收益率、年化收益率、最大回撤的KPI指标
