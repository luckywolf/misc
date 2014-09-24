/*
http://n00tc0d3r.blogspot.com/2013/08/implement-iterator-for-perfect-power.html?view=flipcard

Implement Iterator for Perfect Power Generator

Provide an implementation of the following interface: 
*/
public interface Powers extends Iterator<Long> { 
  /* Returns the next integer a in the arithmetic sequence of integers where 
   * a = m^n, m > 1, n > 1, and m and n are both integers 
   * Thus, the first few outputs will be 4, 8, 9, 16, 25, 27, 32, 36, etc. 
   */ 
  public Long next(); 

  /* Resets the sequence to the beginning, such that the next call to next() 
   * will return 4. 
   */ 
  public void reset(); 
}
/*
Solution

The key point of this problem is to find the next m^n.

One way is to maintain a min-heap of several power values of prime numbers.
At beginning, the heap only contains [2, 4]. It is ordered by power values (not base)
Next, return 4.
Inside the iterator, increase 4 to 8 by multiplying 2, i.e. remove heap top [2, 4] and add [2, 8].
Also find prime numbers between old heap top 4 and new heap top 8, which is 3.
Add [3, 9] to the heap.
Next, return 8.
Remove [2, 8] and add [2, 16].
Find prime numbers between 8 and 9, which is null.
Next, return 9.
Remove [3, 9] and add [3, 27].
Find prime numbers between 9 and 16, which are 5, 7, 11, and 13.
Add [5, 25], [7, 49], [11, 121], [13, 169] to the heap.
... ...
As we discussed in previous post, finding prime numbers under a given number n takes O(n) time. So, as next-value goes up, the running time of next method becomes O(n) where n is the returned value.
In the meantime, the size of the min-heap grows up too. As next-value goes up, the space complexity becomes O(m) where m is the number of primes under n.

Another way is to find the next-value on the fly, i.e find a perfect power between n and n*k where n is last return next-value and k is the corresponding base-value.

Given a number n, there are a couple of ways to test whether it is a perfect power.
Suppose n = a^b (b>1)
Method 1: We have logn = b*loga, i.e. b = logn/loga. So, for each 2 <= a < n/2, check whether logn/loga is an integer.
Assumes that Math.log runs in time O(logn). So this algorithm runs in time O(logn^2).
Method 2: We also have b < logn+1. So, we can use binary search to find a in [2, n/2) such that a^b == n.
There are logn b's and binary search over n/2 numbers takes time O(logn). So, this algorithm also runs in time O(logn^2).
So, the overall running time of next method is O(nlognlogn).
*/

 public class PowersImpl implements Powers {  
   private long next = 4;  
   private int base = 2;  

   /* b = logn/loga */
   private int isPerfectPower(long n) {  
     for (int a=2; a<n/2; ++a) {  
       double b = Math.log(n) / Math.log(a);  
       if (b - (int)b == 0) return a;  
     }  
     return -1;  
   }  

   /* binary search */
   public int isPerfectPower(long n) {  
     for (int b=2; b<(int)(Math.log(n)/Math.log(2)+1); ++b) {  
       long l = 2, r = n/2;  
       while (l <= r) {  
         long mid = l + (r - l) / 2;  
         long v = (long)Math.pow(mid, b);  
         if (v == n) return (int)mid;  
         if (v > n) {  
           r = mid - 1;  
         } else {  
           l = mid + 1;  
         }  
       }  
     }  
     return -1;  
   }  

   @Override  
   public Long next() {  
     long pre = next;  
     next = next*base;  
     for (long i=pre+1; i<next; ++i) {  
       int a = isPerfectPower(i);  
       if (a > 0) {  
         next = i;  
         base = j;  
         break;  
       }  
     }  
     return pre;  
   }  
   
   @Override  
   public void reset() {  
     next = 4; base = 2;  
   }  
 }  