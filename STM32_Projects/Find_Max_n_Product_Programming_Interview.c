/**
 ******************************************************************************
 * @Author Name     : Salih
 * @Surname         : Yalcin (salih.yalcinn@hotmail.com)
 * @Date(DD.MM.YYY) : 22.07.2022
 * @Outputs        :
  				     Max Product : 4536 (Product Length: 4)
					 Attempts : 6
					 First Number Index : 364 , Last Number Index : 367 (364,365,366,367) (9*9*8*7 = 4536)
					 ---------------
					 Max Product : 493807104 (Product Length: 10)
					 Attempts : 11
					 First Number Index : 361 , Last Number Index : 370
					 ---------------
					 Max Product : 4702924800  (Product Length: 12)
					 Attempts : 10
					 First Number Index: 197 , Last Number Index : 208
					 ---------------
					 Max Product : 282293061120  (Product Length: 15)
					 Attempts : 11
					 First Number Index: 498 , Last Number Index : 512




*	@Settings  		 1. To be able to use ITM Data Console, we need to add some code section to syscalls.c between #include <sys/times.h> and  Variables title  (https://github.com/niekiran/Embedded-C/blob/master/All_source_codes/target/itm_send_data.c)
					 2. Also we need to enable Serial Wire Viewer (SWV) from Debug Configurations -> Debugger -> Put Check (Mark) enable SWV
					 3. Then in Debugger Environment Window -> Show View -> SWV -> SWV ITM Data Console
					 4. In ITM Data Console Settings (Configure Trace) put check (mark) zeroth buffer (Stimulus Ports) to enable the Port0.
					 5. Before clicking "Run" make sure the click the "Start Trace" from ITM Data console
					 6. Also we need to change Runtime Library to Standard C, Standard C++. If we want to display 64 bit datas we have to switch it. To do this Properties -> C/C++ Build -> MCU Settings -> Runtime Library


*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void FindMaxProduct(uint32_t prod_length); // FUNCTION PROTOTYPE

const char  *number=
		"64077176531330624919225119674426574742355349194934"
		"96983520312774506326239578318016984801869478851843"
		"85861560789112949495459501737958331952853208805511"
		"12540698747158523863050715693290963295227443043557"
		"66896648950445244523161731856403098711121722383113"
		"62229893423380308135336276614282806444486645238749"
		"30358907296290491560440772390713810515859307960866"
		"70172427121883998797908792274921901699720888093776"
		"65727333001053367881220235421809751254540594752243"
		"52584907711670556013604839586446706324415722155397"
		"53697817977846174064955149290862569321978468622482"
		"83972241375657056057490261407972968652414535100474"
		"82166370484403139890008895243450658541227588666881"
		"16427171479924442928230863465674813919123162824586"
		"17866458359124566529476545682848912883142607690042"
		"24219022671055626321111109370544217506941658960408"
		"07198403850962455444362981230987879927244284909188"
		"84580156166097919133875499200524063689912560717606"
		"05886116467109405077541002256983155200055935729725"
		"71636269561882670428252483600823257530420752963450" ;



int main(void)
{

	uint32_t product_length=4; // TYPE THE DESIRED LENGTH HERE!

	FindMaxProduct(product_length);

	return 0;

}

void FindMaxProduct(uint32_t prod_length)
{
	uint32_t i,j,attempt=0,first_index=0,last_index=0; // HOW MANY ATTEMPT WE DID THE FIND THE MAX PRODUCT?
	uint64_t current_product;
	uint64_t max_product = 0;

	for(i=0; i + prod_length <=1000;++i) // WE HAVE 1000 NUMBERS (WE HAVE TO ADD prod_length BECAUSE WE HAVE TO CHOOSE THAT SPESIFIC LENGTH)
	{
		current_product=1;
		for(j=0;j<prod_length;++j)
		{
			current_product *= (*(char *)(number + i + j)) - '0'; // 1. SEQUENTIAL MULTIPLYING PROCESS  2. CONVERTING CHAR TO VALUE (POINTER)
		}

		/*
		 * The characters '0' to '9' are stored contiguously in memory as numbers 48-57 as defined by ASCII (same as the 1st 127 characters in unicode).
		 * Subtracting '0' or really the number 48 gets the actual number that the character represents.
		 * For example '0' = 48, so '0' - '0' = 48 - 48 = 0 or '8' = 56, so '8' - '0' or 56 - 48 = 8

		 * */
		if(current_product > max_product) // IF WE HAVE BETTER PRODUCT, THEN ASSIGN IT TO MAX PRODUCT.
		{
			first_index = i;
			last_index = i + prod_length;
			max_product = current_product;
			attempt++;
		}

	}

	printf("\nMax product : %lld \n",max_product); // %lld FOR 64 BIT, %ld FOR 32 BIT.
	printf("Attempts : %ld \n",attempt);
	printf("First : %ld , Last  : %ld",first_index,last_index -1);
	fflush(stdout); // JUST IN CASE :)


}
