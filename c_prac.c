/*
Ayodele, David
INFSCI 2620
10/21/19
*/

#include <stdio.h>
#include <string.h>

#define BUFFER 50 

void getString (char *in, int buffer);
int string2array (char *inString, char **wordarray);
void proper (char *word);
void printArray (char **words, int wordcount);

struct Sentence {
	char string[BUFFER];
	char *words[10];
	int wordCount;
};

void getString (char *in, int buffer) { 
  char str[buffer];   
  printf("Enter a string: ");   
  fgets(str, buffer + 1, stdin); 
  
  if ((strlen(str) > 0) && (str[strlen (str) - 1] == '\n')) {  
    str[strlen (str) - 1] = '\0';                              
  } 

  strcpy(in, str);                                             
}

int string2array (char *inString, char **wordarray) {  
  const char s[2] = " ";
  char *token;
  int count = 0;
  int i, j; 

  wordarray = (char**)malloc(strlen(inString)*sizeof(char*));
  for(i=0; i<strlen(inString); i++) {
    wordarray[i] = (char*)malloc((BUFFER + 1)*sizeof(char));
  }

  token = strtok(inString, s); // loads 1st token
  while(token != NULL) {       // continues loading tokens until end
    strcpy(wordarray[count], token);
    count++;
    token = strtok(NULL, s);
  }
  
  printArray(wordarray, count);
  
  return count;
}

void proper (char *word) {
  int i;
  //loop capitalizes first char of sentences
  for(i = 0; word[i]!='\0'; i++) {          //from index 0, loop until terminus char, '\0', is found
    if(i == 0) {                             
      if((word[i]>='a' && word[i]<='z'))    //check if 1st char is lowercase
        word[i] = word[i] - 32;             //subtract 32 ascii vals to make it capital if so
      continue;                             //continue with rest of word (do not exit loop)
    }
    
    if(word[i]=='.') {                      //check if char is period/sentence end
      ++i;                                  //try incrementing 1st then set i (avoids NULL assigns to i)
      if(word[i]==' ') {                    //check if next char (after period) is space
        ++i;                                //increment then reset i
        if(word[i]>='a' && word[i]<='z') {  //if so, check if next char is lowercase
          word[i] = word[i] - 32;           //if so, subtract 32 to make it capital
          continue;                         //continue with rest of word
        }
      }
    }

    if(word[i]==' ') {                      //check if char is space
      ++i;                                  //try incrementing 1st then set i (avoids NULL assigns to i)
    }
    
    //if no period or lone "i" is found, all remaining chars should be lowercase (simple proper)
    if(word[i]>='A' && word[i]<='Z'){       //check if char is uppercase
      word[i] = word[i] + 32;               //add 32 to make it lowercase
    }                                       //increment, repeat checks (for beginning, period, space, captial)

    //search for lone "i"s
    if(word[i]=='i' && word[i+1]==' ' && word[i-1]==' ') {  //check if char is pronoun "i" by itself
      word[i] = word[i] - 32;              //subtract 32 to make it uppercase
      ++i;                                 //increment then reset i (avoids NULL assigns to i)
    }
  }                                        //stop loop at terminus char, '\0'
}

void printArray (char **words, int wordcount) {
  int i;
  for (i = 0; i < wordcount; i++) {   
    printf("%s\n", words[i]);  
  } 
}

int main(void) { 
  struct Sentence s1;
  
  getString(s1.string, BUFFER); 
  proper(s1.string);
  s1.wordCount = string2array(s1.string, s1.words);
  printf("%d", s1.wordCount);
    
  return 0;
 }

/*
References:
www.tutorialspoint.com
*/

/* 
1.  Write a function to accept a string input using the following function prototype:void getString (char *in, int buffer);

2.  Write a function that accepts a single string and splits the string into an array of words and returns the number of words found using the following function prototype:
int string2array (char *inString, char **wordarray);

3.	Write a function to proper case a string using the following function prototype:
void proper (char *word);

4.	Write a function to print out strings stored in an array using the following function prototype:
void printArray (char **words, int wordcount)

5.	Put it all together using the following structure:
struct Sentence {
	char string[50];
	char *words[10];
	int wordCount = -1;
};
a.	Store input into the sentence string,
b.	Parse the string into an array of words and store the number of words found,
c.	Proper case each word in the sentence,
d.	and print out the proper cased sentence

*/
