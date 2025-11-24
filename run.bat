nasm -f win64 asmCalculateVectorDistance.asm
gcc -c cCalculateVectorDistance.c -o cCalculateVectorDistance.obj -m64
gcc cCalculateVectorDistance.obj asmCalculateVectorDistance.obj -o calculateVectorDistance.exe