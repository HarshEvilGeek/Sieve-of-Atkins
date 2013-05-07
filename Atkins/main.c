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

int main(int argc, const char * argv[])
{
    long long N;
    printf("Enter N: ");
    scanf("%lld",&N);
    char *sieve=malloc(N*sizeof(char));
    for(long long i=0;i<N;i++)
        sieve[i]=0;
    int square_root=ceil(sqrt(N));
    sieve[2]=sieve[3]=1;
    clock_t t_bits=clock();
    long long fsq,tsq,ysq,n,y,x;
    
    for (x = 1; x <= square_root; x++)
    {
        fsq=4*x*x;
        tsq=3*x*x;
        y=1;
        ysq=1;
        while((y<=square_root)&(ysq<=N-fsq))
        {
            n = fsq+ysq;
            if ((n % 12 == 1) | (n % 12 == 5))
                sieve[n] ^= 1;
            y++;
            ysq=y*y;
        }
        y=1;
        ysq=1;
        while((y<=square_root)&(ysq<=N-tsq))
        {
            n = tsq+ysq;
            if (n % 12 == 7)
                sieve[n] ^= 1;
            y++;
            ysq=y*y;
        }
        y=1;
        ysq=1;
        while((y<x)&(ysq>=(tsq-N)))
        {
            n = tsq-ysq;
            if (n % 12 == 11)
                sieve[n] ^= 1;
            y++;
            ysq=y*y;
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
    t_bits=clock()-t_bits;
    long long noofprimes=0;
    for(long long i=2;i<N;i++)
    {
        if(sieve[i])
            noofprimes++;
    }
    printf("Calculated %lld primes in %.2lf",noofprimes,(double)t_bits/CLOCKS_PER_SEC);
    return 0;
}

