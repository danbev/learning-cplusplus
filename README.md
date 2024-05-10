## Learning C++
This repository is a collection of notes and code snippets to help understand
C++ concepts.

### __cplusplus macro

* C++ pre-C++98: __cplusplus is 1.
* C++98: __cplusplus is 199711L.
* C++98 + TR1: This reads as C++98 and there is no way to check that I know of.
* C++11: __cplusplus is 201103L.
* C++14: __cplusplus is 201402L.
* C++17: __cplusplus is 201703L.
* C++20: __cplusplus is 202002L.

### glibc++ versioning
On my system I have:
```console
$ ls -l /lib/x86_64-linux-gnu/libstdc++.so.6
/lib/x86_64-linux-gnu/libstdc++.so.6 -> libstdc++.so.6.0.30
```
Notice that this is a symbolic link to `6.0.30` which is the version of the
library. We can use the 6.0.30 version an look this up in                  
https://gcc.gnu.org/onlinedocs/libstdc++/manual/abi.html:                                  
```                                                                                        
GCC 9.1.0: libstdc++.so.6.0.26                                                             
GCC 9.2.0: libstdc++.so.6.0.27                                                             
GCC 9.3.0: libstdc++.so.6.0.28                                                             
GCC 10.1.0: libstdc++.so.6.0.28                                                            
GCC 11.1.0: libstdc++.so.6.0.29                                                            
GCC 12.1.0: libstdc++.so.6.0.30 <------------------- 6.0.30 maps to GCC 12.1.0  
GCC 13.1.0: libstdc++.so.6.0.31                                                 
GCC 13.2.0: libstdc++.so.6.0.32                                                 
GCC 14.1.0: libstdc++.so.6.0.33                                                 
```
And that is the GNU Compiler Collection version 12.1.0 that I'm using.

Now there are two types of versioning used in glibc++ and there is one
versioning for symbols for standard c++ libarary functions. These use the
GLIBCXX versioning. How this works is that every time we use a symbol from the
c++ standard library, like a function, the static linker which is used at
compiler time will add a reference to that symbol with a specific version
appended to it. For example, is we use std::string::size() in our code like
this:
```c++
std::string s = "bajja";
int size = s.size();
```
If we inspect the symbols in the binary we see the following
```console
$ nm bin/symbols | c++filt  | grep size
U std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::size() const@GLIBCXX_3.4.21
```
This means that the dynamic linker will load the version `@GLIBCXX_3.4.21` of 
the `size()` function from the libstdc++ library. This versioning allows the
standard library to evolve and add new functions or change the implementation
of existing functions without breaking existing code.

Now, if we try to run this binary of a system which is using `GLIBCXX_3.4.20`
is would not be able to find this symbol and the program would not be able to
run.

We can inspect the versioning used in the libstdc++ library on our system like
this:
```console
$ strings /lib/x86_64-linux-gnu/libstdc++.so.6 | grep GLIBCXX | sort -V
GLIBCXX_3.4                                                                     
GLIBCXX_3.4.1                                                                   
GLIBCXX_3.4.2                                                                   
GLIBCXX_3.4.3                                                                   
GLIBCXX_3.4.4                                                                              
GLIBCXX_3.4.5                                                                              
GLIBCXX_3.4.6                                                                              
GLIBCXX_3.4.7                                                                              
GLIBCXX_3.4.8                                                                              
GLIBCXX_3.4.9                                                                              
GLIBCXX_3.4.10                                                                             
GLIBCXX_3.4.11                                                                             
GLIBCXX_3.4.12                                                                             
GLIBCXX_3.4.13                                                                             
GLIBCXX_3.4.14                                                                             
GLIBCXX_3.4.15                                                                             
GLIBCXX_3.4.16                                                                             
GLIBCXX_3.4.17                                                                             
GLIBCXX_3.4.18                                                                             
GLIBCXX_3.4.19                                                                             
GLIBCXX_3.4.20                                                                             
GLIBCXX_3.4.21                                                                             
GLIBCXX_3.4.22                                                                             
GLIBCXX_3.4.23                                                                             
GLIBCXX_3.4.24                                                                             
GLIBCXX_3.4.25                                                                             
GLIBCXX_3.4.26                                                                             
GLIBCXX_3.4.27                                                                             
GLIBCXX_3.4.28                                                                             
GLIBCXX_3.4.29                                                                             
GLIBCXX_3.4.30                                                                             
```                                                                                        
So I can see that the version of libstdc++ on my system is 6.0.30 and it                   
supports `GLIBCXX_3.4.30`. I can use the 6.0.30 version an look this up in                  
https://gcc.gnu.org/onlinedocs/libstdc++/manual/abi.html:                                  
```                                                                                        
GCC 9.1.0: libstdc++.so.6.0.26                                                             
GCC 9.2.0: libstdc++.so.6.0.27                                                             
GCC 9.3.0: libstdc++.so.6.0.28                                                             
GCC 10.1.0: libstdc++.so.6.0.28                                                            
GCC 11.1.0: libstdc++.so.6.0.29                                                            
GCC 12.1.0: libstdc++.so.6.0.30 <------------------- 6.0.30 maps to GCC 12.1.0  
GCC 13.1.0: libstdc++.so.6.0.31                                                 
GCC 13.2.0: libstdc++.so.6.0.32                                                 
GCC 14.1.0: libstdc++.so.6.0.33                                                 
```                                                                             
And we can inspect the symbol versioning used for GCC 12.1.0:                   
```                                                                             
GCC 8.1.0: GLIBCXX_3.4.25, CXXABI_1.3.11                                        
GCC 9.1.0: GLIBCXX_3.4.26, CXXABI_1.3.12                                        
GCC 9.2.0: GLIBCXX_3.4.27, CXXABI_1.3.12                                        
GCC 9.3.0: GLIBCXX_3.4.28, CXXABI_1.3.12                                        
GCC 10.1.0: GLIBCXX_3.4.28, CXXABI_1.3.12                                       
GCC 11.1.0: GLIBCXX_3.4.29, CXXABI_1.3.13                                       
GCC 12.1.0: GLIBCXX_3.4.30, CXXABI_1.3.13 <-- 12.1.0 maps to GLIBCXX_3.4.30     
GCC 13.1.0: GLIBCXX_3.4.31, CXXABI_1.3.14                                       
GCC 13.2.0: GLIBCXX_3.4.32, CXXABI_1.3.14                                       
GCC 14.1.0: GLIBCXX_3.4.33, CXXABI_1.3.15     
```

There is also versioning for the C++ ABI which are functions like exception
handling and RTTI (Run-Time Type Information). This is called CXXABI versioning.
```console
$ strings /lib/x86_64-linux-gnu/libstdc++.so.6 | grep CXXABI | sort -V
CXXABI_1.3
CXXABI_1.3.1
CXXABI_1.3.2
CXXABI_1.3.3
CXXABI_1.3.4
CXXABI_1.3.5
CXXABI_1.3.6
CXXABI_1.3.7
CXXABI_1.3.8
CXXABI_1.3.9
CXXABI_1.3.10
CXXABI_1.3.11
CXXABI_1.3.12
CXXABI_1.3.13
CXXABI_FLOAT128
CXXABI_TM_1
```                                                                                        
