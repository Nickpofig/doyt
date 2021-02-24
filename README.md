# doyt
The game engine I dream to write - Doyt!

# Compilation
To compile the application you firstly need to compile the system-run program.
For example, on windows using clang compiler frontend:
```
	clang ./deps/system-run/main.c -o run.exe
``` 

After that find *project.X.build* and call
```
	./run project.X.build
```

Right now, there is only one script to fully build project and it is for Windows platform.
However, it does NOT mean that you could NOT compile project on your machine. I try to keep code as platform-independent as possible, so theoretically you should be able to compile it. Just read available build scripts and you will find out that they are *very* simple. After that you could write your platform specific implementation of those script where it needs and run them via system-run (or you could write a bash script and run it insteed/it really does not matter)