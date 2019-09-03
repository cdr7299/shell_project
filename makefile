# .SILENT:zshell pwd_c clean
zshell : index.c pwd_custom.c
	gcc -o zshell index.c -lreadline
	gcc -o pwd_c pwd_custom.c

# pwd_c : pwd_custom.c
	# @echo "Make complete. Run ./zshell"
clean :
		rm pwd_c zshell