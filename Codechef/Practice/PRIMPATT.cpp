#include<iostream>
#include<cstdio>
#include<ctime>
#include<cmath>
#include<cstdlib>
const static int bits = 19, mask = (1<<19) - 1;
#define UINT_MAX 32767
typedef long long ll;
using namespace std;
long long int getVal(long long int x,long long int y)
{
 ll lev = max(abs(x),abs(y));
 ll lx = lev,ly=1-lev;
 if(x==lev)
  return 4*lev*lev - 4*lev + 1 + y - ly;
 if(y==lev)
  return 4*lev*lev - 2*lev + abs(x-lx);
 if(x==-lev)
  return 4*lev*lev + abs(y-lev);
 if(y==-lev)
  return 4*lev*lev + 2*lev + abs(x+lev);
}
unsigned long long mul(unsigned long long x, unsigned long long y, unsigned long long M)
{
if (x <= UINT_MAX && y <= UINT_MAX) return x * y % M;
unsigned long long rslt = y * (x & mask) % M;
while (x >>= bits) rslt = (rslt + (y = (y << bits) % M) * (x & mask)) % M;
return rslt;
}
 
static int test(unsigned long long n, unsigned long long a) {
unsigned long long s, t, nmin1 = n - 1;
int r;
for (s = nmin1, r = 0; !(s & 1); s >>= 1, r++) ;
for(t = a; s >>= 1; )
{
a = mul(a, a, n);
if (s & 1) t = mul(t, a, n);
}
if (t == 1 || t == nmin1) return 1;
while (--r) if ((t = mul(t, t, n)) == nmin1) return 1;
return 0;
}
 
static int isPrime(unsigned long long n) {
if(n<29) return n==2 || n==3 || n==5 || n==7 || n==11 || n==13 || n==17 || n==19 || n==23;
if(!(n&1 && n%3 && n%5 && n%7 && n%11 && n%13 && n%17 && n%19 && n%23)) return 0;
return test(n, 2) && test(n, 1215) &&(n==17431 || test(n, 34862) && (n==3281359 || test(n, 574237825)));
}
int main()
{
    int t;
    long long int x0,y0,dist,found,x,y;
    long long int val;
    //no_primes=create_sieve();
    //cout<<prime[0]<<" "<<prime[1]<<" "<<prime[2]<<" "<<prime[no_primes-1];
    scanf("%d",&t);
    //cout<<getVal(1,1)<<" "<<isPrime(4);
    while(t--)
    {
        scanf("%lld%lld",&x0,&y0);
        val=getVal(x0,y0);
        found=0;
        if(isPrime(val))
            dist=0;
        else
        {
            for(dist=1;;dist++)
			{
				for(x=1;x<=dist;x++) // first quadrant
				{
					y=dist-x;
					if(isPrime(getVal(x+x0,y+y0)))
					{
						found=1;
						break;
					}
				}
				if(found) break;
				for(x=1-dist;x<=0;x++) // second quadrant
				{
					y=dist+x;
					if(isPrime(getVal(x+x0,y+y0)))
					{
						found=1;
						break;
					}
				}
				if(found) break;
				for(x=-dist;x<0;x++) // third quadrant
				{
					y=-dist-x;
					if(isPrime(getVal(x+x0,y+y0)))
					{
						found=1;
						break;
					}
				}
				if(found) break;
				for(x=0;x<dist;x++) // fourth quadrant
				{
					y=-dist+x;
					if(isPrime(getVal(x+x0,y+y0)))
					{
						found=1;
						break;
					}
				}
				if(found) break;
			}
        }
        printf("%lld\n",dist);
    }
    return 0;
}
