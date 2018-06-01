# Build

`cd ./src && make && cd ..`

# Usage

```$ echo "-1.2 1000000.5 3.4 1000000.5 1000000.5" | ./bin/duplicates /dev/stdin
<1>
(3) 1000000.5```

```$ echo "-1 33 44 42 -2 33 44 -2 44 44" | ./bin/duplicates /dev/stdin
<3>
(2) -2    (2) 33    (4) 44```

```$ ./bin/duplicates ./test/inputs/case-02
<2>
(2) -132394    (2) 6```
