# Installation

To install from source, you will need to install a suitable C++ compiler and
corresponding build tools for your platform as well as CMake and zlib. 
The instructions listed here refer to the installation of PASTAQ's Python
bindings.  Currently the only external dependencies other than zlib are included
as git submodules.  

To get started, clone this repository and initialize git submodules:

```
git clone https://github.com/PASTAQ-MS/PASTAQ.git
cd PASTAQ
git submodule init
git submodule update
```

As usual, it is strongly recommended to create a Python environment in which to build Pastaq, and the core development has been with Python 3.7.8, but other versions may be fine.

# Special build instructions for Windows

Windows requires a static version of zlib, and the one recommended is [zlib-win-build](https://github.com/kiyolee/zlib-win-build).
The core Windows work with Pastaq has been with Visual studio 2017, so it is recommended for building zlib and Pastaq.  Once you have built zlib, you must point `CMakeLists.txt` to the include directory and library according to the commented example at the top of that file.

When building Pastaq in Windows, first open a Visual Studio command prompt using Tools->Visual Studio Command Prompt in the Visual Studio IDE so that you have access to the compiler and linker.  Then, in that command window, activate your Pastaq Python environment and proceed with the instructions below.

# Build the module and install it in your system:

```sh
# Installation
python3 setup.py install --user

# Development
python3 setup.py develop --user
```

Now it can be imported and used in python as follows:

```python
import pastaq
raw_data = pastaq.read_mzxml(...)
```

# Usage

Examples of the usage of the PASTAQ can be found in the `examples` folder. To
run them, install pastaq as previously described, update the input path of the
mzXML and mzID files, change any necessary parameters and run it with:

```
python examples/small_range.py
```

You can use any mzXML files and identifications in mzIdentML v1.1+. If no
identifications are available, remove the `ident_path` from the input files
array or set it to `'none'`. You can find the files we used for testing and
development via ProteomeXchange, with identifier [PXD024584](https://www.ebi.ac.uk/pride/archive/projects/PXD024584).

Processing of mzML files is in an early stage and may lead to some issues.

For more information about PASTAQ and the configuration of the parameters,
please visit [the official website][website].

[website]: https://pastaq.horvatovichlab.com

# Compile the pastaq library from source

For an out of source build of the library, create a build directory and run cmake:

```sh
mkdir build
cd build
cmake ..
make
```

If you wish to enable the compilation of the tests you need to set up the
`PASTAQ_ENABLE_TESTS` flag to 1. A limited number of automated test are
currently available but we are looking forward to improve this in the future.

```sh
mkdir build
cd build
cmake .. -DPASTAQ_ENABLE_TESTS=1
make
make test
```

Additionally, you can use the Ninja building tool for faster compilation times.

```sh
mkdir build
cd build
cmake .. -DPASTAQ_ENABLE_TESTS=1 -GNinja
ninja
ninja test
```

# How to cite this work

The main manuscript has been published in as Open Access Analytical Chemistry with the following details: [Alejandro Sánchez Brotons, Jonatan O. Eriksson, Marcel Kwiatkowski, Justina C. Wolters, Ido P. Kema, Andrei Barcaru, Folkert Kuipers, Stephan J. L. Bakker, Rainer Bischoff, Frank Suits, and Péter Horvatovich, Pipelines and Systems for Threshold-Avoiding Quantification of LC–MS/MS Data, Analytical Chemistry, 2021, 93, 32, 11215–11224](https://pubs.acs.org/doi/10.1021/acs.analchem.1c01892).
