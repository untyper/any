# any

Single header C++11 compatible "any" implementation

## Example

```cpp
#include "any.hpp"

/*...*/

std::string name = "Lelouch";
any emperor = name;

std::cout << "All hail emperor " << emperor.as<std::string>() << "!";

// prints: "All hail emperor Lelouch!"
```

## License
[Boost Software License 1.0](LICENCE)
