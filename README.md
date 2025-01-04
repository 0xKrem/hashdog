# Hashdog
partial reimplementation of Hashcat with a GUI

# Compiling
## Dependencies

| Distribution   | Binary package | Development package |
|----------------|----------------|----------------------|
| Debian/Ubuntu  | libgtk-4-1     | libgtk-4-dev         |
| Fedora         | gtk4           | gtk4-devel           |

## Build
- use the makefile, simply run :
```
make
```

# To-Do
## config
- [ ] GUI settings should be initialized using config file values
    - [ ] merge manually `main.c` from `krem` branch and `main.c` from `front+back`
- [ ] GUI settings should be able to write inside the config file
## misc
- [ ] functions should not exit the program
