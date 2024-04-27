## gtest linking and shared libraries
This examples tries show an issue when linking with gtest and shared libraries.

The idea is to have a shared library `a` that uses a shared library `b`. And
the we have a unit test that tests the shared library `a`. The unit test does
not link directly to the shared library `b` which is something to keep in mind
when we inspect the `a_test` binary.

### Pre-requisites
```console
$ make install_gtest
```

### Building
We can build using
```console
$ make a_test
```

### Running
```console
$ ./a_test
```

### Inspecting the libraries and binary
Lets start with libb.so which should not have any links apart from the standard
libraries:
```console
$ ldd libb.so 
	linux-vdso.so.1 (0x00007ffd6cbf5000)
	libstdc++.so.6 => /lib/x86_64-linux-gnu/libstdc++.so.6 (0x0000773af7000000)
	libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x0000773af6c00000)
	libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x0000773af6f19000)
	/lib64/ld-linux-x86-64.so.2 (0x0000773af72ef000)
	libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x0000773af72b4000)
```
`linux-vsdo` is a virtual library (notice that it is not associated with a file)
that is automatically mapped in the virtual address space of a process by the
kernel. This is a virtual dynamic shared object (vdso) and is a small library
that the kernel maps into the virtual address space of all user processes. The
motivation for this is that there are some system calls that are used very
often, enough to cause a performace issue with having to switch into kernel
mode. An example of a frequently called function is gettimeofday which can be
called directly from user code and also is called from the c library. 

`libstdc++` is the C++ standard library and `libc.so` is the C standard
`/lib64/ld-linux-x86-64.so.2` is the program interpreter (0x0000773af72ef000)
`libgcc_s.so.1` is the `GNU C Library` which is a library that contains support
functions for the GNU Compiler Collection (GCC).

So we only have those standard libraries linked to `libb.so`.

Now lets inspect `liba.so` (I've moved libb.so to the end so make it easier to
see the difference):
```console
$ ldd liba.so 
	linux-vdso.so.1 (0x00007ffee0f7a000)
	libstdc++.so.6 => /lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007e3d67800000)
	libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007e3d67400000)
	libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007e3d67719000)
	/lib64/ld-linux-x86-64.so.2 (0x00007e3d67ade000)
	libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007e3d67a9e000

	libb.so (0x00007e3d67ad2000)
```
So that looks like what we wanted and expected that liba.so is linked to
libb.so.

Now, lets look at a_test:
```console
$ ldd a_test
	linux-vdso.so.1 (0x00007ffe7733e000)
	libstdc++.so.6 => /lib/x86_64-linux-gnu/libstdc++.so.6 (0x000078c08f600000)
	libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x000078c08f519000)
	libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x000078c08f8ba000)
	libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x000078c08f200000)
	/lib64/ld-linux-x86-64.so.2 (0x000078c08f98d000)

	liba.so (0x000078c08f8ee000)
	libb.so (0x000078c08f8b3000)
```
So notice that even though we did not link directly to libb.so, it is still
linked to the binary. 

Now, keep in mind that `ldd` is a script that runs the program interpreter
(`/lib64/ld-linux-x86-64.so.2`) with the binary as an argument. It is not
reporting information from the binary itself but it is using information in the
dynamic section of the binary:
```console
$ readelf -d a_test

Dynamic section at offset 0x95640 contains 31 entries:
  Tag        Type                         Name/Value
 0x0000000000000001 (NEEDED)             Shared library: [liba.so]
 0x0000000000000001 (NEEDED)             Shared library: [libstdc++.so.6]
 0x0000000000000001 (NEEDED)             Shared library: [libm.so.6]
 0x0000000000000001 (NEEDED)             Shared library: [libgcc_s.so.1]
 0x0000000000000001 (NEEDED)             Shared library: [libc.so.6]
...
```
Notice that `a_test` has a `NEEDED` entry for `liba.so` but not for `libb.so`.
When the program interpreter identifies a direct dependency, like `liba.so`, it
will recursively look for the dependencies of `liba.so`:
```console
$ readelf -d liba.so 

Dynamic section at offset 0x2df0 contains 26 entries:
  Tag        Type                         Name/Value
 0x0000000000000001 (NEEDED)             Shared library: [libb.so]
 0x0000000000000001 (NEEDED)             Shared library: [libstdc++.so.6]
 0x0000000000000001 (NEEDED)             Shared library: [libc.so.6]
 ...
```
And it will do the same for `libb.so`:
```console
$ readelf -d libb.so 

Dynamic section at offset 0x2e00 contains 25 entries:
  Tag        Type                         Name/Value
 0x0000000000000001 (NEEDED)             Shared library: [libstdc++.so.6]
 0x0000000000000001 (NEEDED)             Shared library: [libc.so.6]
 ...
```
This will provide a complete list of of all shared libraries that a program
depends on.


[program startup]: https://github.com/danbev/learning-linux-kernel?tab=readme-ov-file#program-startup
