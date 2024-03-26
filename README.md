# DES (Data Encryption Standard) Algorithm
- Input: 64-bit Plaintext, 64-bit Key
- Output: 64-bit Cyphertext

# The Algorithm:
Step 1: 
- Plaintext Initial Permutation: Create a 64-bit permutated stream from the following permutation table: <br/>
<pre>
            58    50   42    34    26   18    10    2 <br/>
            60    52   44    36    28   20    12    4 <br/>
            62    54   46    38    30   22    14    6 <br/>
            64    56   48    40    32   24    16    8 <br/>
            57    49   41    33    25   17     9    1 <br/>
            59    51   43    35    27   19    11    3 <br/>
            61    53   45    37    29   21    13    5 <br/>
            63    55   47    39    31   23    15    7 <br/>
</pre>
- Key Initial Permutation: Create a 56-bit permutated stream from the following permutation table: <br/>
<pre>
            57   49    41   33    25    17    9 <br/>
             1   58    50   42    34    26   18 <br/>
            10    2    59   51    43    35   27 <br/>
            19   11     3   60    52    44   36 <br/>
            63   55    47   39    31    23   15 <br/>
             7   62    54   46    38    30   22 <br/>
            14    6    61   53    45    37   29 <br/>
            21   13     5   28    20    12    4 <br/>
</pre>
Step 2: Round function with 16 iterations
- Key:
  + Divide the 56-bit keystream into 2 halves of 28 each
  + Shift each half to the left, 1 bit for the 1st, 2nd, 9th, 16th iteration, and 2 bits for the remaining iterations.
  + Create a 48-bit keystream from the following permutation table:
            14    17   11    24     1    5
            3     28   15     6    21   10
            23    19   12     4    26    8
            16     7   27    20    13    2
            41    52   31    37    47   55
            30    40   51    45    33   48
            44    49   39    56    34   53
            46    42   50    36    29   32
- Plaintext:
  + Divide the 64-bit plaintext stream into 2 halves of 32 each
  + Create a 48-bit permutated stream of the right half from the following permutation table:
            32     1    2     3     4    5
            4     5    6     7     8    9
            8     9   10    11    12   13
            12    13   14    15    16   17
            16    17   18    19    20   21
            20    21   22    23    24   25
            24    25   26    27    28   29
            28    29   30    31    32    1
  + 
            
  
Original Source: https://page.math.tu-berlin.de/~kant/teaching/hess/krypto-ws2006/des.htm
