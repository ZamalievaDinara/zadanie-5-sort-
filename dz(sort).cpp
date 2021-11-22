#include <iostream>

using namespace std;

// Узнаем количество цифр через логарифм по основанию 10.
// Здесь применяется std::ceil(double arg), возвращающая наименьшее целое(представленное как double), которое не меньше чем arg.
// Например, если дано в качестве аргумента 1.02, то функция ceil() возвращает 2.0.Если дано —1.02, то ceil() возвращает —1.
int getCountsOfDigits(int number) {
	return(number == 0) ? 1 : (int)std::ceil(std::log10(std::abs(number) + 0.5));
}

uint32_t getFractional(double number, int number_of_decimal_places)
{
	double dummy;
	double frac = abs(modf(number, &dummy));
	return round(frac * pow(10, number_of_decimal_places));
}

bool intLessAlphabet(int item1, int item2)
{
	int i1 = abs(item1);
	int i2 = abs(item2);
	int len1 = getCountsOfDigits(item1);
	int len2 = getCountsOfDigits(item2);
	if (len1 < len2)
		i1 *= pow(10, len2 - len1);
	else if (len1 > len2)
		i2 *= pow(10, len1 - len2);
	return i1 < i2;
}

bool doubleLessAlphabet(double item1, double item2)
{
	int whole1 = (int)item1;
	auto fract1 = getFractional(item1, 15);
	int whole2 = (int)item2;
	auto fract2 = getFractional(item2, 15);
	if (whole1 == whole2)
		return fract1 < fract2;
	return (whole1 < 0 && whole2 < 0) ? (whole1 >= whole2) : (whole1 < whole2);
}

void bubble(double* array, const size_t size)
{
	
	for (size_t j = 0; j < size; j++)
	{
		bool alreadySorted = true;
		for (size_t i = size - 1; i > j; i--)
		{
			if (doubleLessAlphabet(array[i], array[i - 1]))
			{
				alreadySorted = false;
				swap(array[i], array[i - 1]);
			}
		}
		if (alreadySorted)
			break;
	}
}

template <typename T>
void printArray(const T& array, const size_t size)
{
	for (size_t i = 0; i < size; i++)
		cout << array[i] << " ";
	cout << endl;
}



int main() {
	setlocale(LC_ALL, "Rus");
	size_t size;
	cout << "Введите колличество элементов массива: ";
	cin >> size;
	double* arr = new double[size];
	for (size_t i = 0; i < size; i++) {
		cout << i + 1 << ": ";
		cin >> arr[i];
	}
	cout << "Введен массив         : ";
	printArray(arr, size);
	
	bubble(arr, size);

	cout << "Отсортированный массив: ";
	printArray(arr, size);
	return 0;
}