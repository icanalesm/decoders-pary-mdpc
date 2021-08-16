# Decoders for p-ary MDPC

Implementation of the Gallager-type and Heuristic decoders for the p-ary MDPC scheme in [1]. This implementation was used to execute the experiments in [1].

## Compilation

Execute
```
make
```

This will create the `bin` directory which contains the executable files for the experiments.

## Execution

### Thresholds for the Gallager-type decoders

The Python script `gallager_estimation.py` is used to compute the thresholds for the decoder. These thresholds are specified in `decoder/gallager_thr.h`.

### Experiments

The executables for the Gallager-type decoders require the following mandatory parameters:
* `k`: size of the blocks of the parity-check matrix,
* `q`: modulo,
* `iter`: number of iterations for the decoding algorithm,

and the following optional parameters:
* `nmtx`: number of random MDPC instances (parity-check matrices) to generate,
* `imtx`: number of decodings per MDPC instance.

The executables for the Heuristic decoders require the following mandatory parameters:
* `k`: size of the blocks of the parity-check matrix,
* `q`: modulo,
* `iter`: number of iterations for the decoding algorithm,
* `delta`: decoding parameter,

and the following optional parameters:
* `nmtx`: number of random MDPC instances (parity-check matrices) to generate,
* `imtx`: number of decodings per MDPC instance.

The output comprises one line per execution of the decoding algorithm. These lines have the following format:
```
m    i    ds    nfail    nexp
```
where `m` is the current MDPC instance among all `nmtx`, `i` is the current decoding execution among all `imtx`, `ds` reports whether decoding was successful (`1`) or failure (`0`), `nfail` is the current total number of decoding failures and `nexp` is the current total number of decoding executions among all `nmtx` * `imtx`.

## References

[1] Canales-Martínez, Guo and Johansson. "Improved decoders for p-ary MDPC". 11th International Workshop on Coding and Cryptography - WCC 2019.
