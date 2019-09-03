.SILENT:zshell clean
zshell : index.c
	gcc -o zshell index.c -lreadline
	@echo "Make complete. Run ./zshell"
clean :
		rm zshell