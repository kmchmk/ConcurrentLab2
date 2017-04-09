#!/bin/bash
rm serial_case_1.txt
rm serial_case_2.txt
rm serial_case_3.txt

rm mutex_case_1_thread_1.txt
rm mutex_case_1_thread_2.txt
rm mutex_case_1_thread_4.txt
rm mutex_case_1_thread_8.txt
rm mutex_case_2_thread_1.txt
rm mutex_case_2_thread_2.txt
rm mutex_case_2_thread_4.txt
rm mutex_case_2_thread_8.txt
rm mutex_case_3_thread_1.txt
rm mutex_case_3_thread_2.txt
rm mutex_case_3_thread_4.txt
rm mutex_case_3_thread_8.txt

rm locks_case_1_thread_1.txt
rm locks_case_1_thread_2.txt
rm locks_case_1_thread_4.txt
rm locks_case_1_thread_8.txt
rm locks_case_2_thread_1.txt
rm locks_case_2_thread_2.txt
rm locks_case_2_thread_4.txt
rm locks_case_2_thread_8.txt
rm locks_case_3_thread_1.txt
rm locks_case_3_thread_2.txt
rm locks_case_3_thread_4.txt
rm locks_case_3_thread_8.txt

gcc serial_case_1.c -o serial_case_1
gcc serial_case_2.c -o serial_case_2
gcc serial_case_3.c -o serial_case_3

gcc mutex_case_1_thread_1.c -o mutex_case_1_thread_1 -pthread
gcc mutex_case_1_thread_2.c -o mutex_case_1_thread_2
gcc mutex_case_1_thread_4.c -o mutex_case_1_thread_4
gcc mutex_case_1_thread_8.c -o mutex_case_1_thread_8
gcc mutex_case_2_thread_1.c -o mutex_case_2_thread_1
gcc mutex_case_2_thread_2.c -o mutex_case_2_thread_2
gcc mutex_case_2_thread_4.c -o mutex_case_2_thread_4
gcc mutex_case_2_thread_8.c -o mutex_case_2_thread_8
gcc mutex_case_3_thread_1.c -o mutex_case_3_thread_1
gcc mutex_case_3_thread_2.c -o mutex_case_3_thread_2
gcc mutex_case_3_thread_4.c -o mutex_case_3_thread_4
gcc mutex_case_3_thread_8.c -o mutex_case_3_thread_8

gcc locks_case_1_thread_1.c -o locks_case_1_thread_1
gcc locks_case_1_thread_2.c -o locks_case_1_thread_2
gcc locks_case_1_thread_4.c -o locks_case_1_thread_4
gcc locks_case_1_thread_8.c -o locks_case_1_thread_8
gcc locks_case_2_thread_1.c -o locks_case_2_thread_1
gcc locks_case_2_thread_2.c -o locks_case_2_thread_2
gcc locks_case_2_thread_4.c -o locks_case_2_thread_4
gcc locks_case_2_thread_8.c -o locks_case_2_thread_8
gcc locks_case_3_thread_1.c -o locks_case_3_thread_1
gcc locks_case_3_thread_2.c -o locks_case_3_thread_2
gcc locks_case_3_thread_4.c -o locks_case_3_thread_4
gcc locks_case_3_thread_8.c -o locks_case_3_thread_8

for (( c=1; c<=100; c++ ))
do  
	./serial_case_1
	./serial_case_2
	./serial_case_3

	./mutex_case_1_thread_1
	./mutex_case_1_thread_2
	./mutex_case_1_thread_4
	./mutex_case_1_thread_8
	./mutex_case_2_thread_1
	./mutex_case_2_thread_2
	./mutex_case_2_thread_4
	./mutex_case_2_thread_8
	./mutex_case_3_thread_1
	./mutex_case_3_thread_2
	./mutex_case_3_thread_4
	./mutex_case_3_thread_8

	./locks_case_1_thread_1	
	./locks_case_1_thread_2
	./locks_case_1_thread_4
	./locks_case_1_thread_8
	./locks_case_2_thread_1
	./locks_case_2_thread_2
	./locks_case_2_thread_4
	./locks_case_2_thread_8
	./locks_case_3_thread_1
	./locks_case_3_thread_2
	./locks_case_3_thread_4
	./locks_case_3_thread_8
done
