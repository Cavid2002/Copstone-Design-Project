cd src
./compile.sh
cd ..

gcc main.c -o ./bin/main -L"./src/" -lNET 
./bin/main