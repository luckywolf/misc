int mem[maxn];
const int size = 8 * sizeof(int);
void set(int x) {
  mem[x / size] |= (1 << (x % size))
}
int get(int x) {
  return mem[x / size] & (1 << (x % size));
}
