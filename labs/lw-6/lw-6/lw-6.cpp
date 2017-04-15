#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
struct Num
{
	std::vector<int> number;
	unsigned count = 0;
};


std::vector<int> ReadNumber(const std::string &n, unsigned lenght)
{
	std::vector<int> num(lenght);
	for (int i = n.length() - 1, j = 0; i >= 0; --i, ++j)
	{
		num[j] = static_cast<int>(n[i]) - '0';
	}
	return num;
}

unsigned GetNum(const std::vector<int> &number, unsigned pos)
{
	unsigned result = 0;
	for (unsigned i = pos; i < number.size(); ++i)
	{
		result += number[i];
	}
	return result;
}

//
//void SetNum(const std::string &str, unsigned &result, unsigned &resultNum)
//{
//	result = 0;
//	resultNum = 0;
//	for (auto el : str)
//	{
//		result += static_cast<unsigned>(el) - '0';
//		resultNum *= 10;
//		resultNum += static_cast<unsigned>(el) - '0';
//	}
//}


//���� �������� �� ������������
void IncNumber(std::vector<int> &number, unsigned i)
{
	for (;number[i] + 1 > 9; ++i)
	{
		number[i] = 0;
	}
	++number[i];
}


std::vector<int> SubNumbers(std::vector<int> &num1, std::vector<int> &num2)
{
	int shortNum = 0;

	std::vector<int> result;
	for (size_t i = 0; i < num1.size() && i < num2.size(); ++i)
	{
		shortNum = num1[i] - num2[i];

		if (shortNum < 0)
		{
			--num1[i + 1];
			shortNum += 10;
		}
		result.push_back(shortNum);
	}

	return result;
}


std::vector<int> AddNumbers(std::vector<int> &num1, std::vector<int> &num2)
{
	int shortNum = 0;

	//std::string result = "";
	std::vector<int> result;
	for (size_t i = 0; i < num1.size() && i < num2.size(); ++i)
	{
		shortNum = num1[i] + num2[i];

		if (shortNum > 9)
		{
			++num1[i + 1];
			shortNum -= 9;
		}
		result.push_back(shortNum);
	}

	return result;
}


std::vector<int> CountNewNumber(const Num &first, const Num &second)
{
	std::vector<int> result = second.number;//wtf??
	unsigned currResult = GetNum(second.number, 1);

	int tmp = first.count - currResult;
	for (size_t i = 0, j = second.number.size() - 1; tmp > 0; ++i, --j)
	{
		if (tmp > 9)
		{
			result[i] = 9;
		}
		else
		{
			if (tmp <= result[i])
			{
				result[i] += tmp;
				if (result[i] > 9)
				{
					result[i + 1] = result[i] - 9;
					result[i] = 9;
					tmp -= result[i + 1];
				}
			}
			else
			{
				result[i] = tmp;
			}
		}
		tmp -= result[i];
	}

	return result;

}


int main()
{

	std::ifstream input("input.txt");
	std::ofstream output("output.txt");
	unsigned numLenght = 0;
	input >> numLenght;
	input.get();

	std::string tmpString;

	input >> tmpString;
	std::string firstNum = tmpString.substr(0, numLenght);
	std::string secondNum = tmpString.substr(numLenght);


	Num first;
	Num second;


	first.number = ReadNumber(firstNum, numLenght);
	first.count = GetNum(first.number, 0);

	second.number = ReadNumber(secondNum, numLenght);
	second.count = GetNum(second.number, 0);


	if (first.count == second.count)
	{
		output << 0;
	}
	else if (first.count > second.count)
	{

		unsigned currResult = GetNum(second.number, 1);
		std::vector<int> tmpRes(numLenght);

		//if (first.count <= currResult)
		//{
		//	IncNumber(first.number, 0);//����������� ������
		//	first.count = GetNum(first.number, 0);//������� ����� ������

		//	//��� ���� ��� ��������� ����� ��� �������� �����

		//	std::vector<int> tmp(numLenght);
		//	tmp.push_back(1);
		//	tmpRes = SubNumbers(tmp, second.number);

		//	second.number = std::vector<int> (numLenght);//�������� ������

		//	second.count = 0;//������� ����� ������

			//��� ��������� �� first.count �����,��� ����� ���������� ���� ���������
		//���������� �� ��� ����� ������ ��� ����� 10--��� ����?
		//��� ������ ����������
		// � ���� ������� ������� � �������������� �������� 1

		//��� ���� 02 98  ��� 02 09 ��� 02 90   //83 91   //83 93


		std::vector<int> newNumber = CountNewNumber(first, second);
		std::copy(newNumber.rbegin(), newNumber.rend(), std::ostream_iterator<int>(std::cout, " "));
		//std::vector<int> res = SubNumbers(newNumber, second.number);

		//add res && tmpRes ������,���� ���� ��

		//res = AddNumbers(res, tmpRes);
		//std::copy(res.begin(), res.end(), std::ostream_iterator<int>(output, " "));
		//output << std::endl;


	}
	else
	{
		unsigned tmp = second.count;
		std::vector<int> tmpNum = second.number;

		if (second.number.size() != 1)
		{
			for (size_t i = 0; tmp > first.count && i < second.number.size() - 1; ++i)
			{

				second.number[i] = 0;
				++second.number[i + 1];//if >9?

				tmp -= second.number[i];
				++tmp;
			}
		}
		if (second.number[second.number.size() - 1] > 9 || second.number.size() == 1)
		{
			second.number[second.number.size() - 1] = 0;
			IncNumber(first.number, 0);
			first.count = GetNum(first.number, 0);
		}
		second.count = GetNum(second.number, 0);

		std::vector<int> newNumber = CountNewNumber(first, second);
		std::copy(newNumber.rbegin(), newNumber.rend(), std::ostream_iterator<int>(std::cout, " "));
	}
	return EXIT_SUCCESS;
}

