#include <stdio.h>
    
typedef unsigned long long ull; //renaming the specifier for ease(Who likes writing more than needed?)
const ull LIMIT = 1000000000000000ULL;//Number greater than 10^15 don't belong here
    
/*Lets calculate the sum of proper divisors(sopd), cause that's math and it works. */
    
ull sopd(ull n)//Now that's what I call a function 
{
	if(n == 1) 
	{
		return 0;
	}    
	ull sn = n;//we need to hold the starting n ,before we start modifying it
	ull sum = 1;// 1 willl always be a prime factor for any n greater than 1
	ull p, power;

       //In order to make the program faster, lets calculate some common factors separately(No reason for that, but now i did it.)
	//Lets begin with 2. Cause we can.

	if (n % 2 == 0) //Boring, skip to the general formula.
	{
		power = 1;
		while (n % 2 == 0) 
		{
	  		n /= 2;
	  		power *= 2;
		}
		sum *= (power * 2 - 1); 
	}
	//Lets do the same for 3

	if (n % 3 == 0) //Still reading???!!! 
	{
		power = 1;
		while (n % 3 == 0) 
		{
	  		n /= 3;
	  		power *= 3;
		}
		sum *= (power * 3 - 1) / 2;
	}
	//Ok, we checked for the most common primes. All the other prime factors are include in the formila 6k +-1
	for (p = 5; p * p <= n; p += 6)// HERE COMES THE GOOD PART(only if you like math) 
	{// we only need to check fro primes smaller than n squared
	//first we check for p = 6k - 1

		if (n % p == 0) 
		{
	   		power = 1;
	   		while (n % p == 0) 
			{
	      			n /= p;
	      			power *= p;
	   		}
	   		sum *= (power * p - 1) / (p - 1);
			
		}
		//now lets also ckeck for p = 6k + 1 ,by adding 2 to p
		ull q = p + 2; //I choose to rename  p + 2 as q because why not    
		if (n % (p + 2) == 0) 
		{
	   		power = 1;
	   		while (n % q == 0) 
			{
	      			n /= q;
	      			power *= q;
	   		}
	  		 sum *= (power * q -1) / (q -1);
		}
	}

	// What if n is a prime itself? ,Then we must include it as a prime factor( I DON'T MAKE THE RULES)
	if (n > 1)
	{
		sum *= (1 + n);
	}
	//Lets also subtruct the number itself as we don't want it to be included in the sum of the prime factors
	return sum - sn;
}   

// HERE COMES THE MAIN( aka more functions to come)
//more functions to come   
int check_n(ull n)// Remember the part were I don't like writing? I don't ,so lets try to write as litlle as possible
{
	if (n > 0 && n < LIMIT ) 
	{
		return 0;
	}
	printf("Invalid input, the number you gave is out of range." );// ABORT ABORT, something is wrong with 'n'
	return 1;
}


int main(void) 
{
	ull n;
	int result;
	char mode;
	ull s;
		
	//Read the starting number
	printf("Please give me a number to start the aliquot sequence from: ");//Only if you fancy it
	result = scanf("%llu", &n);

	//Making sure the program returns 1 when the input n is not a natural number
	if (result != 1) 
	{
		printf("Invalid input, need a natural number.");// ABORT ABORT, something is wrong with 'n'
		return 1;
	}
	if (check_n(n))
	{
		return 1;		
	}

	printf("Provide the max aliquot length to look for (0 for unlimited): ");//Do you want to stop along the way?.
	result = scanf("%llu", &s);
         if (result != 1 ) //Making sure the program returns 1 when the input s is not a natural number or 0
        {
                 printf("Invalid input, need a whole, positive, number.");
                return 1;// ABORT ABORT, something is wrong with 's'
        }
	printf("Do you want to print the full sequence ('f') or just the length ('l')?");//In life you have to make choices.
	result = scanf(" %c", &mode);
	
	if (result != 1 || (mode != 'f' && mode != 'l')) 
	{ 
		printf("Ivalid input, need either 'f' or 'l'.");
		return 1;//Making sure the program returns 1 for invalid input of mode
	}

	
	int keep_running = 1;//Start running and keep doing so till I tell you otherwise.
	ull l = 0;
	while (keep_running)
	{
		l += 1;//'l' will help with tracking your progress 
		if (mode == 'f') //Choice no 1 
		{
			printf("%llu \n",n);
		}
		n = sopd(n);
		if (n == 0)//0 is a finsh line
		{
			if (mode == 'f') 

			{
				printf("0 \n");//many aliquot sequences lead to 0
			}
			l +=1;
			keep_running = 0;// you can rest a bit
		} 
		else if  (n > LIMIT)// Everything has it's limits
		{       printf("%llu \n",n);//We want to know which number is over the limit.
                        printf("Number exceeds maximum supported integer (1000000000000000). Stopping.\n");
			l += 1;
			if (mode == 'l') //Choice no 2
			{
				printf("Length of aliquot sequence: %llu \n",l);
			}
			return 1;
		}
		if (s != 0 && l>= s) //Yeah, yeah I know, you want to make your own limits
		{
			keep_running = 0;// you can rest a bit
		}
	}  
	
	if (mode == 'l')//No more ifs
        {
        	printf("Length of aliquot sequence: %llu \n",l);//Ok 'l' will let as know how many laps you ran
	}

	return 0;//Okay thats enough of that
    		
}   
        //Ta-ta
