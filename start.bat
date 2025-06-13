g++ functions.cpp -c -o functions.obj
g++ main.cpp -c -o main.obj
g++ main.obj functions.obj -o car_sales.exe
car_sales.exe
pause
