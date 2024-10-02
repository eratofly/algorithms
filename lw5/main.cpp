#include <iostream>
#include <vector>
#include <algorithm>

/*
    Охотникова Дарья Сергеевна
    ПС-22
    Задание 1
    VS Code 1.15.1
    1. Имеется массив элементов,  отсортированный по некоторому
	полю. Методом бинарного поиска обеспечить:
    1) нахождение заданного элемента;
    2) вставку элемента;
    3) удаление элемента (7).
*/

int binary_search(std::vector<int> &arr, int left, int right, int target)
{
	while (left <= right)
	{
		int mid = (left + right) / 2;
		if (arr[mid] == target)
		{
			return mid;
		}
		else if (arr[mid] < target)
		{
			left = mid + 1;
		}
		else
		{
			right = mid - 1;
		}
	}
	return -1;
}

void insert_element(std::vector<int> &arr, int target)
{
	int n = arr.size();
	int pos = n;
	for (int i = 0; i < n; i++)
	{
		if (arr[i] > target)
		{
			pos = i;
			break;
		}
	}
	arr.insert(arr.begin() + pos, target);
}

bool delete_element(std::vector<int> &arr, int target)
{
	int pos = binary_search(arr, 0, arr.size() - 1, target);
	if (pos != -1)
	{
		arr.erase(arr.begin() + pos);
	}
	return pos != -1;
}

int main()
{
	std::vector<int> arr;
	std::cout << "Введите числа разделенные пробелами: " << std::endl;
	std::string line;
	std::getline(std::cin, line);
	std::string stringNumber;
	for (auto &ch : line)
	{
		if (isdigit(ch))
		{
			stringNumber += ch;
		}
		else
		{
			arr.push_back(stoi(stringNumber));
			stringNumber = "";
		}
	}
	arr.push_back(stoi(stringNumber));
	std::sort(arr.begin(), arr.end());
	bool isContinue = true;
	while (isContinue)
	{
		std::cout << "Введите команды (search, insert, delete) и число рядом: " << std::endl;
		std::string command;
		std::cin >> command;
		int number;
		std::cin >> number;
		if (command == "delete")
		{
			if (delete_element(arr, number))
			{
				std::cout << "Число " << number << " удален" << std::endl;
			}
			else
			{
				std::cout << "Элемент не найден!" << std::endl;
			}
		}
		else if (command == "insert")
		{
			insert_element(arr, number);
		}
		else if (command == "search")
		{
			int position = binary_search(arr, 0, arr.size() - 1, number);
			if (position == -1)
			{
				std::cout << "Элемент не найден!" << std::endl;
			}
			else
			{
				std::cout << "Позиция заданного элемента: " << position << std::endl;
			}
		}
		std::cout << "Массив после сортировки: " << std::endl;
		for (int i : arr)
		{
			std::cout << i << " ";
		}
		std::cout << std::endl;
		std::cout << "Хотите продолжить?(y/n)" << std::endl;
		std::string continueString;
		std::cin >> continueString;
		isContinue = continueString == "y";
	}
}