g++ siemaeniu.cpp

for i in *.in; do
    desired=".out"
    ./a.out < $i > "${i/.in/$desired}" 
done