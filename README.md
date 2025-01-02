# projet-c
partial reimplementation of Hashcat with a GUI

# compiling GUI
## install dependencies
| Distribution   | Binary package | Development package | Additional packages |
|----------------|----------------|----------------------|---------------------|
| Debian/Ubuntu  | libgtk-4-1     | libgtk-4-dev         | gtk-4-examples      |
| Fedora         | gtk4           | gtk4-devel           | -                   |

## build
```
gcc -o hashdog backend.c config.c main.c $(pkg-config --cflags --libs gtk4 openssl)
```
