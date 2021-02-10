# doyt
The game engine I dream to write - Doyt!

# Compilation
if you link against *shared* glfw libray then add:
```
	-DGLFW_DLL 
```
to your application/library compilation command (if it is not already defined in code as I did).

To compile the application run: 
```
./build project.build
```

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


After cmake we could call *msbuild*:

command:
```
	msbuild 
	GLFW.sln 
	--property:Configuration=Release // if we want the release version
```