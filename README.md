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
myVar : int = 2
myVar : float = 0.0
myVar : List[int] = [1, 5, 8]
myVar : MyObject = MyObject()
```

* Function Definition
```Python
def myFunction() -> int :
<indent><statements>

def myFunction(myParam: int) -> int :
<indent><statements>
```

* Class Definition
```Python
def MyClass:
<indent><__init__>
<indent><function_statements>
```

* Arithmetic equations expression
```Python
myVar = 5 + 3
myVar = myVar + 3
myVar = myVar - 3
```

* Boolean expression
```Python
True
myVar > 0
myVar < 4 and myVar >= 8
```