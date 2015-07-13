

# Source Tree #

The _source tree_ is where your project lives. For example,

```
$ pwd
/home/ich/source
$ svn co http://fh-kapfenberg-sysprog-swd12.googlecode.com/svn/trunk/cmake-demo/hello-project-monolithic
```

Gives you a directory `/home/ich/source/hello-project-monolithic`. This directory is called the _project root directory_. (If you hadn't given the `hello-project-monolithic` argument, then SVN creates the basename of the path instead - this would be `trunk` in this case.)

Look in there,

```
$ tree hello-project-monolithic/
hello-project-monolithic/
|-- CMakeLists.txt
`-- hello.cc
```

This project is not very sophisticated. It consists of a single main file, `hello.cc` that outputs the program's commandline, and it compiles to an executable. The `CMakeLists.txt` file tells CMake all this; take a look in the file to understand.

The source tree is where your handwritten code is. This is what is maintained by Subversion - and nothing else. Everything else - CMake generated `Makefile`s, compiled code, executables - are in the _build tree_.

# Building with CMake #

Building with CMake is done in a separate tree. I suggest to put it completely apart from the SVN controlled source tree, in a location which you purge regularly, and which is not subject to periodic backups.

My preferred build locations are named like `/var/jfasch/build/hello-project-monolithic`, and that's what I use here in the remainder.

```
$ mkdir /var/jfasch/build/hello-project-monolithic
```

CMake's primary job is to generate `Makefile`s out of all of the `CMakeLists.txt` files in the source tree. You then use the good old `make` command to perform the actual build. Like so,

```
$ cd /var/jfasch/build/hello-project-monolithic
$ cmake /home/ich/source/hello-project-monolithic
... roedel roedel ...
$ make
... roedel roedel ...
```

You'll find an executable named `hello` in the toplevel build directory, and this is what you specified in the toplevel `CMakeLists.txt` file in the source tree.

```
$ ./hello Hallo Du!
Hallo
Du!
```

# Overengineering the Build #

The "Monolithic" project has been very simple, in that it consists of only two files - the main program and the `CMakeLists.txt` file. This is not very realistic, as real world programs are generally more complex. In a real world, programmers tend to reuse code and factor it out into libraries. The libraries are then used by other libraries, and libraries are usually used by more than one executable (people often have test suites aggregated into separate executables for example).

I tried to "simulate" complexity by overengineering the "Monolithic" project a bit. The enhanced version not only outputs the program's argument vector, but also its environment variables. Check out the enhanced project like so,

```
$ svn co http://fh-kapfenberg-sysprog-swd12.googlecode.com/svn/cmake-demo/hello-project-overengineered
```

As you browse through the tree of the "Overengineered" project, you'll notice the following.

The toplevel `CMakeLists.txt` is special, as it defines the project's name, via the `PROJECT` function. It optionally contains other things like including _Find Modules_ (but more about that later in the course of our project).

The other `CMakeLists.txt` files define so-called _nodes_ - anchor points with dependencies between them. The project, as its name suggests, is kind of overengineered in that it accomplishes simple things with artificial complexity that nobody wants. This is common in nowadays programming (Java and Dotnet programmers can't do without), and we won't make an exception.

The program does two things:

  * Output the argument vector
  * Output the environment

Consequently there are three modules (subdirectories with their own `CMakeLists.txt` files:

  * `args` - a library that outputs the argument vector.
  * `environ` - a library that outputs the environment
  * `hello` - the main executable that aggregates the functionality that is provided by the libraries.

Not enough, there's a fourth directory. We notice that the `args` and `environ` libraries have one thing in common: they _output_ things. So, rather than duplicating code, we factor out this commonality - we _overengineer_ - into one more library that resides in the `output` subdirectory of our project. This results in the final state of the project,

  * `args` - a library that outputs the argument vector.
  * `environ` - a library that outputs the environment
  * `output` - a library that provides the (extremely complex) generic "output" functionality.
  * `hello` - the main executable that aggregates the functionality that is provided by the libraries.

These modules use one another. `args` and `environ` use `output`, and `hello` uses both `args` and `environ` (but not `output`, at least not directly). This rather verbose fact is better visualized using a picture, the _dependency graph_.

![http://lh4.googleusercontent.com/-uZxgFMB6klU/TpvOLq0CEkI/AAAAAAAAAog/YEwSi1-N6oY/s251/cmake-overengineered-depgraph.jpg](http://lh4.googleusercontent.com/-uZxgFMB6klU/TpvOLq0CEkI/AAAAAAAAAog/YEwSi1-N6oY/s251/cmake-overengineered-depgraph.jpg)

I suggest now that you browse through the project a bit. The project is done in C++ which makes things a bit simpler for us (C is a bit awkward in some corner cases). Take care to notice a couple of things.

On the C/C++ front,

  * C _Include Guards_. These have to go in every header file that's subject to inclusion in multiple other files. `args/hello_args.h` for example wrap the entire content in a guard macro `HELLO_OVERENGINEERED_HELLO_ARGS_H` (the macro's name is up to the inventor).
  * `#include` directives. Header files declare a library's "interface". For example, `args/hello_args.h` declares a function `void hello_args(int argc, char** argv)`, and that declaration is pulled in in `hello/hello.cc` via `#include <hello_args.h>`. (Normally, a library's interface is much larger, and a library usually exports more than one header - but as I said we overengineer.)

On the CMake front,

  * The toplevel `CMakeLists.txt` file only registers the subdirectories `args`, `anviron`, `output` and `hello`, and does boilerplate build machinery.
  * The other `CMakeLists.txt` files define the _nodes_ of the above picture.
    * Libraries are defined in `args`, `environ`, `output` using `ADD_LIBRARY`. For example, the `args` library (defined in `args/CMakeLists.txt`) consists of `hello_args.h` and `hello_args.cc`.
    * An executable is defined in `hello/CMakeLists.txt`, using `ADD_EXECUTABLE`.
  * The arrows of the picture are defined using `TARGET_LINK_LIBRARIES`. `hello` has two such _dependencies_, `args` and `environ`. `args` and `environ` each depend on the `output` functionality. `output` is at the basis and depends on nothing at all.

# Conclusion #

That's about all you need to know about CMake and software build in general, at least concerning our course. As a matter of fact take care to not introduce _cyclic_ dependencies, as things will become weird when you do that. But that's natural anyway.