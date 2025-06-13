#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>

/*
Структура Sale хранит данные о продаже автомобиля:
- date: дата продажи в формате "dd.mm.yyyy"
- manager: фамилия менеджера, оформившего продажу
- car: марка проданного автомобиля
- price: цена продажи
*/
struct Sale {
	std::string date;
	std::string manager;
	std::string car;
	int price;
};

/*
Функции для работы с данными автосалона:
- showMenu: отображает меню и обрабатывает выбор пользователя
- loadSales: загружает данные о продажах из файла
- saveSales: сохраняет данные о продажах в файл
- printSales: выводит список всех продаж
- addSale: добавляет новую запись о продаже
- editSale: редактирует существующую запись
- deleteSale: удаляет запись о продаже
- sortSales: сортирует записи по выбранному критерию
- processQuery: анализирует продажи по месяцам и сохраняет отчет
*/
void showMenu(Sale*& sales, int& count);
void loadSales(Sale*& sales, int& count, const char* filename);
void saveSales(const Sale* sales, int count, const char* filename);
void printSales(const Sale* sales, int count);
void addSale(Sale*& sales, int& count);
void editSale(Sale* sales, int count);
void deleteSale(Sale*& sales, int& count);
void sortSales(Sale* sales, int count);
void processQuery(const Sale* sales, int count);

#endif
