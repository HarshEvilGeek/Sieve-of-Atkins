//
//  main.c
//  Atkins
//
//  Created by Akhil Verghese on 5/7/13.
//  Copyright (c) 2013 Akhil Verghese. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

long long Atkins_Sieve(char* sieve, long long N, long long square_root)
{
    sieve[2]=sieve[3]=1;
    long long four_x_square,three_x_square,y_square,n,y,x;
    
    for (x = 1; x <= square_root; x++)
    {
        four_x_square=4*x*x;
        three_x_square=3*x*x;
        y=1;
        y_square=1;
        while((y<=square_root)&(y_square<=N-four_x_square))
        {
            n = four_x_square+y_square;
            if ((n % 12 == 1) | (n % 12 == 5))
                sieve[n] ^= 1;
            y++;
            y_square=y*y;
        }
        y=1;
        y_square=1;
        while((y<=square_root)&(y_square<=N-three_x_square))
        {
            n = three_x_square+y_square;
            if (n % 12 == 7)
                sieve[n] ^= 1;
            y++;
            y_square=y*y;
        }
        y=1;
        y_square=1;
        while(y<x)
        {
            n = three_x_square-y_square;
            if ((n<N)&(n % 12 == 11))
                sieve[n] ^= 1;
            y++;
            y_square=y*y;
        }
    }
    for(long long p=5; p<=square_root;p++)
    {
        if (sieve[p])
        {
            long long q=2*p*p;
            for (long long i = p*p; i <= N; i += q)
                sieve[i] = 0;
        }
    }
    long long noofprimes=0;
    for(long long i=2;i<N;i++)
    {
        if(sieve[i])
            noofprimes++;
    }
    return noofprimes;
}

int main(int argc, const char * argv[])
{
    long long N,noofprimes;
    printf("Enter N: ");
    scanf("%lld",&N);
    char *sieve=malloc(N*sizeof(char));
    for(long long i=0;i<N;i++)
        sieve[i]=0;
    int square_root=ceil(sqrt(N));
    clock_t t_bits=clock();
    noofprimes=Atkins_Sieve(sieve, N, square_root);
    t_bits=clock()-t_bits;
    printf("Calculated %lld primes in %.2lf",noofprimes,(double)t_bits/CLOCKS_PER_SEC);
    return 0;
}

