# Hubbart

> NOTE: This project is brand new and the current version is probably not functional. It is strongly recommended not to use this code in production. As of January 13th, 2022, there is nothing in here.

**Hubbart** is a framework to accelerate the development of prototypes when several computing units are under consideration. A computing units refer to any IC (*Integrated Circuit*) that can perform computation, such as:

* CPU;
* GPU;
* SoC;
* Microcontroller;
* FPGA;
* DSP.

This will help areas using heterogeneous systems such as robotics or HPCs (*High-Performance Computer*).

## Use cases

The folder `usecases` will display script examples that we want to target for this framework.

## Parser implementation

* Importation statements
```Python
import math
from math import sqrt
```

* Instantiation statements
```Python
value : int = 16
approx : float = 2.0
```

* Arithmetic equations expression
```Python
tmp = (approx + value / approx) / 2
err = tmp - approx
```

* Boolean expression
```Python
err > 0.001
```

* Control structure
```Python
while (err > 0.001):
    # statements

if (value > 0):
    # statements

```

## Example : The Babilonnian algorithm for square roots

The phase one should be able to tackle algorithm similar to the babilonnian algorithm:

```Python
import Hubbart

# An undefined variable is a input
value: int

if (value >= 0):
    approx: float = 2.0
    tmp: float = (approx + value / approx) / 2
    err = tmp - approx
    while (err > 0.001):
        approx = tmp
        tmp = (approx + value / approx) / 2
        err = tmp - approx
    return (True, tmp)
else :
    return (False, 0)

```

