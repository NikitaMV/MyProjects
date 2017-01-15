/* ������: �������� ��������� ������������� �������������� ��������� ����.
�������� � ��������������� ����������� �� 30 � 15 ��������� ��������������.

�����: ������ ������ */


#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
using namespace std;

double a = 0.0283;			//�������� ���� �������� 					

double test_function(double x)		//������� ��� �������������
{
	double result;
	double a=7;
	double b=7;
	double d=0.4;

	result = a*sin(b*x) + d;

	return result;
}

double neural_function(double y1, double y2, double y3, double w1, double w2, double w3, double T)  //�������� ������� ��������� ��������� ����
{
	double result = y1*w1 + y2*w2 + y3*w3 - T;
	return result;
}

double calculate_error(double actual, double etalon)			//������������������ ������ ����
{
	double result = (actual - etalon)*(actual - etalon) / 2;
	return result;
}

double change_W(double W0, double y, double actual, double etalon, double a)  //������� ��������� ����� ��������� ����
{
	double result = W0 - a*(actual - etalon)*y;
	return result;
}

double change_T(double T0, double actual, double etalon, double a)   //������� ��������� ������ ��������� ����
{
	double result = T0 + a*(actual - etalon);
	return result;
}


int main()
{
	setlocale(LC_ALL, "russian");

	ofstream fout("output.txt");	
	
	double Em = 0.001;		//�������� ��������� ������������ ������ ����

	double x[45], y[45];

	for (int i = 0; i < 45; i++)
		x[i] = i*0.1;

	for (int i = 0; i < 45; i++)
		y[i] = test_function(x[i]);

	double w1 = 0.1, w2 = 0.2, w3 = 0.3, T = 0.4, E;
	int number_of_iterations = 0;

	while (true)
	{
		number_of_iterations++;

		if (number_of_iterations > 1000)
		{
			cout << "���������� �������� ��������� ����������� ����������. �������������� ����� �� �����" << endl<<endl;
			break;
		}

		double NeuralValue;		
		E = 0;

		for (int i = 0; i < 27; i++)
		{
			NeuralValue = neural_function(y[i], y[i + 1], y[i + 2], w1, w2, w3, T);
			E += calculate_error(NeuralValue, y[i + 3]);
		}		

		if ((E - Em) < 0.00000001)
		{
			cout << "����� ��������: " << number_of_iterations << endl;
			fout << "����� ��������: " << number_of_iterations << endl;
			break;
		}

		for (int i = 0; i < 27; i++)
		{
			NeuralValue = neural_function(y[i], y[i + 1], y[i + 2], w1, w2, w3, T);					

			w1 = change_W(w1, y[i], NeuralValue, y[i + 3], a);				//�������� ��������� ���� - ��������� �������������
			w2 = change_W(w2, y[i + 1], NeuralValue, y[i + 3], a);
			w3 = change_W(w3, y[i + 2], NeuralValue, y[i + 3], a);
			T = change_T(T, NeuralValue, y[i + 3], a);
		}

	}	
	
	cout << "������������ ������ ����: " << E << endl;
	fout << "������������ ������ ����: " << E << endl;

	cout << "w1: " << w1 << "\tw2: " << w2 << "\tw3: " << w3 << "\tT: " << T << endl << endl;
	fout << "w1: " << w1 << "\tw2: " << w2 << "\tw3: " << w3 << "\tT: " << T << endl << endl;

	cout << "���������������:" << endl;
	fout << "���������������:" << endl;

	for (int i = 27; i <= 41; i++)			//��������������� �������� ������������ ������� � ������� ��������� ��������� ����
	{
		double result = neural_function(y[i], y[i + 1], y[i + 2], w1, w2, w3, T);
		cout << "�������� ����: " << result << "\t" << "������: " << y[i + 3] << "  \t������: " << abs(result - y[i + 3]) << endl;
		fout << "�������� ����: " << result << "\t" << "������: " << y[i + 3] << "  \t������: " << abs(result - y[i + 3]) << endl;		
	}

	return 0;
}