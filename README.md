# Hashdog
partial reimplementation of Hashcat with a GUI

# Compiling
<<<<<<< HEAD
- a Makefile is used to compile the project. Just run :
```
make
```

# How-To
## dictionnary
- you specifty a wordlist (some are available in `wordlists/`)
- you choose a hashing algorithm (sha256, md5)
- every word is tried against the target
```bash
./hashdog -p 751BFE525CED7366C5BD61B473FF05BEE028F47C036EDD00174CAD2EC92FE63A
```

## bruteforce
- trying strings with every combination of characters
- strings have varying sizes
- you can specify the character set of the password
```bash
./hashdog        \
    -m bruteforce\
    -c ln        \
    -n 6         \
    -x 8         \
    -p d6710209b8fed4d12f7c305d4a68c3a1a1f327ae2037b9c9c2983aea5ce7cad4
```
=======
## install dependencies

| Distribution   | Binary package | Development package |
|----------------|----------------|----------------------|
| Debian/Ubuntu  | libgtk-4-1     | libgtk-4-dev         |
| Fedora         | gtk4           | gtk4-devel           |

## build
- use the makefile, simply run :
```
make
```
>>>>>>> dbc4c29506f54b019524cdf595c5b7ab00ccfadd
