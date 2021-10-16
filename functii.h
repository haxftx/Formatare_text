#pragma pack(1)

#define MAX 1000
#define MAXSPACE "        "

//funtia de inversare a unui sir de caractere;
void reverse(char *x, int begin, int end)
{
  char c;
 
  if (begin >= end)
  {
    return;
  }
 
   c          = *(x+begin);
   *(x+begin) = *(x+end);
   *(x+end)   = c;
 
   reverse(x, ++begin, --end);
}

//calcularea spatiilor la inceputul unui sir de caractere;
//     sau a taburilor
int nr_space(char str[MAX] )
{
    int i = 0;
    while(str[i] == ' ' || str[i] == '\t')
    {
        i++;   
    }
    return i;
}

//schimbarea a 2 siruri de caractere;
void swap(char str1[MAX], char str2[MAX])
{
  char str[MAX];
  strcpy(str, str1);
  strcpy(str1, str2);
  strcpy(str2, str);
  
}

//sortarea crescatoare a sirurilor de caractere;
void sort_inc(char original[MAX][MAX], int begin, int end)
{
  int i, j;
  for(i = begin ; i < end - 1 ; i++)
  {
    for(j = i + 1; j < end; j++)
    {
      if(strcmp(original[i], original[j]) > 0)
      {
        swap(original[i], original[j]);
      }
    }
  }
}

//sortarea descrescatoare a sirurilor de caractere;
void sort_dec(char original[MAX][MAX], int start, int stop)
{
  int i, j;
  for(i = start ; i < stop - 1; i++)
  {
    for(j = i + 1; j < stop; j++)
    {
      if(strcmp(original[i], original[j]) < 0)
      {
        swap(original[i], original[j]);
      }
    }
  }
}

//stergerea sirurilor de caractere;
void del_text(char original[MAX][MAX], int *original_line_count)
{
  int i;
  for(i = 0 ; i < *original_line_count; i++)
  {
    strcpy(original[i], "\0");
  }

  *original_line_count = 0;
}

//citire de input;
void reading(char *name, char original[MAX][MAX],
             int *original_line_count, char buf[MAX])
{
   // Open input file for reading
  FILE *input_file = fopen(name, "r");
  int n = 0;
  if (input_file == NULL)
  {
    fprintf(stdout, "File \"%s\" not found\n", name);
    return ;
  }

  // Read data in file line by line
  while (fgets(buf, MAX, input_file)) 
  {
    strcpy(original[n], buf);
    n++;
  } 

  *original_line_count = n;
  fclose(input_file); 

}

//scriere de output;
void writing(char *name, char result[MAX][MAX], int result_line_count)
{

  // Open output file for writing
  FILE *output_file = fopen(name, "w");
  int i;
  if (output_file == NULL) 
  {
    fprintf(stdout, "Could not open or create file \"%s\"\n", name);
    return ;
  }

  // Write result in output file
  for (i = 0; i < result_line_count; i++) 
  {
    fputs(result[i], output_file);
  }

  fclose(output_file);

}
#pragma pack()