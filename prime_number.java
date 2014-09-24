/*
http://n00tc0d3r.blogspot.com/2013/08/prime-numbers.html
Prime Numbers
*/

/*
Problem 1: Find All Prime Numbers
Given a number n, print all primes smaller than or equal to n. It is also given that n is a small number.

For example, if n is 10, the output should be ¡°2, 3, 5, 7¡å. If n is 20, the output should be ¡°2, 3, 5, 7, 11, 13, 17, 19¡å.
Solution
A Prime number is a natural number which has exactly two distinct natural number divisors: 1 and itself.

A naive solution is for each number k <= n check whether k is divisible by any number less than k. If not, mark it as a prime number. Obviously, this algorithm takes O(n^2) time.

Let's take another view point of this problem.

Finding all prime numbers is equivalent to find the remaining numbers after removing non-prime numbers. That is, if we remove all even numbers, then all multiples of 3, all multiples of 5, ..., eventually, the remaining numbers are the prime numbers.
*/
 public void printPrimes(int n) {  
   if (n < 2)  return; // A prime number must be >= 2.
   boolean[] flags = new boolean[n+1]; // by default initialized to false  
   
   int rootN = (int)Math.sqrt(n);  
   for (int i=2; i<=rootN; ++i) {  // [1]
     // flags[i]==true means it has been marked before and thus all its multiples can be skipped
     if (!flags[i]) {  
       // Note: if we get here, i itself is a prime number

       // mark its multiples
       for (int j=i*i; j<=n; j+=i) {  // [2]
         flags[j] = true;  
       }  
     }  
   }  
   
   // print all primes  
   System.out.println("Prime numbers less than " + n + ":");  
   for (int i=2; i<=n; ++i) {  
     if (!flags[i]) System.out.print(i + ", ");  
   }  
 }

/* 
There are two small optimizations as marked in the code:
Since n = sqrt(n) * sqrt(n), for any number greater than sqrt(n), it is either a prime number or it is a multiple of some number that is no greater than sqrt(n).
Proof: Suppose there is a number, say k<=n, such that it is not a prime number and it is > sqrt(n) and it is not a multiple of any number <= sqrt(n). Then it must has at least two divisors such that both of them are > sqrt(n). It implies that k > n, which is a contradiction to our assumption.
Similarly, to mark all multiples of i (except itself since it itself is a prime number :), we can start from i*i since for any i*j, where 1<j<i, must have been taken care of in previous rounds.
With these optimizations, each number will be marked at most once. Thus, this algorithm runs in time O(n).
For prime numbers > sqrt(n), it touches each once for printing;
For numbers <= sqrt(n), it touches each at most twice, for marking and maybe printing.
Update (thanks to Keith): With these optimizations, each number will be marked k_i times, where k_i is the number of prime factors of the number i. E.g. 12 -- two times, one for 2 and the other for 3; 105 - 3 times, one for 3, one for 5 and one for 7.
In total, there are n numbers, for each prime x, we will mark n/x numbers, i.e. the total running time T(n) = n*(1/2 + 1/3 + 1/5 + ...) = n * sum_{i = all primes less than n} (1 / i). This series is called, Prime Harmonic Series, which has been proved to be asymptotic to loglogn. Therefore, the total running time T(n) = O(n*loglogn).

This algorithm takes O(n) spaces.

This algorithm is called Sieve of Eratosthenes.
*/

/*
Problem 2: Is it a Prime Number?
Given number n, return true if n is prime otherwise false.
Solution
To verify whether a number is a prime number, we need to check whether it has any divisor other than itself and > 1.

As proved in previous problem, instead of searching divisor among all numbers in (2..n), we only need to check numbers in [2..sqrt(n)].
*/
 public boolean isPrime(int n) {  
   if (n < 2) return false; // prime must >=2  
   if (n == 2) return true;  
   if ((n & 1) == 0) return false; // prime must not be even  
   
   int rootN = (int)Math.sqrt(n);  
   for (int i=2; i<=rootN; ++i) {  
     if (n % i == 0) return false;  
   }  
   return true;  
 }
 
/* 
This algorithm runs in time O(sqrt(n)) and uses O(1) space.
*/

/*
Problem 3: Find All Prime Factors
Given a number n, print all prime factors of n.

For example, if the input number is 12, then output should be ¡°2 2 3¡å. And if the input number is 315, then output should be ¡°3 3 5 7¡å.
Solution
After completing the previous problems, the intuitive solution for this problem is to first find all prime numbers less than sqrt(n) and then iterate through those numbers to find all factors of n.

Finding all prime numbers less than sqrt(n) takes O(sqrt(n)) time and space. Do we really need to find all prime numbers?

No. If we divide n by factors we found, for any following non-prime numbers, they will not be a divisor of n. For example, if we already check 2 and 3 and "remove" them from n, then (n % 6) must not equal 0.
*/

 public static void printPrimeFactors(int n) {  
   if (n < 2) return ; // prime must >=2  
     
   System.out.println("Prime factors of " + n + ":");  
   
   while ((n & 1) == 0) {  
     System.out.print(2 + " ");  
     n /= 2;  
   }  
   
   int rootN = (int)Math.sqrt(n);  
   for (int i=3; i<=rootN; ++i) {  
     while (n % i == 0) {  
       System.out.print(i + " ");  
       n /= i;  
     }  
   }  
   
   if (n > 2) { // there is at most one prime factor > sqrt(n)  
     System.out.print(n);  
   }  
 }  
/* 
This algorithm runs in O(m) time where m is the number of prime factors.
*/