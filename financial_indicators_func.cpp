#include <iostream> // ����������ߣ����� cout (������ӡ��Ϣ)
#include <fstream>  // �ļ��������ߣ����� ifstream (������ȡ�ļ�)
#include <sstream>  // �ַ����������ߣ����� stringstream (�����з��ַ���)
#include <vector>   // �������ߣ����� vector (������ܶ�������)
#include <string>   // �ַ�������
#include <iomanip> //��ٷֱ�
#include <cmath> //�������ָ��
#include"func_declare.hpp"

//�����Ӧ��MA
//���������̼�vector��MA��y����ȥy�գ�
//�����double��vector
std::vector<double>get_MA(const std::vector<DailyInfo>& close, int y) {
	std::vector<double> MA;
	double sum = 0.0;
	/*if (close.size() < y) {
		std::cout << "too few arguments in close vector";
		return MA;
	}*/

	//�������ڣ��ȼ���ǰ��y��Ԫ��
	int temp;
	for (int i = 0; i < y && i < close.size(); i++) {
		sum += close[i].close;
		MA.push_back(0.0);
		temp = i;
	}

	//��y+1��Ԫ�ص�MAֵ
	MA.push_back(sum / y);

	//�ӵ�y+2��Ԫ�ؿ�ʼ
	for (int i = y + 1; i < close.size(); i++) {
		sum = sum - close[i - y].close + close[i].close;
		MA.push_back(sum / y);

	}
	return MA;
}
