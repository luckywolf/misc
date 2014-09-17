/*
http://cs-technotes.blogspot.com/2010/11/find-second-largest-number-in-array.html?view=sidebar

write a function to return the second largest number in an array
 Method 1: brute force
round 1: put the largest number to the tail x[n-1]
round 2: find the max from x[0..n-2]
time complexity: 2n -3
Code: 
*/
int secondLargest(int* arr)
{
    if(!arr)
        return -1;
    int* head = arr;
    int len=0;
    while((head+1) != NULL)
    {
        if(*head >*(head+1))
        {
            int t=*head;
            *head = *(head+1);
            *(head+1) = t;
        }
        head++;
        len++;
    }

    int secMax = *arr;
    for(int i=1;i<len-1;i++)
    {
        if(*(arr+i)>secMax)
            secMax = *(arr+i);
    }
    return secMax;    
}

/*
 Method 2: tournament 
the second largest number must be compared to the largest number.
find the largest one from the losers of the largest number
Code:
*/