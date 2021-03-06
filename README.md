The code `make_koch_snowflake` generates instances of Koch's snowflake curve.

# Compilation

Any standard C compiler will do. E.g.:

    gcc -O2 -Wall -o make_koch_snowflake make_koch_snowflake.c -lm

# Usage

    make_koch_snowflake --number <N> --output <OUTPUTFILE> [--nested]

where N is a positive integer and OUTPUTFILE is the name of the output file.

# Generating polygonal data

The runtime-option "--number N" specifies the order of the snowflake curve.
For N=1 we simply get a triangle. The curve is written to the file named XYZ,
as specified in "--output XYZ". If the option "--nested" is given then the
code generates two copies of the snowflake curve, where the smaller copy forms
a hole inside the larger copy. E.g., for N=1 we get a triangle inside of a
triangle.

Please direct bug reports or suggestions to Martin Held at held@cs.sbg.ac.at.

# License

This is free software.  You may redistribute it and/or modify
it under the terms of the GNU General Public License (v3).
