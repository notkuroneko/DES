# DES (Data Encryption Standard) Algorithm
- Input: 64-bit Plaintext, 64-bit Key
- Output: 64-bit Cyphertext

# The Algorithm:
![The overall algorithm](https://github.com/notkuroneko/DES/assets/133151430/a67ed51c-72a6-419f-bf4f-6c3183af9dbc)

Step 1: 
- Plaintext Initial Permutation: Create a 64-bit permutated stream from the following permutation table: 
<pre>
            58    50   42    34    26   18    10    2 
            60    52   44    36    28   20    12    4
            62    54   46    38    30   22    14    6 
            64    56   48    40    32   24    16    8 
            57    49   41    33    25   17     9    1 
            59    51   43    35    27   19    11    3 
            61    53   45    37    29   21    13    5 
            63    55   47    39    31   23    15    7 
</pre>
- Key Initial Permutation: Create a 56-bit permutated stream from the following permutation table: 
<pre>
            57   49    41   33    25    17    9 
             1   58    50   42    34    26   18 
            10    2    59   51    43    35   27 
            19   11     3   60    52    44   36 
            63   55    47   39    31    23   15 
             7   62    54   46    38    30   22 
            14    6    61   53    45    37   29 
            21   13     5   28    20    12    4 
</pre>
Step 2: Round function with 16 iterations
- Key: <br/>
![Keystream generation per iteration](https://github.com/notkuroneko/DES/assets/133151430/f60fffa9-26c5-41a8-8d24-5c62ac941cab)
  + Divide the 56-bit keystream into 2 halves of 28 each
  + Shift each half to the left, 1 bit for the 1st, 2nd, 9th, 16th iteration, and 2 bits for the remaining iterations.
  + Create a 48-bit keystream from the following permutation table:
<pre>
            14    17   11    24     1    5
            3     28   15     6    21   10
            23    19   12     4    26    8
            16     7   27    20    13    2
            41    52   31    37    47   55
            30    40   51    45    33   48
            44    49   39    56    34   53
            46    42   50    36    29   32
</pre>
- Cyphertext Stream: <br/>
![An iteration of the round function](https://github.com/notkuroneko/DES/assets/133151430/fa0072ea-4135-4b4a-a2c3-a78d79b905a1)
  + Divide the 64-bit plaintext stream into 2 halves of 32 each
  + Create a 48-bit permutated stream of the right half from the following permutation table (P-Expansion Box):
<pre>
            32     1    2     3     4    5
             4     5    6     7     8    9
             8     9   10    11    12   13
            12    13   14    15    16   17
            16    17   18    19    20   21
            20    21   22    23    24   25
            24    25   26    27    28   29
            28    29   30    31    32    1
</pre>
  + Bitwise XOR the 48-bit permutated stream with the 48-bit keystream
  + Divide the new stream into 8 streams of 6 each. For every 6 bits, take the first bit and the last bit and convert into decimal to get the row index, and take the remaining bits and convert into decimal to get the column index. Obtain the value in the S-box from the indexes and convert into binary. Use the S(i)-box for the i-th stream and form a 32-bit stream from these tables:
<pre>
                             S1

     14  4  13  1   2 15  11  8   3 10   6 12   5  9   0  7
      0 15   7  4  14  2  13  1  10  6  12 11   9  5   3  8
      4  1  14  8  13  6   2 11  15 12   9  7   3 10   5  0
     15 12   8  2   4  9   1  7   5 11   3 14  10  0   6 13

                             S2

     15  1   8 14   6 11   3  4   9  7   2 13  12  0   5 10
      3 13   4  7  15  2   8 14  12  0   1 10   6  9  11  5
      0 14   7 11  10  4  13  1   5  8  12  6   9  3   2 15
     13  8  10  1   3 15   4  2  11  6   7 12   0  5  14  9

                             S3

     10  0   9 14   6  3  15  5   1 13  12  7  11  4   2  8
     13  7   0  9   3  4   6 10   2  8   5 14  12 11  15  1
     13  6   4  9   8 15   3  0  11  1   2 12   5 10  14  7
      1 10  13  0   6  9   8  7   4 15  14  3  11  5   2 12

                             S4

      7 13  14  3   0  6   9 10   1  2   8  5  11 12   4 15
     13  8  11  5   6 15   0  3   4  7   2 12   1 10  14  9
     10  6   9  0  12 11   7 13  15  1   3 14   5  2   8  4
      3 15   0  6  10  1  13  8   9  4   5 11  12  7   2 14

                             S5

      2 12   4  1   7 10  11  6   8  5   3 15  13  0  14  9
     14 11   2 12   4  7  13  1   5  0  15 10   3  9   8  6
      4  2   1 11  10 13   7  8  15  9  12  5   6  3   0 14
     11  8  12  7   1 14   2 13   6 15   0  9  10  4   5  3

                             S6

     12  1  10 15   9  2   6  8   0 13   3  4  14  7   5 11
     10 15   4  2   7 12   9  5   6  1  13 14   0 11   3  8
      9 14  15  5   2  8  12  3   7  0   4 10   1 13  11  6
      4  3   2 12   9  5  15 10  11 14   1  7   6  0   8 13

                             S7

      4 11   2 14  15  0   8 13   3 12   9  7   5 10   6  1
     13  0  11  7   4  9   1 10  14  3   5 12   2 15   8  6
      1  4  11 13  12  3   7 14  10 15   6  8   0  5   9  2
      6 11  13  8   1  4  10  7   9  5   0 15  14  2   3 12

                             S8

     13  2   8  4   6 15  11  1  10  9   3 14   5  0  12  7
      1 15  13  8  10  3   7  4  12  5   6 11   0 14   9  2
      7 11   4  1   9 12  14  2   0  6  10 13  15  3   5  8
      2  1  14  7   4 10   8 13  15 12   9  0   3  5   6 11       
</pre>
![S-box rule](https://github.com/notkuroneko/DES/assets/133151430/5db1bd17-9d11-40bd-8167-e534d3649ee8)

  + Bitwise XOR the 32-bit stream with the left half of the original stream.
  + Create a new 64-bit stream that concatenates the right half of the original stream and the 32-bit stream obtained from the last step. <br/><br/>
Step 3: <br/> Swap the left half and the right half of the final 64-bit stream and create the 64-bit cyphertext stream from the following permutation table (Straight-P Box):
<pre>
            40     8   48    16    56   24    64   32
            39     7   47    15    55   23    63   31
            38     6   46    14    54   22    62   30
            37     5   45    13    53   21    61   29
            36     4   44    12    52   20    60   28
            35     3   43    11    51   19    59   27
            34     2   42    10    50   18    58   26
            33     1   41     9    49   17    57   25
</pre>

# Decryption Algorithm (idea only)
Input: 64-bit Cyphertext, 64-bit Key
Output: 64-bit Plaintext
Step 1: 
- Create a 64-bit stream from the indexes of the final permutation table an swap the left half with the right half of that stream.
- Repeat Key Initial Permutation
Step 2: Reverse Round Function with 16 iterations
- Key:
+ Divide the 56-bit key into 2 halves of 28 each
+ Shift each half to the right, 1 bit for the 1st, 7nd, 15th, 16th iteration, and 2 bits for the remaining iterations.
+ Create a 48-bit keystream from the keystream permutation table
- Plaintext Stream: Since the left half of an iteration is the right half of the previous iteration, we can reverse the round function to trace back the left half of the previous iteration.
+ Divide the cyphertext stream into 2 halves of 32 each
+ Create a 48-bit stream of the left half from the P-Expansion Box and bitwise XOR it with the 48-bit keystream.
+ Repeat the S-box step to obtain the 32-bit stream and bitwise XOR it with the right half.
+ Create a 64-bit stream from the 32-bit stream from the last step and the left half, and permute it with the indexes of the Straight-P Box.
Step 3: Create the 64-bit plaintext stream from the indexes of the plaintext initial permutation table.

Original Source: https://page.math.tu-berlin.de/~kant/teaching/hess/krypto-ws2006/des.htm
