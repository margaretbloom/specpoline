# specpoline
Test specpoline in recent Intel processors under Linux

Use `make run_spec` to execute a store in the speculative path of the specpoline.
Use `make run_arch` to execute a store in the architectural path of the specpoline.

The store is fixed as the first location (index 0) of a Flush+Reload buffer.

The program shows the timing<sup>1</sup> of each of the 256 entries of the Flush+Reload buffer.

<sup>1</sup> WARNING: The timing is in CORE CYCLES not TSC (wallclock) cycles but the difference should still be noticeable.

