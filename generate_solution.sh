g++ siemaeniu.cpp

for i in *.txt; do
    desired=".out"
    ./a.out < $i > "${i/.txt/$desired}" 
done