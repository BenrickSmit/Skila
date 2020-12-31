# Skila
Skila is a very simple Ray Tracer which will help with choosing the colours of either OpenGL or Vulkan rendered graphics. 

# Description
Skila is a simple Ray Tracer made to be used with either OpenGL or Vulkan. It is made to form a sort of bridge between the normal way of rendering raster graphics, and allowing ray tracing. How it does, this, however, is not important. The different classes in the project provide different functions

<code>Coordinate</code> is the main class for all things coordinates. They can be adapted to be used in any graphics processor, but Skila will do most of the heavy-lifting (in later versions).
<code>Object</code> is the most basic coordinate collection to form other objects, such as triangles, squares, spheres, pyramids and other objects. It can only take 3 Coordinates as input to create an object that has to be rendered.
<code>MatrixOperations</code> is where most of the heavy lifting takes place. It contains funtions that are rather implicitly called by the objects to obtain colour and other data based on the rays cast
<code>Skils</code> [currently in progress] will contain the basic factory that will allow for object creation and rendering in OpenGL and (later) Vulkan.

Additionally, the following files can be found in the project that help with building and testing:

<code>init_documentation.sh</code> is used to create the documentation automatically
<code>run_all.sh</code> is used to run all tests and program execution, as well as to create the necessary documentation and profile information
<code>run_application.sh</code> is used to run only the application
<code>run_tests.sh</code> is used to run only the tests
<code>run_profile.sh</code> is used to run only the profiler

<code>build_info</code> contains the build_name, build_version, and build_cxx_standard text files.
<code>build_name</code> contains the project name. 
<code>build_version</code> contains the project version number. 
<code>build_cxx_standard</code> contains the CXX standard used, it's default is 11

Find the project [here](https://github.com/BenrickSmit/Skila), if you did not find this project on my github.

# Features
Currently this project only allows rays to affect the brightness and colour of the actual objects rendered.

# Future Changes
This project will, in future, implement reflections, refractions, light absorbtion, as well as custom light sources. I will also work on optimising the code and adding in more debugging information - as soon as it's necessary.

# How to Run
Currently the only way to use this project is to use it as a bridge between actual OpenGL code and final render by creating the objects, the resulting values, and using them in the renders. There is currently no functioning executable with sample code.

# How to Run Unit Tests
Unit tests can easily be run with the help of the run_tests.sh script, or if you are not on a linux-based system, simply navigate to build/tests/ to find the actual tests to run.

# Key Dependencies
Currently there are no definite dependcies except some STL libraries, and the already included Google Test library, that help with execution. Later it will require libraries such as OpenGL and Vulkan, however.

# How to contribute
If you find any bugs, or code improvements, please do contact me, or simply fork the code, correct it, and send it my way. I'll look at the code and see which improvements I'd like to keep.

In future, if you wish, I will enable monetary contributions as well, but not yet. I'm not yet happy with the project at hand.

# License
Skila is licensed under the  [Apache 2.0 Licence](LICENSE).

