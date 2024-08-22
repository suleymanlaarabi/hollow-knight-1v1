gcc -O3 -march=native -flto -funroll-loops -ffast-math delivery/life_spawner/*.c  delivery/*.c delivery/utils/*.c delivery/player/*.c delivery/app/*.c -o main -lcsfml-window -lcsfml-system -lcsfml-graphics -lcsfml-audio
rm -rf ~/Bureau/game
mkdir ~/Bureau/game
cp -r assets ~/Bureau/game
cp main ~/Bureau/game
./main