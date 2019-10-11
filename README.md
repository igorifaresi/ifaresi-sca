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
tpman -r ~/Documents/aed2/expectedInOut/block1
```
For make a diff with your file and expected out. The script recognize if the file is .c or .java, compile the file, and diff with exercise directory.
```
tpman -d [EXERCISE_NUMBER] [FILE]
```
example:
```
tpman -d 4 ex04.java
```

## TruthTableGen
A program for generate truth tables.
### usage
Create a `TruthTableGen` object and gives to constructor the std::vector of (bool)(std::vector<bool>) functions, the std::vector of functions name, and the var qnt (1 to 4).
```cpp
bool my_func(std::vector<bool> b)
{
	return b[0] & b[1] & b[2] & b[3];
}

bool my_func2(std::vector<bool> b1)
{
	return !b1[0];
}

int main()
{
	TruthTableGen table({my_func,my_func2},{"x & y & z & w","~x"},4);
	printf(table.generate().c_str());
}
```
