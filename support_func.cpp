#include <iostream> // ����������ߣ����� cout (������ӡ��Ϣ)
#include <fstream>  // �ļ��������ߣ����� ifstream (������ȡ�ļ�)
#include <sstream>  // �ַ����������ߣ����� stringstream (�����з��ַ���)
#include <vector>   // �������ߣ����� vector (������ܶ�������)
#include <string>   // �ַ�������
#include <iomanip> //��ٷֱ�
#include <cmath> //�������ָ��
#include "func_declare.hpp"


//������������ȡ��ծʱ�������ַ������ֶ���Ϊ0
double sup_stod(std::string x) {
	if (x == "") {
		return 0.0;
	}
	else {
		return std::stod(x);
	}
}

//��csv�л�ȡ����
std::vector<DailyInfo>load_data_from_csv(const std::string& filename) {
	std::vector<DailyInfo> dataset;

	std::ifstream file(filename);

	if (!file.is_open()) {
		std::cout << "�����޷�������csv�ļ���·�����ܲ���ȷ��" << filename << std::endl;
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


//��csv�л�ȡ������ծ
std::vector<US_Treasury_Yields>load_yields_from_csv(const std::string& filename) {
	std::vector<US_Treasury_Yields> dataset;

	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cout << "�����޷��򿪹�ծ������csv�ļ���·�����ܲ���ȷ��" << filename << std::endl;
		return dataset; // ���ؿ�vector
	}

	//��ȡ��һ�в�����
	std::string line;//����һ��string���͵���ʱ����line
	std::getline(file, line);//�ѵ�һ�����ݶ�ȡ��line��

	while (std::getline(file, line)) {
		US_Treasury_Yields item;

		std::stringstream ss(line);
		std::string token;

		std::getline(ss, item.date, ','); //����

		std::getline(ss, token, ',');        // �ڶ���������һ���ַ������ȷŵ���ʱ token ��
		item.m1 = sup_stod(token);

		std::getline(ss, token, ',');
		item.m3 = sup_stod(token);

		std::getline(ss, token, ',');
		item.m6 = sup_stod(token);

		std::getline(ss, token, ',');
		item.y1 = sup_stod(token);

		std::getline(ss, token, ',');
		item.y2 = sup_stod(token);

		std::getline(ss, token, ',');
		item.y3 = sup_stod(token);

		std::getline(ss, token, ',');
		item.y5 = sup_stod(token);

		std::getline(ss, token, ',');
		item.y7 = sup_stod(token);

		std::getline(ss, token, ',');
		item.y10 = sup_stod(token);

		std::getline(ss, token, ',');
		item.y20 = sup_stod(token);

		std::getline(ss, token, ',');
		item.y30 = sup_stod(token);

		dataset.push_back(item);
	}


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

//ѡ���޷������ʣ����ձ��ʣ���ѡ�����ݵ�һ���10����������ծ����
//��������һ��������ַ�������ծ����vector
//���أ�double������ʣ��������-1��Ϊû�ҵ���Ӧ���ڵ�����
double choose_norisk_rate(std::string finddate, std::vector<US_Treasury_Yields>& yields) {
	for (const auto& i : yields) {
		if (i.date == finddate) {
			return i.y10;
		}
	}
}

//����˻�Ϊcsv
//���룺�˻�vector��������Ϊvector������MA�Ĳ���
//������ޣ����ǻᴴ��һ��csv
void output_account_csv(std::vector<Account>& sum,std::vector<TradeAct>& act,
    int short_days,int long_days) {
    std::string filename = "Data/Analysis/backtest_result_" + std::to_string(short_days) + "and" + std::to_string(long_days)+".csv";
	std::ofstream output(filename);
	output << "date,total_value,action,price\n";
    for (size_t i = 0; i < sum.size(); ++i) {
        output << sum[i].date << ","
            << sum[i].total_value << ","
            << (i < act.size() ? static_cast<int>(act[i].action) : -1) << ","
            << (i < act.size() ? act[i].close : 0) << "\n";
    }
    output.close();


}
