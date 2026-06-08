#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int* stvori_lps(int m, char* pattern) {
	int *lps;
	
	lps = (int*)malloc(m * sizeof(int));
    
	lps[0] = 0;
	int k = 0, q;
    
    for (q = 1; q < m; q++)
    {
 
        while (k > 0 && pattern[k] != pattern[q]) {
            k = lps[k - 1];
        }
 
        if (pattern[k] == pattern[q]) {
            ++k;
        }
        lps[q] = k;
    }
    
	return lps;
}


void KMP(char* text, char* pattern, int n, int m)
{
   
    int* lps;
    lps = stvori_lps(m, pattern);
	
	int i, q = 0;
	
	int flag = 0;
 	
    for (i = 0; i < n; ++i) {
    	//if (n - i < m - q) break;
    	while (q > 0 && pattern[q] != text[i]) {
    		q  = lps[q - 1];
		}
		if (pattern[q] == text[i]) {++q;}
		if (q == m) {
			flag = 1;
			printf("Uzorak se pojavljuje na indeksu %d\n", i - m + 1);
			q = lps[q - 1];
		} 		
	}
    
    if (!flag) printf("Uzorak se ne pojavljuje.\n");
    
}

void rand_str(char *dest, size_t length) {
	//"0123456789"
	//"abcdefghijklmnopqrstuvwxyz"
	//"ABCDEFGHIJKLMNOPQRSTUVWXYZ";	
    char charset[] = "abcdefghijklmnopqrstuvwxyz";

    while (length-- > 0) {
        size_t index = (double) rand() / RAND_MAX * (sizeof charset - 1);
        *dest++ = charset[index];
    }
    *dest = '\0';
}

int main(void) {
	
	srand(time(0));
	// n je duljina teksta, m je duljina uzorka
	
	int n = 50000, m = 50;
	int pomak = 50000, size;
	//printf("Unesite duljinu nasumicnog teksta: ");
	//scanf("%d", &n);
	//printf("Unesite duljinu nasumicnog uzorka: ");
	//scanf("%d", &m)e;
	
	
	//printf("\n");
	

	/*
	char* pat;
	char* txt;
	txt = (char *)malloc(n * sizeof(char));
    pat = (char *)malloc(m * sizeof(char));
    txt = "";
    pat = "";
    double vrijeme;
    clock_t start, end;
	start = clock();
    KMP(txt, pat, n, m); 
	end = clock();
	vrijeme = (double)(end - start) / CLOCKS_PER_SEC;
	printf("Vrijeme izvrsenja: %.6f", vrijeme);
	*/
	
	//testiranje za više sluèajeva i mjerenje vremena
	
	for (size = n; size <= 1000000; size += pomak) {		
		int i; 
		double suma = 0.0, vrijeme;
		char* pat;
		char* txt;
    	for (i = 0; i < 10; i++) {
    		txt = (char *)malloc(size * sizeof(char));
    		pat = (char *)malloc(m * sizeof(char));
    		rand_str(pat, m);
			rand_str(txt, size);
			//printf("%s\n", pat);
			//printf("%s\n", txt);
			*(txt + size) = '\0';
			*(pat + m) = '\0';
		
			clock_t start, end;
			start = clock();
			KMP(txt, pat, size, m);
			end = clock();
			
			vrijeme = (double)(end - start) / CLOCKS_PER_SEC;
			
			suma += vrijeme;
			
			free(txt);
    		free(pat);
		}
		
    	printf("REZULTAT KMP: \n");
    	double avg_time = suma / 10.0;
    	printf("\nTekst duljine %d, uzorak duljine %d. Prosjecno vrijeme: %.6f\n\n", size, m, avg_time);	
	}
	
		
	return 0;
}
