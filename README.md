# CFGER

CFGER is a simple configuration parser written in c.It is written for the project manager PCKM configuration.

### NOTE: It is still running project and is not stable yet

## Installation
 To build CFGER, you need to have a make build system installed on your machine. Follow the steps below to build and install CFGER:

### Clone the Repository:
```sh
git clone https://github.com/Saugat913/cfger.git
cd cfger
```
### Build the Project:

Run the following command in the project directory:

```sh
make all
```
This will compile the source files, create the static library, and move the necessary header files to the build directory.

### Clean the Build:

To clean the build artifacts, run:

``` sh
make clean
```

## Usage
After building the project, you can link the libcfger.a library in your own projects by including the headers located in the build/include/cfger directory.

To link against the library, add the following flags to your compilation command:

```sh

-Ipath/to/build/include -Lpath/to/build/lib -lcfger
```
Replace path/to/build with the actual path to the build directory.


## Example

```c
#include "cfger/config.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{

    cfger_Config config = cfger_parse_config_file("config.txt");

    if (config == NULL)
    {
        printf("ERROR while opening file\n");
        return 1;
    }

    cfger_Section new_test_section = cfger_create_section("test", config);

    cfger_set_str_value("key1", "value1", new_test_section);

    cfger_display_config(config);

    cfger_destroy_config(config);

    return 0;
}
```
Example is in example folder and can be build and run using command.
```shell
make example
./example/example
```


## Limitation 
[x] Configuration file doesnot support comment.

[x] Only string value is supported for key value.