# CPD_Proyecto1

## Temporary compilation instructions
### Windows
#### Secuencial
g++ .\main.cpp -I"include" -L"lib" -Wall -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -o main

#### Paralelo
g++ .\main.cpp -I"include" -L"lib" -Wall -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -o main -fopenmp
### Ubuntu
#### Secuencial
g++ -Wall -o main.exe main.cpp -lSDL2 -lSDL2_image

#### Paralelo
g++ -Wall -o main.exe main.cpp -lSDL2 -lSDL2_image -fopenmp

./main 1