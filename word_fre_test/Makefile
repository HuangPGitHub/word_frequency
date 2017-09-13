main_word_frq_improve_improve : main_word_frq_improve.o libdoubleList.a
	gcc -o main_word_frq_improve main_word_frq_improve.o libdoubleList.a
libdoubleList.a : doubleList.o
	ar rc libdoubleList.a doubleList.o
main_word_frq_improve.o : main_word_frq_improve.c doubleList.h
	gcc -c -g main_word_frq_improve.c 
doubleList.o : doubleList.c doubleList.h
	gcc -c -g doubleList.c
.PHONY : clean
clean :
	rm main_word_frq_improve doubleList.o main_word_frq_improve.o libdoubleList.a
