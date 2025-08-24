#include <iostream> // ����������ߣ����� cout (������ӡ��Ϣ)
#include <fstream>  // �ļ��������ߣ����� ifstream (������ȡ�ļ�)
#include <sstream>  // �ַ��������ߣ����� stringstream (�����з��ַ���)
#include <vector>   // �������ߣ����� vector (������ܶ�������)
#include <string>   // �ַ�������
#include<iomanip > //��ٷֱ�
#include<cmath> //�������ָ��
#include"func_declare.hpp"



//
std::vector<DailyInfo>load_from_csv(const std::string& filename) {
	std::vector<DailyInfo> dataset;

	std::ifstream file(filename);

	if (!file.is_open()) {
		std::cout << "�����޷����ļ���·�����ܲ���ȷ��" << filename << std::endl;
		return dataset; // ���ؿ�vector
	}
	//��ȡ��һ�в�����
	std::string line;//����һ��string���͵���ʱ����line
	std::getline(file, line);//�ѵ�һ�����ݶ�ȡ��line��

	//ѭ����ȡֱ��ĩβ
	while (std::getline(file, line)) {
		DailyInfo item;
		//������ĩβʱ��line���ж�������line����ss
		//stringstream��������ļ���һ�������ַ�����
		// �������ǰ��ָ����������Ƕ��ţ��ָ��ַ�����
		// �൱�ڰ�һ���ı����һ�� �����и������Դ��
		std::stringstream ss(line);
		std::string token;
		// 4.3 ��ʼ���вˡ��������ŷָ��ַ���
		// ��ʽ�ǣ�����,���̼�,��߼�,��ͼ�,���̼�,�ɽ���
		std::getline(ss, item.date, ',');    // ��һ�����������ڣ��ŵ���Ƭ��date��
		std::getline(ss, token, ',');        // �ڶ���������һ���ַ��������̼ۣ����ȷŵ���ʱ token ��
		item.open = std::stod(token);        //         ������ַ���ת���� double ���֣��ٷŵ���Ƭ��open��

		std::getline(ss, token, ',');        // �����������£���߼ۣ�
		item.high = std::stod(token);        //         ת������� high

		std::getline(ss, token, ',');        // ���ĵ������£���ͼۣ�
		item.low = std::stod(token);         //         ת������� low

		std::getline(ss, token, ',');        // ���嵶�����£����̼ۣ�
		item.close = std::stod(token);       //         ת������� close

		std::getline(ss, token, ',');        // �����������£��ɽ�����
		item.volume = std::stoll(token);     //         ת���� long long ���֣����� volume

		// 4.4 ���ſ�Ƭ����ˣ������Ž������
		dataset.push_back(item);
	}

	// 5. �����������رջ����ᣬ����װ����Ƭ�Ĵ���
	file.close();
	return dataset;
	}



//�������е����̼�
//���������ݼ�
//�����double��vector
std::vector<double>get_sum_close(const std::vector<DailyInfo>& data) {
	std::vector<double> sum;
	for (const auto& d : data) {
		sum.push_back(d.close);
	}
	return sum;
}

//�����Ӧ��MA
//���������̼�vector��MA��y����ȥy�գ�
//�����double��vector
std::vector<double>get_MA(const std::vector<double>& close, int y) {
	std::vector<double> MA;
	double sum = 0.0;
	/*if (close.size() < y) {
		std::cout << "too few arguments in close vector";
		return MA;
	}*/
	//�������ڣ��ȼ���ǰ��y��Ԫ��
	int temp;
	for (int i = 0; i < y && i < close.size(); i++) {
		sum += close[i];
		MA.push_back(0.0);
		temp = i;
	}
	
	//��y+1��Ԫ�ص�MAֵ
	MA.push_back(sum / y);

	//�ӵ�y+2��Ԫ�ؿ�ʼ
	for (int i = y+1; i < close.size(); i++) {
		sum = sum - close[i - y] + close[i];
		MA.push_back(sum/y);
		if (i == 10407) {
			std::cout << i << std::endl;
		}
	}
	return MA;
}


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
	while (longMA[idx]==0)
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

//ģ�⽻��
//������������Ϊvector�����ݼ�����ʼ�ʲ���������
//���أ��˻���vector
std::vector<Account> simulated_trading(const std::vector<TradeAct>& act, 
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

//������Ч

//��������
double total_return(const std::vector<Account>&sum,double base) {
	double ratio = (sum[sum.size() - 1].total_value - base) / base;
	std::cout << std::fixed << std::setprecision(5) << ratio << "%" << std::endl;
	return ratio;
}

//�껯������
double annualized_rate_of_return(const std::vector<Account>&sum, double base) {
	double times = sum[sum.size() - 1].total_value / base;
	int start_year = std::stoi(sum[0].date.substr(sum[0].date.rfind("/") + 1, 4));
	int end_year= std::stoi(sum[sum.size() - 1].date.substr(sum[sum.size() - 1].date.rfind("/") + 1, 4));
	double annual_rate = std::pow(times, 1.0 / (end_year-start_year)) - 1;

	return annual_rate;
}


//���س�
//���룺�˻�vector��ÿ������
//���أ�double��ʽ�����س�ֵ
//�ۼƾ�ֵ��ȡ�˻����ʲ�
double max_drawdown(const std::vector<Account> &sum) {
	double peak = -1.0;
	double min_drawdown = 0.0;
	double current_drawdown = -1.0;
	for (auto i=sum.begin();i!=sum.end();i++) {
		//�ж��Ƿ���·�ֵ
		if (i->total_value > peak) {
			//���·�ֵ
			peak = i->total_value;
		}
		//�ж��Ƿ�������س�
		current_drawdown= (i->total_value - peak) / peak;
		if (current_drawdown < min_drawdown) {
			min_drawdown = current_drawdown;
		}
		

	}
	return min_drawdown;
}



