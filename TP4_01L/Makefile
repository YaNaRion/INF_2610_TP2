all:
	gcc -O0 -std=gnu11 -Werror -Wall -Wno-unused-result -Wno-unused-variable -o CommLab  CommLab.c

handin:
	mkdir 2207643_2198643_handin
	cp TubesNommes.c TubesAnonymes.c In.txt 2207643_2198643_handin/
	tar -czvf 2207643_2198643_handin.tar.gz 2207643_2198643_handin
	rm -rf 2207643_2198643_handin

clean:
	rm -f CommLab
	rm -f 2207643_2198643_handin.tar.gz
