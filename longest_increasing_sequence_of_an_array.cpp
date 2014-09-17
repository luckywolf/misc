/*
http://cs-technotes.blogspot.com/2010/12/longest-increasing-sequence-of-array.html?view=sidebar

Given an integer array, return the longest increasing sequence, for instance: for the array {1,3,2,4,3,5,4,6}, the longest increasing sequence is {1,3,4,5,6} 
Algorithm: it's a dynamic programming problem, slightly different to longest common sequence.
scan the array, for each integer a_i, compare it with all previous integers [a_0...a_i-1], if it's larger than a_j, then the length of the sequence that ends with a_j can increase one by adding a_i to that sequence. 
Therefore, we need one array(s in below code) to record the current max length of sequences which ends with a_i, and we also need one array(path in below code) to record the previous integer's position so that we can print the longest increasing sequence.
Code:
*/

 void printpath(int *arr, int *path, int end)
{
    if(end> -1){
        printpath(arr,path,path[end]);
        printf("%d ",arr[end]);
    }
}
void longestincreasingsequence(int *arr, int n)
{
    int *s = new int[n];    //current max number of ints  
    int *path = new int[n]; //previous number
    memset(path,0,n);

    int global_max = 1;        //at least one number
    int end_pos = 0;

    s[0]= 1;
    path[0]= -1;
    for(int i=1;i<n;i++){
        int local_prev = -1;
        s[i] = 1;
        for(int j=0;j<i;j++){
            if(arr[j]<arr[i] && s[i]<(s[j]+1)){
                s[i]= s[j]+1;
                local_prev = j;
            }
        }

        path[i] = local_prev;
        if(global_max < s[i]){
            global_max = s[i];
            end_pos = i;
        }
    }

    printf(" size of longest seq : %d \n",global_max);
    printpath(arr,path,end_pos);
    printf("\n");
    delete(path);
    delete(s);
}

/*
Question:
for above algorithm, the return sequence is {1,3,4,5,6}, however, {1,2,3,4,6} is also a candidate, as well as {1,2,4,5,6}. Why it can't find these two sequences?
I think this algorithm sort of like greedy algorithm. It can find one optimal solution, not enumerate every optimal solution. Need to prove it.
*/