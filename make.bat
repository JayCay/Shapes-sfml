g++ -std=gnu++11 -c %1 -I"C:\SFML-2.4.2\include" -o main.o && g++ main.o -o a.exe -L"C:\SFML-2.4.2\lib" -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system