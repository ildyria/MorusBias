# Trails for MiniMorus[640/1280] and Morus[640/1280]

## DEPENDENCIES

* AVX2 (for Morus1280)
* SSE (for Morus640)
* Lib OpenMp
* AES-NI
* Python3

## BUILD

A simple `make` will show the list of default target and build the default one.
Every target correspond to one of the trail fragments:

* alpha,
* beta,
* gamma,
* delta,
* epsil,
* first approximation
* second approximation
* full trail: Combination of first and second approximation

## Generating the masks and optimizations

In order to provide flexibility and speed we generate the masks C files through
a Python3 script. Once generated they will be found in the newly created Masks
folder.

Using C++ with OOP or C with function pointer does not allow the compiler to
predict efficiently which function will be executed next. This induce a factor
2 slowdown. By specifying with `#define` the version we want to use, we allow the
compiler to inline most of the code.

In order to compute C_0 + C_2 we do not loop over the bits of C. We generate a masks
where bits at positions 0 and 2 are set and `&` it with C.
The oddness of the Hamming Weight provide us the result.
Bits positions used in the masks are specified in `masks.py`

## Morus implementations

The Morus implementations in SSE and AVX2 are greatly inspired from the one provided for
the CAESAR competition: http://www3.ntu.edu.sg/home/wuhj/research/caesar/caesar.html.
