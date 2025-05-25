## Profiling notes

### perf
Running `perf record` on a binary that uses `libstdc++` might fail with:
```console
$ perf record -g ./bin/iterator
Error:
Access to performance monitoring and observability operations is limited.
Consider adjusting /proc/sys/kernel/perf_event_paranoid setting to open
access to performance monitoring and observability operations for processes
without CAP_PERFMON, CAP_SYS_PTRACE or CAP_SYS_ADMIN Linux capability.
More information can be found at 'Perf events and tool security' document:
https://www.kernel.org/doc/html/latest/admin-guide/perf-security.html
perf_event_paranoid setting is 4:
  -1: Allow use of (almost) all events by all users
      Ignore mlock limit after perf_event_mlock_kb without CAP_IPC_LOCK
>= 0: Disallow raw and ftrace function tracepoint access
>= 1: Disallow CPU event access
>= 2: Disallow kernel profiling
To make the adjusted perf_event_paranoid setting permanent preserve it
in /etc/sysctl.conf (e.g. kernel.perf_event_paranoid = <setting>)
```
This is a security restriction on linux and can be changed by running:
```console
$ sudo sysctl -w kernel.perf_event_paranoid=1
[sudo] password for danbev:
kernel.perf_event_paranoid = 1
```

Running:
```console
$ perf record -g ./bin/iterator
````
This will generate a report which can then be viewed with:
```console
$ perf report
```

Hotspot can also be used to visualize the performance data:
```console
$ sudo apt install hotspot
```
And then just run:
```console
$ hotspot
```
