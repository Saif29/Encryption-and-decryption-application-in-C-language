/***************************************************************************************************************
"WELCOME TO ENCRYPTION AND DECRYPTION SOFTWARE."
This is our FoCP End Semester Project.

****************************************************************************************************************/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>

//--------------------------------------------[FUNCTIONS PROTOTYPE]-----------------------------------------------

int prime_num(int);		// Function for generating a Random Prime Number.
int public_key(int);	// The number "n" and "e" are public keys that can be shared with anyone.
int private_key(int, int);	// The Number "d" is private key; it must kept secret.
int gcd(int, int);		// This function find the GEATEST COMMON DIVISOR between "e" and "t".
void file_handling();	// This function is used to encrypt/decrypt ".txt" files.
void encryption();		// Main function of Encryption.
void decryption();		// Main function of Decryption.
void Thanks();

//----------------------------------------------[GLOBAL VARIABLES]------------------------------------------------

int i = 1, j = 0;	// This Two variables are used in diferent loops so we made them Global.
int d, n;			// "d" is Private Key  &&  "n" is one of the Public key.	
int code[100];		// Array for storing Encrypted/Decrypted Code.
char data[100];		// Array for storing the whole data written on file.
char text[100] = { '\0' };	// Array for storing the whole text enter by the user.
char Choice2, Choice1;
FILE *fp;			// File pointer

//-----------------------------------------------[MAIN FUNCTION]--------------------------------------------------
int main()
{

	while (1)
	{
		memset(data, 0, sizeof(data));
		memset(text, 0, sizeof(text));
		memset(code, 0, sizeof(code));
		i = 0;

		// Encryption or Decryption? Whatever the user will want.
		while (1)
		{
			printf("Press E for Encryption or D for Decryption (Q to Exit):");
			Choice1 = getche();		// Storing the choice of user into Choice1

			if (Choice1 == 'E' || Choice1 == 'e' || Choice1 == 'd' || Choice1 == 'D')
				break;
			else if (Choice1 == 'q' || Choice1 == 'Q')
			{
				Thanks();
				printf("\n");
				return 0;
			}
			printf("\n\nINVALID CHOICE!\a\n\n");
		}

		// Encrypt/Decrypt File or any text entered from keyboard
		while (1)
		{
			printf("\nPress F for File or K for Input from Keyboard:");
			Choice2 = getche();		// Storing the choice of user into Choice2

			if (Choice2 == 'f' || Choice2 == 'F' || Choice2 == 'k' || Choice2 == 'K')
				break;

			printf("\n\nINVALID CHOICE!\a\n\n");
		}


		if (Choice1 == 'E' || Choice1 == 'e')
		{
			printf("\n\n");

			if (Choice2 == 'f' || Choice2 == 'F')
			{
				file_handling();	// If user wants to ENCRYPT a FILE then this function will call.
			}
			else if (Choice2 == 'k' || Choice2 == 'K')
			{
				printf("ENTER TEXT: ");
				fgets(text, sizeof(text), stdin);
				text[strlen(text) - 1] = '\0';

				encryption();	// If user wants to ENCRYPT text from keyboard then this function will call.
			}
		}
		else if (Choice1 == 'd' || Choice1 == 'D')
		{
			printf("\n\n\t\tEnter Decryption keys!\nPrivate Key = ");
			scanf("%d", &d);
			printf("\nn = ");
			scanf("%d", &n);

			if (Choice2 == 'f' || Choice2 == 'F')
			{
				file_handling();	// If user wants to DECRYPT a FILE then this function will call.
			}
			else if (Choice2 == 'k' || Choice2 == 'K')
			{
				printf("\nEnter code(Press ENTER when there is dash in code)(Enter any negative number when code ends): ");
				for (i = 0;; i++)	// Loop for storing the code to Decrypt
				{
					scanf("%d", &code[i]);

					if (code[i] < 0)
						break;

					decryption();	// If user wants to DECRYPT text from keyboard then this function will call.
				}
				printf("\n-----------------\"DECRYPTED CODE\"-----------------------\n\n");
				printf("%s", text);
				printf("\n\n--------------------------------------------------------\n");
			}
		}

		printf("\n\nEnter N to end the Program or any other key to continue:");
		Choice2 = getche();


		if (Choice2 == 'N' || Choice2 == 'n')
			break;

		printf("\r***************************************************************************************************************\n\n");
	}

	Thanks();
	printf("\n");
	return 0;
}

//-------------------------------------------[PRIME NUMBER GENERATER]---------------------------------------------

int prime_num(int x)	// Here x is the alternative of p and q.
{
	int a, prime;
	srand(time(NULL));
	while (1)
	{
		a = rand() % 90 + 10;
		for (i = 2; i <= (a / 2); i++)
		{
			prime = 1;
			if (a % i == 0)
			{
				prime = 0;
				break;
			}
		}
		if (prime == 1 && a != x)
			break;
	}
	return a;
}

//------------------------------------------[PUBLIC NUMBER GENERATER]---------------------------------------------

/* This Function is generating a PUBLIC KEY (e) and That KEY must fullfil the following conditions:

1) Must be less than Totient Number (t) and greater than 1.  i.e: [1 < e < t]
2) There is no common factor between t and e except 1.  i.e: [Greatest common Divisor of t and e is '1']

*/

int public_key(int y)	// Here 'y' is the altenative if 't'.
{
	int e;
	srand(time(NULL));
	while (1)
	{
		e = 2 + rand() % (y - 2);
		if (gcd(e, y) == 1)
		{
			break;
		}
		else
		{
			continue;
		}
	}
	return e;
}

//---------------------------------------[GREATEST COMMON DIVISOR CHECKER]----------------------------------------

int gcd(int u, int v)	// Here 'u' is the altenative of 'e' and 'v' is the alternative of 't'.
{
	while (u != v)
	{
		if (u > v)
		{
			return gcd(u - v, v);
		}
		else
		{
			return gcd(u, v - u);
		}
	}
	return u;
}

//--------------------------------------------[PRIVATE KEY GENERATER]---------------------------------------------

/* This Function is generating a PRIVATE KEY (d) and That KEY must fullfil the following conditions:

1) Must be less than Totient Number (t) and greater than 1.  i.e: [1 < d < t]
2) 'd * e - 1' will the multiple of 't'  i.e: [((d * y) - 1) % t == 0]

*/

int private_key(int z, int y)	// Here 'z' is the alternative of 't' and 'y  is the alternative of 'e' .
{
	srand(time(0));
	while (1)
	{
		d = 2 + rand() % (z - 2);
		if (((d * y) - 1) % z == 0 && d != y)
			break;
		else
			continue;
	}
	return d;
}

//--------------------------------------------[FILE HANDLER FUNCTION]---------------------------------------------

void file_handling()
{
	char name[100] = { "" };	// Array for storing the name of the file.

	while (1)
	{
		printf("Enter file name with COMPLETE PATH: ");
		fgets(name, sizeof(name), stdin);

		if (Choice1 == 'D' || Choice1 == 'd')
			fgets(name, sizeof(name), stdin);

		name[strlen(name) - 1] = '\0';

		printf("\nOpening the file \" %s \" in read mode...\n", name);
		fp = fopen(name, "r");

		if (fp == NULL)
		{
			printf("\n\aCOULD NOT OPEN THE FILE \" %s \"\n\n\n", name);
			continue;
		}
		else
			break;
	}

	if (Choice1 == 'D' || Choice1 == 'd')
	{
		for (i = 0; i < sizeof(code); i++)
		{
			fscanf(fp, "%d", &code[i]);

			if (code[i] == 0)
				break;

			decryption();
		}
		printf("\n");
	}
	else if (Choice1 == 'E' || Choice1 == 'e')
	{
		while (fgets(data, 100, fp) != NULL)
		{
			printf("%s", data);
			strcat(text, data);
		}
		printf("\n");
	}

	fp = fopen(name, "w");

	if (Choice1 == 'E' || Choice1 == 'e')
	{
		i = 0;
		encryption();
	}
	else if (Choice1 == 'D' || Choice1 == 'd')
	{

		fprintf(fp, "%s", text);
		printf("\n-----------------\"DECRYPTED CODE\"-----------------------\n\n%s", text);
		printf("\n\n--------------------------------------------------------\n");
	}


	printf("\nClosing the file %s\n", name);
	fclose(fp);
}

//---------------------------------------------[ENCRYPTION FUNCTION]----------------------------------------------

/* This function is doing these task:

1) Generate two prime numbers randomly. ( p & q )
2) Create Totient Number. ( t )
3) Generate public and private keys. ( e & d )
4) Then use RSA Algorithm to encrypt the entered text or file.

*/

void encryption()
{
	int p = 0, q = 0;	// p & q are two prime numbers randomly generated by a fuction.
	int t, e = 0;		// t is called "Totient Number" obtained by multiplying (p-1) & (q-1). e is one of the public key.

	if (i == 0)
	{
		p = prime_num(q);
		q = prime_num(p);
		n = p*q;
		t = (p - 1) * (q - 1);
		e = public_key(t);
		d = private_key(t, e);
		printf("\nPRIME 1 = %d\tPRIME 2 = %d\n\nPublic Keys | Private Key\n\ne  = %6d | d  = %6d\nn  = %6d |\n", p, q, e, d, n);

	}
	printf("\n-----------------\"ENCRYPTED CODE\"-----------------------\n\n");

	for (i = 0; i < strlen(text); i++)        //Runs for the length of string entered
	{

		code[i] = text[i];					// Storing ASCII values of Alphabets and other characters if any.
		int En = 1;							//variable to temporary store encoded number

		for (j = 0; j < e; j++)
		{
			En = En*code[i];
			En = En % n;
		}
		code[i] = En;

		if (Choice2 == 'f' || Choice2 == 'F')
			fprintf(fp, "%d\n", code[i]);

		printf("%d-", code[i]);
	}
	printf("\b ");

	if (Choice2 == 'f' || Choice2 == 'F')
		fprintf(fp, "%d\n", code[i]);
	printf("\n\n--------------------------------------------------------\n");
}

//---------------------------------------------[DECRYPTION FUNCTION]----------------------------------------------

void decryption()
{

	int Dn = 1;             //variable to temporary store decoded number
	for (j = 0; j < d; j++)
	{
		Dn = Dn*code[i];
		Dn = Dn%n;
	}
	text[i] = Dn;
}

//----------------------------------------------------------------------------------------------------------------

void Thanks()
{
	system("cls");
	system("COLOR 02");
	printf("\n\n\n\n\n\n\n\n\n\n\n\t\t\t\tTTTTTTTTTTT   H       H     AAAA     N         N   K    K    SSSSSSS\n");
	printf("\t\t\t\t     T        H       H    A    A    N N       N   K   K    S       S\n");
	printf("\t\t\t\t     T        H       H   A      A   N   N     N   K  K     S\n");
	printf("\t\t\t\t     T        HHHHHHHHH   AAAAAAAA   N     N   N   KK        SSSSSSS\n");
	printf("\t\t\t\t     T        H       H   A      A   N      N  N   K  K             S\n");
	printf("\t\t\t\t     T        H       H   A      A   N       N N   K   K     S      S\n");
	printf("\t\t\t\t     T        H       H   A      A   N         N   K    K     SSSSSS \n\n");
}
