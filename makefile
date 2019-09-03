.SILENT:zshell 
zshell : index.c pwd_custom.c find_custom.c
	gcc -o zshell index.c -lreadline
	gcc -o pwd_c pwd_custom.c
	gcc -o find_c find_custom.c
	@echo "Make complete. Run ./zshell"

clean :
		rm find_c pwd_c zshell 