#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <file_opt.h>
#include <math.h>

long Hex2Long( unsigned char *buf, int len )
{
	int  i;
	long num = 0;
	long base = 1;

	if( len > sizeof( long ) )
		return -1;

	for( i = 0; i < len; i++ ) {
		num += buf[len-1-i]*base;
		base = base*256;
	}
	return num;
}

float exp2float(unsigned char *data)
{
	unsigned char sign, m[3];
	float ret = 0, base = 8388608;
	double exp, e = 0;
	long tmp;

	sign = data[0] >> 7;

	e = (unsigned char)((data[0] << 1) | (data[1] >> 7)) - 127;
	exp = pow(2, e);

	memcpy(m, data + 1, 3);
	m[0] = m[0] & 0x7F;
	tmp = Hex2Long(m, 3);
	ret = (1.0 + tmp / base) * exp;

	if (sign == 1) {
	       	ret = ret * (-1);
	}

	return ret;
}

static int parse_data(unsigned char *src, unsigned char *des)
{ 	int i, k, lenstr;
	unsigned char tmp1[12]={0};

	lenstr = strlen(src);
	for(i=0;i<lenstr;i++){
		if(src[i] >= 0x30) 
			src[i] &= 0x0f;		//ascii to bcd
		}
	lenstr--;
	for(i=11;lenstr >= 0 && i >= 0;lenstr--){
		if(src[lenstr] != 0x2e && src[lenstr] != 0x2d){
			tmp1[i] = src[lenstr];
			i--;
			}
		}

	for(k=5, i=11;i > 0 && k >= 0;i=i-2){	
		des[k] = tmp1[i] | (tmp1[i-1] << 4);
		k--;
	}

	return 0;
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("argc is [%d]\n", argc);
		return -1;
	}

	unsigned char src[4];
	unsigned char des[10];
	unsigned char hex[8];
	float f;
	bzero(src, sizeof(src));
	bzero(des, sizeof(des));

	asc_to_hex(argv[1], hex, strlen(argv[1]));
	hex_to_bcd(hex, des, strlen(argv[1]));
	f = exp2float(des);
	printf("des f %.3f\n", f);
	return 0;
}


