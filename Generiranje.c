#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void search( char* txt, char* pat,int N, int M) {
    
	int i;
    // A loop to slide pat[] one by one
    for (i = 0; i <= N - M; i++) {
        int j;

        // For current index i, check for pattern match
        for (j = 0; j < M; j++) {
            if (txt[i + j] != pat[j]) {
                break;
            }
        }

        // If pattern matches at index i
        if (j == M) {
            printf("Pattern found at index %d\n", i);
        }
    }
}

// Function to implement the KMP algorithm


void KMP(char* text, char* pattern, int n, int m)
{
	int i, j;
    // base case 1: pattern is NULL or empty
    if (*pattern == '\0' || m == 0) {
        printf("The pattern occurs with shift 0");
    }
 
    // base case 2: text is NULL, or text's length is less than that of pattern's
    if (*text == '\0' || m > n) {
        printf("Pattern not found");
    }
 	printf("Usao u KMP");
    // lps[i] stores the index of the next best partial match
    int lps[m + 1];
     
	for (i = 0; i < m + 1; i++) {
        lps[i] = 0;
    }
    
    for (i = 1; i < m; i++)
    {
        j = lps[i];
 
        while (j > 0 && pattern[j] != pattern[i]) {
            j = lps[j];
        }
 
        if (j > 0 || pattern[j] == pattern[i]) {
            lps[i + 1] = j + 1;
        }
    }
	printf("Izgradio lps\n");
	int flag = 0;
 	
    for (i = 0, j = 0; i < n; i++)
    {
        if (*(text + i) == *(pattern + j))
        {
            if (++j == m) {
            	flag = 1;
                //printf("The pattern occurs with shift %d\n", i - j + 1);
            }
        }
        else if (j > 0)
        {
            j = lps[j];
            i--;    // since `i` will be incremented in the next iteration
        }
    }
    
    if (!flag) printf("Pattern not found\n");
    
}

void rand_str(char *dest, size_t length) {
    char charset[] = "ab";

    while (length-- > 0) {
        size_t index = (double) rand() / RAND_MAX * (sizeof charset - 1);
        *dest++ = charset[index];
    }
    *dest = '\0';
}

int main(void) {
	
	srand(time(0));
	
	int mm = 5, nn = 50;
	//printf("Unesite duljinu nasumicnog teksta: ");
	//scanf("%d", &nn);
	//printf("Unesite duljinu nasumicnog uzorka: ");
	//scanf("%d", &mm);
	//printf("\n");
	
	int pomak = 50;
	char *txt, *pat;
	/*
	
	txt = (char *)malloc(nn * sizeof(char));
    pat = (char *)malloc(mm * sizeof(char));
    int i;
    for(i = 0; i < 3; i += 2) {
    	pat[i] = 'a';
    	pat[i+1] = 'b';
	}
	pat[4] = 'a';
	
	for (i = 0; i < 14; i += 2) {
		txt[i] = 'a';
		txt[i+1] = 'b';
	}
	txt[14] = 'b';
	
	printf("%s\n", pat);
	printf("%s\n", txt);
			
	KMP(txt, pat, nn, mm);*/
    
    
	
	int size;
	for (size = nn; size <= 1000; size += pomak) {
		txt = (char *)malloc(size * sizeof(char));
    	pat = (char *)malloc(mm * sizeof(char));
    	printf("%d\n", size);
    	
		
		int i; 
		double suma = 0.0, vrijeme;
		
		
    	for (i = 0; i < 10; i++) {
    		rand_str(pat, mm);
			rand_str(txt, size);
			//printf("%s\n", pattern2);
			//printf("%s\n", text2);
			*(txt + size) = '\0';
			*(pat + mm) = '\0';
		
			clock_t start, end;
			start = clock();
			KMP(txt, pat, size, mm);
			end = clock();
			
			vrijeme = (double)(end - start) / CLOCKS_PER_SEC;
			
			suma += vrijeme;
		}
		
    	printf("REZULTAT: \n");
    	double avg_time = suma / 10.0;
    	printf("\nTekst duljine %d, uzorak duljine %d. Prosjecno vrijeme: %.6f\n\n", size, mm, avg_time);
    	
    	
    	free(txt);
    	free(pat);
    	printf("Krepava li? %d", size);
	}
	
		
	return 0;
}

//"0123456789"
//"abcdefghijklmnopqrstuvwxyz"
//"ABCDEFGHIJKLMNOPQRSTUVWXYZ";




