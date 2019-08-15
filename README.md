# ifaresi-sca
Ifaresi's Simple Cool Applications.

## tpman
A script to manage my CS exercises.
### usage
For configure your root exercises directory. The script scans the number of subdirectories and create a config file (for default this config file is on ~/.tpmanrc ) and each exercise expected `pub.out` and default `pub.in` have to be inside each subdirectory.
```
tpman -r [ROOT_DIRECTORY]
```
example:
```
tpman -f ~/Documents/aed2/expectedInOut/block1
```
For make a diff with your file and expected out. The script recognize if the file is .c or .java, compile the file, and diff with exercise directory.
```
tpman -d [EXERCISE_NUMBER] [FILE]
```
example:
```
tpman -d 4 ex04.java
```
