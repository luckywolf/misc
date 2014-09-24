/*
Given a method that takes in a positive non-zero number N, 
return from that method the total number of factors of N.  

4 = 1, 2, 4
27 =  1, 3, 9 
36 = 1, 2, 3, 4, 6,       9, 12, 18, 36
*/

vector<int> fatctor(int n) {
    assert(n >= 1);
    vector<int> res;
    for (int i = 1; i <= sqrt(n); ++i) { 
        if (n % i == 0) {
            res.push_back(i);
            if (i != sqrt(n)) {
                res.push_back(n / i);
            }
        }
    }
    return res;
}