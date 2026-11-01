#include <stdio.h>
#include "bits.h"
void print_binary(uint32_t x,int width){for(int i=width-1;i>=0;i--){printf("%u",(x>>i)&1u);if(i>0&&i%4==0)printf(" ");}puts("");}
uint32_t get_field(uint32_t w,int p,int n){if(p<0||p>31||n<1||n>32||p+n>32)return 0;return (w>>p)&(n==32?UINT32_MAX:((1u<<n)-1u));}
uint32_t set_field(uint32_t w,int p,int n,uint32_t v){if(p<0||p>31||n<1||n>32||p+n>32)return w;uint32_t m=n==32?UINT32_MAX:((1u<<n)-1u);return (w&~(m<<p))|((v&m)<<p);}
int32_t sign_extend(uint32_t v,int n){if(n<1||n>32)return 0;if(n==32)return (int32_t)v;uint32_t m=(1u<<n)-1u;v&=m;if(v&(1u<<(n-1)))v|=~m;return (int32_t)v;}
