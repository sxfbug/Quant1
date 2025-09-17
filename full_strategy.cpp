#include <iostream> // ����������ߣ����� cout (������ӡ��Ϣ)
#include <sstream>  // �ַ����������ߣ����� stringstream (�����з��ַ���)
#include <vector>   // �������ߣ����� vector (������ܶ�������)
#include <string>   // �ַ�������
#include <iomanip> //��ٷֱ�
#include <cmath> //�������ָ��
#include"func_declare.hpp"

//�������ԡ��ز⡢�����ĸ߷�װ�Ȳ��Ժ���

//˫���߲��ԣ�ȫ�ֽ���
int Dual_MA_Strategy_full(const std::vector<DailyInfo>& data,int short_days, 
	int long_days, double base, double handling_Fees,int days,double norisk
	) {
	std::vector <TradeAct>act= Dual_MA_Strategy(short_days,long_days,data);
	std::vector<Account> account = full_position(act, data, base,handling_Fees);
	std::cout << "\nshortMA: " << short_days << "\nlongMA: " << long_days << "\n";
;	evaluate_func(account, base, days, norisk);
    output_account_csv(account, act,short_days,long_days);
return 0;
}