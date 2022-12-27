## USAGE of Calculate Mahjong Score (CMS.c)

This Program can calculate Mahjong Score with rank Uma.

### 1.  Make Text File  with Following Format:

-   In input text file (#define MJ_TXT)

```txt
name1 point1
name2 point2
name3 point3
name4 point4
```

-   you can insert tab(\\t) instead of space between name and point.

### 2.  Select UMA Mode (#define MODE_UMA)

-   In CMS.c

```c
mode 515: 5-15
mode 1020: 10-20
mode 1030: 10-30
```

### 3.  Check Options

-   In CMS.c, of course you can change these options.

```c
#define START_POINT 25000
#define TH_POINT 30000
#define MJ_TXT_INPUT "./input/mj_input.txt"
#define MJ_TXT_OUTPUT "./output/mj_output.txt"
#define MJ_TXT_OUTPUT_TIME "./output/mj_output_%y%m%d_%H%M_%S.txt"
```

-   Also You should check Uma Mode, but you can change in compile time(4.).

### 4.  You Can Change UMA Mode When Compile This File (Optional)

-   Default Uma settings is 5-15.
-   You can change Uma setting following this. command

|  command (gcc -D) | uma_low | uma_high |
| :---------------: | :-----: | :------: |
| 1 or 515(default) |    5    |    15    |
|     2 or 1020     |    10   |    20    |
|  3 or 1030 or 'M' |    10   |    30    |
|     4 or 2030     |    20   |    30    |

-   In your shell, you can use gcc -D option to setting UMA
    -   ex)

```sh
$gcc -D MODE_UMA=1020 mj_calc.c -o mj_calc
$gcc mj_calc.c -D "MODE_UMA='M'"
```

### 5.  Compile and Run

## Output File is Created  with Following Format:

-   In text file (#define MJ_TXT_OUTPUT) + timestamp

```txt
Time: YYYY/MM/DD HH:MM:SS ----DAY
Uma: x-yy

rank:   name    : point : score
[1] : name1 : point1 : score1
[2] : name2 : point2 : score2
[3] : name3 : point3 : score3
[4] : name4 : point4 : score4
```
