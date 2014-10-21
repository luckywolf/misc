/* 
 * Given a file containing all possible numbers on a 32-bit architecture, 
 * 4 numbers are missing. Find the 4 missing numbers. 
 */

/* Use a bitmap to represent all 32-bit integers, we need 2^32 / 8 =  2^29 B =  512MB memory.
Suppose we only have 64MB = 2^26 B, we can have two methods:
1) read the given file  2^29 / 2^26 = 8 times; each time covers 1/8 range of integers.
2) write the given file to 8 small files, each file covers 1/8 range of integers.
In both cases, a bitmap (use all 512MB memory) can represent the last 29 bits 
(2^29 / 8 = 2^26B= 64MB) of the each integer.
Depends on the read from vs write to disk speed, and the disk space (method 2 needs double disk
space), we can decide which method is better.

Suppose we use method 1, the pseudo code is as below:
*/

#include <fstream>
using namespace std;
const int memSize = 0x1 << 26;
int mem[memSize];
const int mask = (0x1 << 29) - 1; // clear the first 3 bits

const int wordSize = 8 * sizeof(int);
void setBit(int x) {
  mem[x / wordSize] |= (1 << (x % wordSize));
}
int getBit(int x) {
  return mem[x / wordSize] & (1 << (x % wordSize));
}

vector<int> findFourMissingNumbers(string inFilePath) {
    vector<int> res;
    ofstream inFile(inFilePath, ios::in);
    int nextInt = 0;
    for (int i = 0; i < 8; ++i) { // read input file 8 times
        inF.clear();
        inF.seekg(0, ios::beg);
        memset(mem, 0, sizeof(mem));
        while (inf >> nextInt) { // pseudo code to get next integer
            nextInt &= mask;
            setBit(nextInt);
        }
        for (int j = 0; j <= mask; ++j) {
            if (getBit(j) == 0) {
                res.push_back((i << 29) | j);
                if (res.size() == 4) {
                    inF.close();
                    return res;
                }
            }
        }
    }
    inF.close();
    return res;
}

