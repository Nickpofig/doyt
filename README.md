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

# GLFW Compilation
GLFW uses cmake to create build files. (in case of windows it will generate microsoft build files: sln, vcproj, etc.)
```
	cmake
	-DBUILD_SHARED_LIBS=ON    // if we want glfw to be a shared library
	-DGLFW_BUILD_EXAMPLES=OFF // no examples
	-DGLFW_BUILD_TESTS=OFF    // no tests
	-DGLFW_BUILS_DOCS=OFF     // no docs
	<glfw-directory>
```

On the Windows to compile glfw call:
```
	msbuild GLFW.sln --property:Configuration=Release
```

# Run the application
Just call it. However, do not forget to add glfw.dll manually into the binary folder (I didn't automized it yet :P) 