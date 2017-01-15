/*
������:
�������� ��������� �� �++ � STL, ������� ������ ��������� ����,
������� �������� ����� � ������ ������, ��������� ����������� ������ ��� ����� �������� ��������
� ��������� � ����� ����. ��������� ������ ���� ������� ����-�������.
��� ������ ������������ googletest. 

�����: ������ ������
����������: ��������� ������������� ��� ������ � ���������� �������
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <gtest/gtest.h>

using namespace std;

bool compare_strings_case_insensitive(const string& lhs, const string& rhs)	//������� ��� ��������� ����� ��� ����� ��������
{
	string lhcLower(lhs);
	string rhcLower(rhs);
	transform(lhs.begin(), lhs.end(), lhcLower.begin(), ::tolower);
	transform(rhs.begin(), rhs.end(), rhcLower.begin(), ::tolower);
	return lhcLower < rhcLower;
}


string delete_word_from_str(string line, string word)	//������� ��� �������� ���������� ����� �� ������
{
	string symbols = ".,!?\t ";		// �������, ������� ����� ���� ����� �����(����� �������� ����� ������ � �������� ������)
	string symbols2 = " \t";		// �������, ������� ����� ���� ����� ������

	int pos = 0;	/*������� ������ � ������. ���� � ������ ����� ������� ��������� ����, ����� ������� ����� 
					����� �������������� �� � ������ ������, � � �������� �������*/
	int n;			//���������� ��� ���������� �������, � �������� ���������� ��������� �����

	bool word_is_deleted;   //���� ����� true, ���� ��������� ����� ������� �� ������   
	bool correct_symbols_before_word;    //���� ����� true, ���� ����� ��������� ������ ������ ���������� �������(������, ���� ���������)

	while (true)		//���� ����� ��� �������� �� ������, � ���������� ���������� ���� � ������
	{
		correct_symbols_before_word = true;
		word_is_deleted = false;

		n = line.find(word, pos);	//����� ����� � ������� pos � ������
		if (n == -1)				//����� �� �������
			break;

		if (n != 0)		//�����������, ���� ��������� ����� ������������� �� � ������ ������
		{
			char symbol_before_word = line.at(n - 1);		//������ ����� ������
			if (symbols2.find(symbol_before_word) == -1)
			{
				correct_symbols_before_word = false;
			}
		}

		if (correct_symbols_before_word)
		{
			if (line.length() == n + word.length())		//�����������, ���� ����� ������� � ����� ������
			{
				line.erase(n, word.length());		//�������� �����
				word_is_deleted = true;
			}

			else
			{
				char symbol_after_word = line.at(n + word.length());	//������ ����� �����
				if (symbols.find(symbol_after_word) != -1)				//�������� �� ���������� ������ ����� �����
				{
					line.erase(n, word.length());
					word_is_deleted = true;
				}
			}
		}

		if (word_is_deleted)
		{
			pos++;
		}
		else
			pos = pos + 1 + word.length();		//���� ����� �� �������, �� ���� ��� ��������� ������� �����, ���������� 
												//���������� ������� �� ����� �����+1
	}

	return line;
}





TEST(MyTest1, Testing_Deletion_Of_Word) 
{

	string checked_string = "abc word1 abc";
	string word = "word1";
	char* expected_result = "abc  abc";
	string actual_result = delete_word_from_str(checked_string, word);

	char * actual_result_str = new char[];
	strcpy(actual_result_str, actual_result.c_str());

	ASSERT_STREQ(expected_result, actual_result_str);	//��������� ���������� ���������� � ���������� ������ �������

}

TEST(MyTest2, Testing_Deletion_Of_Part_Of_Word)
{

	string checked_string = "abc word1 abc";
	string word = "word";
	char* expected_result = "abc word1 abc";
	string actual_result = delete_word_from_str(checked_string, word);

	char * actual_result_str = new char[];
	strcpy(actual_result_str, actual_result.c_str());

	ASSERT_STREQ(expected_result, actual_result_str);
}

TEST(MyTest3, Testing_Deletion_Of_Word_Ended_By_Comma) 
{

	string checked_string = "abc word, abc";
	string word = "word";
	char* expected_result = "abc , abc";
	string actual_result = delete_word_from_str(checked_string, word);

	char * actual_result_str = new char[];
	strcpy(actual_result_str, actual_result.c_str());

	ASSERT_STREQ(expected_result, actual_result_str);
}

TEST(MyTest4, Testing_Deletion_Of_Word_Ended_By_Point)
{

	string checked_string = "abc word. abc";
	string word = "word";
	char* expected_result = "abc . abc";
	string actual_result = delete_word_from_str(checked_string, word);

	char * actual_result_str = new char[];
	strcpy(actual_result_str, actual_result.c_str());

	ASSERT_STREQ(expected_result, actual_result_str);
}

TEST(MyTest5, Testing_Deletion_Of_Word_Ended_By_Exclamation_Point) 
{

	string checked_string = "abc word! abc";
	string word = "word";
	char* expected_result = "abc ! abc";
	string actual_result = delete_word_from_str(checked_string, word);

	char * actual_result_str = new char[];
	strcpy(actual_result_str, actual_result.c_str());

	ASSERT_STREQ(expected_result, actual_result_str);
}

TEST(MyTest6, Testing_Deletion_Of_Word_Ended_By_Interrogation_Point)
{

	string checked_string = "abc word? abc";
	string word = "word";
	char* expected_result = "abc ? abc";
	string actual_result = delete_word_from_str(checked_string, word);

	char * actual_result_str = new char[];
	strcpy(actual_result_str, actual_result.c_str());

	ASSERT_STREQ(expected_result, actual_result_str);
}

TEST(MyTest7, Testing_Deletion_Of_Part_Of_Word) 
{

	string checked_string = "abc xword? abc";
	string word = "word";
	char* expected_result = "abc xword? abc";
	string actual_result = delete_word_from_str(checked_string, word);

	char * actual_result_str = new char[];
	strcpy(actual_result_str, actual_result.c_str());

	ASSERT_STREQ(expected_result, actual_result_str);
}

TEST(MyTest8, Testing_Deletion_Of_Word_In_The_Beginning_Of_The_String)
{

	string checked_string = "word abc";
	string word = "word";
	char* expected_result = " abc";
	string actual_result = delete_word_from_str(checked_string, word);

	char * actual_result_str = new char[];
	strcpy(actual_result_str, actual_result.c_str());

	ASSERT_STREQ(expected_result, actual_result_str);
}

TEST(MyTest9, Testing_Deletion_Of_Word_At_The_End_Of_The_String) 
{

	string checked_string = "abc word";
	string word = "word";
	char* expected_result = "abc ";
	string actual_result = delete_word_from_str(checked_string, word);

	char * actual_result_str = new char[];
	strcpy(actual_result_str, actual_result.c_str());

	ASSERT_STREQ(expected_result, actual_result_str);
}

TEST(MyTest10, Testing_Deletion_Of_Several_Words) 
{

	string checked_string = "abc word ABC word";
	string word = "word";
	char* expected_result = "abc  ABC ";
	string actual_result = delete_word_from_str(checked_string, word);

	char * actual_result_str = new char[];
	strcpy(actual_result_str, actual_result.c_str());

	ASSERT_STREQ(expected_result, actual_result_str);
}


TEST(MyTest11, Testing_Sort_Of_Strings)
{

	ifstream fin("input1.txt");	

	if (!fin)
	{
		cout << "File input1.txt is not found" << endl;
		FAIL();
	}
	
	ofstream fout("output1.txt");

	string line;			//����������� �� ����� ������
	vector<string> vec;		//���������, ���������� ������

	string word = "word";		//�����, ������� ���� ������� �� �����

	while (!fin.eof())
	{
		getline(fin, line);
		line = delete_word_from_str(line, word);
		vec.push_back(line);
	}

	sort(vec.begin(), vec.end(), compare_strings_case_insensitive);	//���������� �����

	vector<string>::const_iterator i;
	for (i = vec.begin(); i != vec.end() - 1; i++)
	{
		fout << *i << endl;			//����� ����� � ����
	}

	fout << *i;



	fin.close();		//�������� ������
	fout.close();


	ifstream read_actual_result("output1.txt");	

	if (!read_actual_result)
	{
		cout << "File output1.txt is not found" << endl;
		FAIL();
	}
	
	ifstream read_expected_result("expected_result_1.txt");

	if (!read_expected_result)
	{
		cout << "File expected_result_1.txt is not found" << endl;
		read_actual_result.close();
		FAIL();
	}

	string line1, line2;

	while (true)
	{
		if (read_actual_result.eof() && read_expected_result.eof())			//�������� ���������� ����� 
		{
			read_actual_result.close();
			read_expected_result.close();
			break;
		}

		if (read_actual_result.eof() && !read_expected_result.eof() || !read_actual_result.eof() && read_expected_result.eof())
		{
			read_actual_result.close();
			read_expected_result.close();
			FAIL() << "Numbers of strings in two files are not equal" << endl;
		}

		getline(read_actual_result, line1);
		getline(read_expected_result, line2);

		if (!line1.compare(line2))		//��������� ����� �� ���� ������
			continue;
		else
		{
			read_actual_result.close();
			read_expected_result.close();
			FAIL() << "Files are not equal" << endl;
		}

	}
}




int main(int argc, char *argv[])
{
	ifstream fin("input.txt");	

	if (!fin)
	{
		cout << "File input.txt is not found" << endl;
		return 0;
	}
	
	ofstream fout("output.txt");

	string line, word;
	vector<string> vec;			//���������, ���������� ������

	cout << "Input word:";			//������ ����� ��� ��������
	cin >> word;

	while (!fin.eof())
	{
		getline(fin, line);
		line = delete_word_from_str(line, word);
		vec.push_back(line);
	}

	sort(vec.begin(), vec.end(), compare_strings_case_insensitive);

	vector<string>::const_iterator i;
	for (i = vec.begin(); i != vec.end() - 1; i++)
	{
		fout << *i << endl;
	}
	fout << *i;

	fin.close();
	fout.close();

	::testing::InitGoogleTest(&argc, argv);		
	return RUN_ALL_TESTS();	
}