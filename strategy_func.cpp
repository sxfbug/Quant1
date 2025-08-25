#include <iostream> // ����������ߣ����� cout (������ӡ��Ϣ)
#include <fstream>  // �ļ��������ߣ����� ifstream (������ȡ�ļ�)
#include <sstream>  // �ַ��������ߣ����� stringstream (�����з��ַ���)
#include <vector>   // �������ߣ����� vector (������ܶ�������)
#include <string>   // �ַ�������
#include<iomanip > //��ٷֱ�
#include<cmath> //�������ָ��
#include"func_declare.hpp"

//���ԣ�������룬��������
//������shortMA,longMA�����ݼ�?
//���أ�������Ϊvector
std::vector<TradeAct> Strategy1(const std::vector<double>& shortMA, const std::vector<double>& longMA,
	const std::vector<DailyInfo> data) {

	//������Ϊvector
	std::vector<TradeAct> act;

	//״̬�������жϵ�ǰ�ֲ�״̬������Ҫhold����Ϊhold is not actionable
	bool isHolding = false;
	int idx = 0;

	//û�г��ھ��ߣ�������Ƚ�����
	while (longMA[idx] == 0)
	{
		TradeAct item;

		item.date = data[idx].date;
		item.close = data[idx].close;
		item.action = TradeAct::HOLD;
		act.push_back(item);
		idx++;
	}



	for (int i = idx; i < longMA.size(); i++) {

		TradeAct item;
		//���ھ�������ͻ�Ƴ��ھ��ߣ��γɽ�棬��δ����ʱ����
		if (shortMA[i] > longMA[i] && shortMA[i - 1] <= longMA[i - 1] && !isHolding) {

			item.date = data[i].date;
			item.close = data[i].close;
			item.action = TradeAct::BUY;
			act.push_back(item);
			isHolding = true;
		}
		//���ھ�������ͻ�Ƴ��ھ��ߣ��γ����棬�ҳ���ʱ����
		else if (shortMA[i] < longMA[i] && shortMA[i - 1] >= longMA[i - 1] && isHolding) {
			item.date = data[i].date;
			item.close = data[i].close;
			item.action = TradeAct::SELL;
			act.push_back(item);
			isHolding = false;
		}
		else {
			item.date = data[i].date;
			item.close = data[i].close;
			item.action = TradeAct::HOLD;
			act.push_back(item);
		}



	}
	return act;
}
