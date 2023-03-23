# Proyecto #1 - Programación Paralela con OpenMP

<hr>

## Compilado

<hr>

### Windows

```
g++ .\pmain_1.cpp -I"include" -L"lib" -Wall -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -o main -fopenmp
```

<hr>

### Ubuntu

#### Paralelo
```
g++ -Wall -o main.exe p_main1.cpp -lSDL2 -lSDL2_image -fopenmp
```


<hr>

## Ejecucion

<hr>

```
./main n_balls
```


![ezgif com-video-to-gif (1)](https://user-images.githubusercontent.com/28350445/226826695-3c27121c-7f45-4d39-b8dc-3fbfd747fa28.gif)
