# doyt
The game engine I dream to write - Doyt!

# Compilation


if you link against *shared* glfw libray then add:
```
	-DGLFW_DLL 
```
to your application/library compilation command.


DO NOT FORGET TO LINK AGAINTS GLFW REQUIRED LIBRARIES (ON WINDOWS):
```
	-user32
	-gdi32
	-kernel32
	-opengl32 // when you didn't specify context by yourself (I guess so, didn't check it)
```


Compiling application using clang:

	`Main compilation configuration`
	clang++
	-std=c++17

	`Links againts c++ standard library`
	--include-directory "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Tools\MSVC\14.27.29110\include"
	--library-directory "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Tools\MSVC\14.27.29110\bin\Hostx64\x64"
	--library-directory "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Tools\MSVC\14.27.29110\lib\x64"

	`Links againts GLFW`
	--include-directory D:/Rasul/Projects/c++/glfw/include
	-lgdi32 -luser32 -lkernel32 -lopengl32
	-lD:/Rasul/Projects/c++/doyt/dependencies/glfw/src/Release/glfw3dll.lib

	`Specifies which files to compile and include into final binary`
	source/main.cpp 

	`Output binary`
	-o doyt.exe

# GLFW Compilation
GLFW uses cmake to create build files.
	* in case of windows it will generate microsoft build files: sln, vcproj, etc.

command:
```
	cmake
	-DBUILD_SHARED_LIBS=ON    // if we wont glfw to be shared library
	-DGLFW_BUILD_EXAMPLES=OFF // we don't need examples
	-DGLFW_BUILD_TESTS=OFF    // we don't need tests
	-DGLFW_BUILS_DOCS=OFF     // why the fuck we need docs?
	// this should be enough for us, 
	// however just know that there are other glfw cmake flags
	<glfw-directory>
```
**the above command will generate build files inside the called directory

clean-command:
```
	cmake -DBUILD_SHARED_LIBS=ON -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILS_DOCS=OFF .
```


After cmake we could call *msbuild*:

command:
```
	msbuild 
	GLFW.sln 
	--property:Configuration=Release // if we want the release version
```

clean-command:
```
	msbuild GLFW.sln --property:Configuration=Release
```
