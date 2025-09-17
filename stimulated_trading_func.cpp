#include <iostream> // ����������ߣ����� cout (������ӡ��Ϣ)
#include <fstream>  // �ļ��������ߣ����� ifstream (������ȡ�ļ�)
#include <sstream>  // �ַ����������ߣ����� stringstream (�����з��ַ���)
#include <vector>   // �������ߣ����� vector (������ܶ�������)
#include <string>   // �ַ�������
#include <iomanip> //��ٷֱ�
#include <cmath> //�������ָ��
#include "func_declare.hpp"







//ģ�⽻�ף�ȫ��
//������������Ϊvector�����ݼ�����ʼ�ʲ���������
//���أ��˻���vector
std::vector<Account> full_position(const std::vector<TradeAct>& act, 
	const std::vector<DailyInfo>& data,double base,double handling_Fees) {
	std::vector<Account> sum;
	Account item;
	item.cash = base;

	//����������Ϊ
	int test = 0;
	for (int i = 0;i<act.size();i++) {
		
		if (act[i].date != data[i].date) {
			std::cout << "���ڲ�ƥ��"<<test<<"\n";
			test++;
		}
		item.date = data[i].date;
		if (act[i].action == TradeAct::action::BUY) {
			item.shares = item.cash / data[i].close;
			item.cash = 0.0;
		}
		else if(act[i].action == TradeAct::action::SELL){
			item.cash = data[i].close * item.shares;
			item.shares = 0.0;
			//������
			item.cash -= handling_Fees * item.cash;
		}
		
		item.total_value = item.cash + item.shares * data[i].close;
		sum.push_back(item);
	}
	return sum;
}


