build:
	gcc file_system.c functions.c functions.h utils.h commands.h commands.c -g -o filesystem

clean:
	rm filesystem

checker:
	python3 checker.py
