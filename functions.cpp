#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "functions.h"

/*
Функция showMenu
Отображает главное меню программы и обрабатывает выбор пользователя.
Параметры:
- sales: ссылка на массив структур Sale
- count: ссылка на количество элементов в массиве
*/
void showMenu(Sale*& sales, int& count) {
	int choice;
	do {
		std::cout << "\nМеню:\n"
		<< "0. Выход\n"
		<< "1. О программе\n"
		<< "2. Загрузить продажи\n"
		<< "3. Сохранить продажи\n"
		<< "4. Показать все продажи\n"
		<< "5. Добавить продажу\n"
		<< "6. Редактировать продажу\n"
		<< "7. Удалить продажу\n"
		<< "8. Сортировать продажи\n"
		<< "9. Анализ по месяцам\n"
		<< "Выберите пункт: ";
		std::cin >> choice;
		std::cin.ignore();
		
		switch(choice) {
			case 0: 
			std::cout << "Выход из программы.\n";
			break;
		case 1:
			std::cout << "Программа для учета продаж автосалона.\n";
			break;
		case 2:
			loadSales(sales, count, "in.txt");
			break;
		case 3:
			saveSales(sales, count, "in.txt");
			break;
		case 4:
			printSales(sales, count);
			break;
		case 5:
			addSale(sales, count);
			break;
		case 6:
			editSale(sales, count);
			break;
		case 7:
			deleteSale(sales, count);
			break;
		case 8:
			sortSales(sales, count);
			break;
		case 9:
			processQuery(sales, count);
			break;
		default:
			std::cout << "Неверный выбор!\n";
		}
	} while (choice != 0);
}

/*
Функция loadSales
Загружает данные о продажах из текстового файла.
Параметры:
- sales: ссылка на массив структур Sale
- count: ссылка на количество элементов в массиве
- filename: имя файла для загрузки данных
*/
void loadSales(Sale*& sales, int& count, const char* filename) {
	std::ifstream file(filename);
	if (!file) {
		std::cout << "Ошибка открытия файла!\n";
		return;
	}
	
	// Подсчет количества строк в файле
	int tempCount = 0;
	std::string line;
	while (std::getline(file, line)) tempCount++;
	file.clear();
	file.seekg(0);
	
	// Выделение памяти под массив
	delete[] sales;
	sales = new Sale[tempCount];
	count = tempCount;
	
	// Чтение данных из файла
	for (int i = 0; i < count; i++) {
		file >> sales[i].date >> sales[i].manager 
		>> sales[i].car >> sales[i].price;
	}
	
	file.close();
	std::cout << "Загружено " << count << " продаж.\n";
}

/*
Функция saveSales
Сохраняет данные о продажах в текстовый файл.
Параметры:
- sales: массив структур Sale
- count: количество элементов в массиве
- filename: имя файла для сохранения
*/
void saveSales(const Sale* sales, int count, const char* filename) {
	std::ofstream file(filename);
	if (!file) {
		std::cout << "Ошибка сохранения файла!\n";
		return;
	}
	
	for (int i = 0; i < count; i++) {
		file << sales[i].date << " " << sales[i].manager << " "
		<< sales[i].car << " " << sales[i].price << "\n";
	}
	
	file.close();
	std::cout << "Сохранено " << count << " продаж.\n";
}

/*
Функция printSales
Выводит на экран список всех продаж.
Параметры:
- sales: массив структур Sale
- count: количество элементов в массиве
*/
void printSales(const Sale* sales, int count) {
	if (count == 0) {
		std::cout << "Нет данных о продажах.\n";
		return;
	}
	
	std::cout << "Список продаж:\n";
	for (int i = 0; i < count; i++) {
		std::cout << i+1 << ". " << sales[i].date << " " 
		<< sales[i].manager << " " << sales[i].car 
		<< " " << sales[i].price << "\n";
	}
}

/*
Функция addSale
Добавляет новую запись о продаже в массив.
Параметры:
- sales: ссылка на массив структур Sale
- count: ссылка на количество элементов в массиве
*/
void addSale(Sale*& sales, int& count) {
	Sale newSale;
	
	// Ввод данных о новой продаже
	std::cout << "Введите дату (dd.mm.yyyy): ";
	std::getline(std::cin, newSale.date);
	std::cout << "Введите фамилию менеджера: ";
	std::getline(std::cin, newSale.manager);
	std::cout << "Введите марку автомобиля: ";
	std::getline(std::cin, newSale.car);
	std::cout << "Введите цену: ";
	std::cin >> newSale.price;
	std::cin.ignore();
	
	// Создание нового массива с увеличенным размером
	Sale* newSales = new Sale[count + 1];
	for (int i = 0; i < count; i++) {
		newSales[i] = sales[i];
	}
	newSales[count] = newSale;
	
	// Освобождение старой памяти и обновление указателя
	delete[] sales;
	sales = newSales;
	count++;
	
	std::cout << "Продажа добавлена.\n";
}

/*
Функция editSale
Редактирует существующую запись о продаже.
Параметры:
- sales: массив структур Sale
- count: количество элементов в массиве
*/
void editSale(Sale* sales, int count) {
	if (count == 0) {
		std::cout << "Нет данных для редактирования.\n";
		return;
	}
	
	// Вывод списка продаж для выбора
	printSales(sales, count);
	int index;
	std::cout << "Введите номер продажи для редактирования: ";
	std::cin >> index;
	std::cin.ignore();
	
	if (index < 1 || index > count) {
		std::cout << "Неверный номер!\n";
		return;
	}
	
	// Ввод новых данных
	std::cout << "Введите новую дату (dd.mm.yyyy): ";
	std::getline(std::cin, sales[index-1].date);
	std::cout << "Введите новую фамилию менеджера: ";
	std::getline(std::cin, sales[index-1].manager);
	std::cout << "Введите новую марку автомобиля: ";
	std::getline(std::cin, sales[index-1].car);
	std::cout << "Введите новую цену: ";
	std::cin >> sales[index-1].price;
	std::cin.ignore();
	
	std::cout << "Продажа изменена.\n";
}

/*
Функция deleteSale
Удаляет запись о продаже из массива.
Параметры:
- sales: ссылка на массив структур Sale
- count: ссылка на количество элементов в массиве
*/
void deleteSale(Sale*& sales, int& count) {
	if (count == 0) {
		std::cout << "Нет данных для удаления.\n";
		return;
	}
	
	// Вывод списка продаж для выбора
	printSales(sales, count);
	int index;
	std::cout << "Введите номер продажи для удаления: ";
	std::cin >> index;
	std::cin.ignore();
	
	if (index < 1 || index > count) {
		std::cout << "Неверный номер!\n";
		return;
	}
	
	// Создание нового массива без удаляемого элемента
	Sale* newSales = new Sale[count - 1];
	for (int i = 0, j = 0; i < count; i++) {
		if (i != index-1) {
			newSales[j++] = sales[i];
		}
	}
	
	// Освобождение старой памяти и обновление указателя
	delete[] sales;
	sales = newSales;
	count--;
	
	std::cout << "Продажа удалена.\n";
}

/*
Функция sortSales
Сортирует массив продаж по выбранному критерию.
Параметры:
- sales: массив структур Sale
- count: количество элементов в массиве
*/
void sortSales(Sale* sales, int count) {
	if (count == 0) {
		std::cout << "Нет данных для сортировки.\n";
		return;
	}
	
	int choice;
	std::cout << "Сортировать по:\n"
	<< "1. Дате\n"
	<< "2. Менеджеру\n"
	<< "3. Марке авто\n"
	<< "4. Цене\n"
	<< "Выберите вариант: ";
	std::cin >> choice;
	std::cin.ignore();
	
	// Сортировка в зависимости от выбора пользователя
	switch(choice) {
	case 1:
		std::sort(sales, sales + count, [](const Sale& a, const Sale& b) {
			return a.date < b.date;
		});
		break;
	case 2:
		std::sort(sales, sales + count, [](const Sale& a, const Sale& b) {
			return a.manager < b.manager;
		});
		break;
	case 3:
		std::sort(sales, sales + count, [](const Sale& a, const Sale& b) {
			return a.car < b.car;
		});
		break;
	case 4:
		std::sort(sales, sales + count, [](const Sale& a, const Sale& b) {
			return a.price < b.price;
		});
		break;
	default:
		std::cout << "Неверный выбор!\n";
		return;
	}
	
	std::cout << "Данные отсортированы.\n";
	printSales(sales, count);
}

/*
Функция processQuery
Анализирует продажи по месяцам и сохраняет отчет в файл.
Параметры:
- sales: массив структур Sale
- count: количество элементов в массиве
*/
void processQuery(const Sale* sales, int count) {
	if (count == 0) {
		std::cout << "Нет данных для анализа.\n";
		return;
	}
	
	// Массив для подсчета продаж по месяцам
	int months[12] = {0};
	
	// Подсчет продаж по месяцам
	for (int i = 0; i < count; i++) {
		int month = std::stoi(sales[i].date.substr(3, 2)) - 1;
		if (month >= 0 && month < 12) {
			months[month]++;
		}
	}
	
	// Сохранение отчета в файл
	std::ofstream out("out.txt");
	out << "Месяц года Количество\n";
	for (int i = 0; i < 12; i++) {
		if (months[i] > 0) {
			out << (i+1) << ".2022 " << months[i] << "\n";
		}
	}
	out.close();
	
	std::cout << "Результат сохранен в out.txt\n";
}
