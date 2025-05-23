## Standard Library
So depending on the compiler the standard library will have different
implementation. For gcc it is libstdc++, and the headers are installed and
they depend on the version of for example gcc. 

I've got the following version on my machine:
```console
$ gcc --version
gcc (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0
Copyright (C) 2023 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

To see the include paths for the standard library:
```console
$ gcc -v -E -x c++ - < /dev/null
Using built-in specs.
COLLECT_GCC=gcc
OFFLOAD_TARGET_NAMES=nvptx-none:amdgcn-amdhsa
OFFLOAD_TARGET_DEFAULT=1
Target: x86_64-linux-gnu
Configured with: ../src/configure -v --with-pkgversion='Ubuntu 13.3.0-6ubuntu2~24.04' --with-bugurl=file:///usr/share/doc/gcc-13/README.Bugs --enable-languages=c,ada,c++,go,d,fortran,objc,obj-c++,m2 --prefix=/usr --with-gcc-major-version-only --program-suffix=-13 --program-prefix=x86_64-linux-gnu- --enable-shared --enable-linker-build-id --libexecdir=/usr/libexec --without-included-gettext --enable-threads=posix --libdir=/usr/lib --enable-nls --enable-bootstrap --enable-clocale=gnu --enable-libstdcxx-debug --enable-libstdcxx-time=yes --with-default-libstdcxx-abi=new --enable-libstdcxx-backtrace --enable-gnu-unique-object --disable-vtable-verify --enable-plugin --enable-default-pie --with-system-zlib --enable-libphobos-checking=release --with-target-system-zlib=auto --enable-objc-gc=auto --enable-multiarch --disable-werror --enable-cet --with-arch-32=i686 --with-abi=m64 --with-multilib-list=m32,m64,mx32 --enable-multilib --with-tune=generic --enable-offload-targets=nvptx-none=/build/gcc-13-fG75Ri/gcc-13-13.3.0/debian/tmp-nvptx/usr,amdgcn-amdhsa=/build/gcc-13-fG75Ri/gcc-13-13.3.0/debian/tmp-gcn/usr --enable-offload-defaulted --without-cuda-driver --enable-checking=release --build=x86_64-linux-gnu --host=x86_64-linux-gnu --target=x86_64-linux-gnu --with-build-config=bootstrap-lto-lean --enable-link-serialization=2
Thread model: posix
Supported LTO compression algorithms: zlib zstd
gcc version 13.3.0 (Ubuntu 13.3.0-6ubuntu2~24.04)
COLLECT_GCC_OPTIONS='-v' '-E' '-mtune=generic' '-march=x86-64'
 /usr/libexec/gcc/x86_64-linux-gnu/13/cc1plus -E -quiet -v -imultiarch x86_64-linux-gnu -D_GNU_SOURCE - -mtune=generic -march=x86-64 -fasynchronous-unwind-tables -fstack-protector-strong -Wformat -Wformat-security -fstack-clash-protection -fcf-protection -dumpbase -
ignoring duplicate directory "/usr/include/x86_64-linux-gnu/c++/13"
ignoring nonexistent directory "/usr/local/include/x86_64-linux-gnu"
ignoring nonexistent directory "/usr/lib/gcc/x86_64-linux-gnu/13/include-fixed/x86_64-linux-gnu"
ignoring nonexistent directory "/usr/lib/gcc/x86_64-linux-gnu/13/include-fixed"
ignoring nonexistent directory "/usr/lib/gcc/x86_64-linux-gnu/13/../../../../x86_64-linux-gnu/include"
#include "..." search starts here:
#include <...> search starts here:
 /usr/include/c++/13
 /usr/include/x86_64-linux-gnu/c++/13
 /usr/include/c++/13/backward
 /usr/lib/gcc/x86_64-linux-gnu/13/include
 /usr/local/include
 /usr/include/x86_64-linux-gnu
 /usr/include
End of search list.
# 0 "<stdin>"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "<stdin>"
COMPILER_PATH=/usr/libexec/gcc/x86_64-linux-gnu/13/:/usr/libexec/gcc/x86_64-linux-gnu/13/:/usr/libexec/gcc/x86_64-linux-gnu/:/usr/lib/gcc/x86_64-linux-gnu/13/:/usr/lib/gcc/x86_64-linux-gnu/
LIBRARY_PATH=/usr/lib/gcc/x86_64-linux-gnu/13/:/usr/lib/gcc/x86_64-linux-gnu/13/../../../x86_64-linux-gnu/:/usr/lib/gcc/x86_64-linux-gnu/13/../../../../lib/:/lib/x86_64-linux-gnu/:/lib/../lib/:/usr/lib/x86_64-linux-gnu/:/usr/lib/../lib/:/usr/lib/gcc/x86_64-linux-gnu/13/../../../:/lib/:/usr/lib/
COLLECT_GCC_OPTIONS='-v' '-E' '-mtune=generic' '-march=x86-64'
```

When we include a header like this:
```c++
#include <vector>
```
The file vector is will be in `/usr/include/c++/13/vector`. This file mainly
contains includes of other files and most of them are in the "bits and pieces"
directory name 'bits'.
```c++
...

#include <bits/requires_hosted.h> // container

#include <bits/stl_algobase.h>
#include <bits/allocator.h>
#include <bits/stl_construct.h>
#include <bits/stl_uninitialized.h>
#include <bits/stl_vector.h>
#include <bits/stl_bvector.h>
```
In `stl_vector.h` we can find the implementation of the vector class:
```c++
  template<typename _Tp, typename _Alloc = std::allocator<_Tp> >
    class vector : protected _Vector_base<_Tp, _Alloc>
    {
```

I'm finding is a litle difficult to read the code in the headers, take allocator.h
and its allocate function:
```c++
      // NB: __n is permitted to be 0.  The C++ standard says nothing
      // about what the return value is when __n == 0.
      _GLIBCXX_NODISCARD _Tp*
      allocate(size_type __n, const void* = static_cast<const void*>(0))
      {
#if __cplusplus >= 201103L
	// _GLIBCXX_RESOLVE_LIB_DEFECTS
	// 3308. std::allocator<void>().allocate(n)
	static_assert(sizeof(_Tp) != 0, "cannot allocate incomplete types");
#endif

	if (__builtin_expect(__n > this->_M_max_size(), false))
	  {
	    // _GLIBCXX_RESOLVE_LIB_DEFECTS
	    // 3190. allocator::allocate sometimes returns too little storage
	    if (__n > (std::size_t(-1) / sizeof(_Tp)))
	      std::__throw_bad_array_new_length();
	    std::__throw_bad_alloc();
	  }

#if __cpp_aligned_new
	if (alignof(_Tp) > __STDCPP_DEFAULT_NEW_ALIGNMENT__)
	  {
	    std::align_val_t __al = std::align_val_t(alignof(_Tp));
	    return static_cast<_Tp*>(_GLIBCXX_OPERATOR_NEW(__n * sizeof(_Tp),
							   __al));
	  }
#endif
	return static_cast<_Tp*>(_GLIBCXX_OPERATOR_NEW(__n * sizeof(_Tp)));
      }
```
`_GLIBCXX_NODISCARD` expands to `[[nodiscard]]` which tells the compiler to
warn if the return value is not used.
This function returns `_Tp*` which means that it returns a pointer to the type
that we are allocating, which is speified in the template:
```c++
    std::allocator<int> alloc;
    int * ptr = alloc.allocate(5);
```
And `__n` is the number of elements we want to allocate.
The second parameter is a locality hint, which is used to specify a location
where the memory is likely to be used. Thi can be used like this:
```c++
    // just an example of using the locality hint parameter
    int* ptr2 = alloc.allocate(5, ptr);
```
The syntax for this really threw me off at first.
```c++
const void* = static_cast<const void*>(0)
```
Notice that this parameter does not have a name and it does nothing, it is just
an old relic from C++98. This was deprecated in C++17 and removed in C++20.

`__builtin_expect` is a GCC compiler intrinsic that help with branch prediction.
The following lines are equivalent:
```c++
if (__builtin_expect(__n > this->_M_max_size(), false))
if (__n > this->_M_max_size())
```
What `buildin_expect` does is to tell the compiler that the first argument is
likely to be false, so it can optimize the code for that case. This is useful

```c++
#if __has_builtin(__builtin_operator_new) >= 201802L
# define _GLIBCXX_OPERATOR_NEW __builtin_operator_new
# define _GLIBCXX_OPERATOR_DELETE __builtin_operator_delete
#else
# define _GLIBCXX_OPERATOR_NEW ::operator new
# define _GLIBCXX_OPERATOR_DELETE ::operator delete
#endif
```

### Versions
The format of versions is `YYYYMML` where YYYY is the year, MM is the month
and L is Long suffix (like can be used for integer literals that is).
* 201103L is C++11 (auto, smartpointers, nullptr, lambda)
* 201402L is C++14 (make_unique, generic lambdas)
* 201703L is C++17 (optional, string_view, std::variant)
* 202002L is C++20 (concepts, coroutines, ranges)
* 202300L is C++23 (std::expected, std::flat_map, std::flat_set)


### c++config.h
This file is included in many of the standard library headers and is located
in: 
```console
$ find /usr/ -name 'c++config.h'
/usr/include/x86_64-linux-gnu/c++/13/bits/c++config.h
```

You can find most of the macros that are specific to the compiler and the current
platform in this file.

One reason for the many usages of macros is to enable backwards compatibility
with older versions of the standard library. This can be good to keep in mind
when reading the code as it can seem a bit messy at times I think.
For example in stl_vector.h we have:
```c++
namespace std _GLIBCXX_VISIBILITY(default)
```
```c++
#if _GLIBCXX_HAVE_ATTRIBUTE_VISIBILITY
# define _GLIBCXX_VISIBILITY(V) __attribute__ ((__visibility__ (#V)))
#else
// If this is not supplied by the OS-specific or CPU-specific
// headers included below, it will be defined to an empty default.
# define _GLIBCXX_VISIBILITY(V) _GLIBCXX_PSEUDO_VISIBILITY(V)
#endif
```
```c++
namespace std __attribute__ ((__visibility__ ("default")))
{
    class vector { ... };
}
```
* default symbols are exported and visible to other libraries/programs.
* hidden symbols are not visible to other libraries/programs.
* protected symbols are exported but can also be overridden by other libraries/programs.


#### Library
So bin/vector used std::vector and is linked against the standard library:
```
$ ldd bin/vector
	linux-vdso.so.1 (0x000075813e1b8000)
	libstdc++.so.6 => /lib/x86_64-linux-gnu/libstdc++.so.6 (0x000075813de00000)
	libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x000075813e168000)
	libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x000075813da00000)
	libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x000075813e07f000)
	/lib64/ld-linux-x86-64.so.2 (0x000075813e1ba000)
```
Now, one might think that we should be able to see std::vector symbols in
libstdc++.so.6, but that is not the case. The reason is that the vector is
almost entirely implemented in the header files, so the compiler will inline
the code and the symbols will not be in the library. So they will be in the
executable instead. We can see this by using `nm`:
```console
$ objdump -t bin/vector | c++filt | grep -i vector
bin/vector:     file format elf64-x86-64
0000000000000000 l    df *ABS*	0000000000000000              vector.cpp
0000000000001996  w    F .text	0000000000000045              std::_Vector_base<int, std::allocator<int> >::_Vector_impl::_Vector_impl(std::allocator<int> const&)
000000000000164a  w    F .text	0000000000000028              std::_Vector_base<int, std::allocator<int> >::_Vector_impl::~_Vector_impl()
0000000000001a44  w    F .text	000000000000004d              std::_Vector_base<int, std::allocator<int> >::_M_allocate(unsigned long)
0000000000001532  w    F .text	000000000000005a              std::vector<int, std::allocator<int> >::~vector()
000000000000173e  w    F .text	00000000000000f1              void std::vector<int, std::allocator<int> >::_M_range_initialize<int const*>(int const*, int const*, std::forward_iterator_tag)
000000000000169c  w    F .text	0000000000000051              std::_Vector_base<int, std::allocator<int> >::~_Vector_base()
0000000000001c02  w    F .text	0000000000000032              std::_Vector_base<int, std::allocator<int> >::_Vector_impl_data::_Vector_impl_data()
000000000000164a  w    F .text	0000000000000028              std::_Vector_base<int, std::allocator<int> >::_Vector_impl::~_Vector_impl()
00000000000019dc  w    F .text	0000000000000052              std::_Vector_base<int, std::allocator<int> >::_M_deallocate(int*, unsigned long)
0000000000001532  w    F .text	000000000000005a              std::vector<int, std::allocator<int> >::~vector()
0000000000001996  w    F .text	0000000000000045              std::_Vector_base<int, std::allocator<int> >::_Vector_impl::_Vector_impl(std::allocator<int> const&)
0000000000001842  w    F .text	00000000000000a3              std::vector<int, std::allocator<int> >::_S_check_init_len(unsigned long, std::allocator<int> const&)
000000000000146c  w    F .text	00000000000000c6              std::vector<int, std::allocator<int> >::vector(std::initializer_list<int>, std::allocator<int> const&)
0000000000001c02  w    F .text	0000000000000032              std::_Vector_base<int, std::allocator<int> >::_Vector_impl_data::_Vector_impl_data()
000000000000169c  w    F .text	0000000000000051              std::_Vector_base<int, std::allocator<int> >::~_Vector_base()
00000000000018e6  w    F .text	0000000000000065              std::_Vector_base<int, std::allocator<int> >::_Vector_base(unsigned long, std::allocator<int> const&)
0000000000001b72  w    F .text	000000000000005a              std::_Vector_base<int, std::allocator<int> >::_M_create_storage(unsigned long)
00000000000018e6  w    F .text	0000000000000065              std::_Vector_base<int, std::allocator<int> >::_Vector_base(unsigned long, std::allocator<int> const&)
0000000000001830  w    F .text	0000000000000012              std::_Vector_base<int, std::allocator<int> >::_M_get_Tp_allocator()
000000000000158c  w    F .text	0000000000000086              std::vector<int, std::allocator<int> >::vector(unsigned long, int const&, std::allocator<int> const&)
0000000000001672  w    F .text	000000000000002a              std::_Vector_base<int, std::allocator<int> >::_Vector_base(std::allocator<int> const&)
000000000000146c  w    F .text	00000000000000c6              std::vector<int, std::allocator<int> >::vector(std::initializer_list<int>, std::allocator<int> const&)
000000000000194c  w    F .text	0000000000000049              std::vector<int, std::allocator<int> >::_M_fill_initialize(unsigned long, int const&)
000000000000158c  w    F .text	0000000000000086              std::vector<int, std::allocator<int> >::vector(unsigned long, int const&, std::allocator<int> const&)
0000000000001af0  w    F .text	0000000000000081              std::vector<int, std::allocator<int> >::_S_max_size(std::allocator<int> const&)
0000000000001672  w    F .text	000000000000002a              std::_Vector_base<int, std::allocator<int> >::_Vector_base(std::allocator<int> const&)
0000000000001612  w    F .text	0000000000000027              std::vector<int, std::allocator<int> >::size() const
```
