# Gogolitor

Minimal fluid solver written as a c++ core interfaced with pyton, that 
tracks a fluid interface. This projecti aims to be used for interactive 
fluid simulations in videogames.

## Python Interface

The code is interfaced to python using [pybind11][pybind11_link].

### Prerequisites

**On Unix (Linux, OS X)**

* C++11 compiler
* CMake

**On Windows**

* Visual Studio 2015
* CMake

### Installation

Just clone this repository and pip install. The `--recursive` option is
needed for the pybind11 submodule:

```bash
git clone --recursive https://https://github.com/leDernier/Gogolitor.git
pip install ./Gogolitor
```

Following instructions of the `setup.py` file, the `pip install` command will
invoke CMake and build the pybind11 module as specified in `CMakeLists.txt`.

### Special notes for Windows

**Compiler requirements**

Pybind11 requires a C++11 compliant compiler, i.e Visual Studio 2015 on Windows.

**Runtime requirements**

The Visual C++ 2015 redistributable packages are a runtime requirement for this
project. It can be found [here][vs2015_runtime]. 

### Test call

```bash
python scripts/simple_example.py
```

### Building the documentation

Build the documentation in html format using Sphinx :

 - `cd cmake_example/docs`
 - `make html`

## TODO

### General
- [ ] Add yourselves as authors 
- [ ] Write a lot of comments and documentation
- [ ] Write the naming conventions
- [ ] Copyrite notice should be in each file of the source code
- [ ] Add references
- [ ] Draw a logo, improve this README with pictures and increas this TODO list 
- [ ] Build the documentation of the "physics" part

### Structure or Optimisation
- [ ] Rewrite the Vector class with two template arguments
- [ ] Structure the project folders
- [ ] Improve CMake configuration (so that it is much more flexible)
- [ ] Create Godot bindings (and a scons configuration)
- [ ] Assert errors
- [ ] Setup testing operations
- [ ] Write more carefully the bindings

### Features
- [ ] Improve Python visualisation. Build up Python post processing tools.
- [ ] Couple the fluid to solids.
	* [ ] Add a possible source terme in the St-Venant equation
	* [ ] Deduce the fluid forces that should apply to a rigidbody present in the flow
- [ ] Add new possibilities for mesh generation.
- [ ] Solver optimisation for a structured mesh ?
- [ ] Try out other time schemes : Rung-Kuta and/or Adams-Bashforth methods.
- [ ] Add a Lagrangian solver : Look at the boundary element method.
- [ ] Take a look to [vortons][vortons_doc].


## License

Gogolitor is provided under the MIT license, that can be found in the [LICENSE][license] file.


## Authors

* [Rémi Monthiller](https://github.com/leDernier)

[license]: ./LICENSE
[vs2015_runtime]: https://www.microsoft.com/en-us/download/details.aspx?id=48145
[vortons_doc]: http://www.mijagourlay.com/fluid
[pybind11_link]: http://github.com/pybind/pybind11
