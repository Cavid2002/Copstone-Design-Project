cd src
./compile.sh
cd ..

gcc main.c -o ./bin/main -L"./src/" -lNET 
gcc client.c -o ./bin/client -L"./src/" -lNET