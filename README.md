# CPD_Proyecto1

## Temporary compilation instructions
### Windows
g++ .\main.cpp -I"include" -L"lib" -Wall -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -o main
### Ubuntu
g++ -Wall -o main.exe main.cpp -lSDL2 -lSDL2_image

./main 1