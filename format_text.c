#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functii.h"

//copierea din input in output;
void copy(char original[MAX][MAX], int original_line_count,
          char result[MAX][MAX], int *result_line_count)
{
  int i;
  for (i = 0; i < original_line_count; i++) 
  {
    strcpy(result[i], original[i] );
  }

  *result_line_count = original_line_count; 
}

//strtok cu salvarea datelor pentru operatii si paramtrei;
void my_strtok(char ofter[MAX][MAX], char str[MAX], char c, int *nr_oper)
{
    int i = 0, j ,k = 0 ;
    for(j = 0 ; j < strlen(str) + 1 ; j++)
    {
        if(str[j] != c)
        {//daca e diferit de caracterul c atunci copiez in matrice
            ofter[i][k] = str[j];//copiem
            k++;//incremetez coloana matricii
        }
        if( (str[j] == c) && (str[j + 1] != c) && (k != 0) )
        {//altfel adaug spatiu si sfarsesc linia
            ofter[i][k] = ' ';
            ofter[i][k + 1] = '\0';
            i++;//incrementez linia matricii
            k = 0;
        }
    }
    *nr_oper = i + 1;
}

//calcularea lungimii celui mai lung sir de caractere;
int l_max_l(char original[MAX][MAX], int nr_line)
{
    int max = strlen(original[0]) ;
    int i;
    for(i = 1 ; i < nr_line ; i++)
    {
        if (max < strlen(original[i]))
        { 
          max = strlen(original[i]);
        }
    }

    return max;
}

//sterge spatiile de la sfarsitul fiecarui sir de caractere;
void del_end_space(char result[MAX][MAX], int result_line_count)
{
  int i, len;
  for(i = 0; i < result_line_count; i++)
  {
    len = strlen(result[i]) - 2;
    while(result[i][len] == ' ' || result[i][len] == '\t')
    {//cat timp avem spatii sau taburi la sfarsit le eliminam
      strcpy(result[i] + len , "\n\0");
      len-- ;
    }
  }
}

//adauga spatii la sfarsitul unui sir de caractere;
void add_space(char str[MAX], int len)
{
  if(strlen(str) - 1 == len)
  {
    return ;
    }
  else 
  {
     add_space( strcat(str, " "), len);
  }
}

void wrap(char parametri[MAX][MAX], int *ok,
          char original[MAX][MAX], int original_line_count,
          char result[MAX][MAX] ,int *result_line_count)
{
  int max = atoi(parametri[1]);
  int i, j, n, k = 0;
  char temp[MAX][MAX];//pentru salvarea temporara a cuvintelor
  if(parametri[2][0] != '\0' )
  {
    *ok = 1;
    return;
  }//sterg spatiile de la srasitul liniilor
  del_end_space(original, original_line_count);
  for(i = 0; i < original_line_count; i++)
  {//parcurgem toata matricea
    if(strlen(original[i]) == 1)
     {//daca e newline termin linia
      strcat(result[k], "\0");
      k++ ;//incrementam
      strcat(result[k], "\n\0");//copiez newline
      k++ ;//incrementam
       continue ;
      }
    if( ((original[i][0] == ' ' || original[i][0] == '\t' ) && 
        strlen(original[i - 1]) ==  1) || (i == 0 && original[0][0] == ' ' ))
    {//daca e prima linie de paragraf
      while(nr_space(original[i]) > max + 1)
      {//daca sunt mai multe spatii ca lungimea dorita
        strcpy(result[k], "\n\0" );//copiez un newline
        k++;//incrementam
        //sterg spatiile pe care le-am parcurs
        strcpy(original[i], original[i] + max + 1 );
      }//adaugam spatiile ramase daca sunt mai mici ca lungimea dorita
      strncpy(temp[0], original[i] , nr_space(original[i]));
      strcat(result[k], temp[0]);
      strcpy(original[i], original[i] + nr_space(original[i]));
      strcpy(temp[0], "\0");
      
    }
    strcpy(temp[0], "\0");
    my_strtok(temp, original[i], ' ', &n);
    for(j = 0; j < n; j++)
    {
      if(strlen(temp[j]) - 1> max)
      {//tratez eroare de Cannot wrap!
        *ok = 2;
        return ;
      }

      if(strlen(result[k]) + strlen(temp[j]) - 1 > max)
      {//daca nu incape urmatorul cuvant termin linia
        result[k][strlen(result[k]) - 1] = '\n';
        k++;
      }
    
      if( (strlen(result[k]) + strlen(temp[j]) <= max + 1)  && (j + 1 == n)
           && strlen(original[i + 1]) != 1)
      {//adaug fiecarui cuvant un spatiu
        temp[j][strlen(temp[j]) - 1] = ' ';
      }
      //adaug cuvintele in result
      strcat(result[k], temp[j]);
   
    }
  }
  //terminal linia result
    strcat(result[k], "\n\0");
   k++;
  *result_line_count = k;

}

void center(char parametri[MAX][MAX], int *ok,
            char original[MAX][MAX], int original_line_count,
            char result[MAX][MAX], int *result_line_count)
{//aplicam ca la align right doar ca cu un numar injumatatit de spatii
  int max =l_max_l(original, original_line_count) - 1 ;
  int start_line = 0;
  int end_line = original_line_count;
  int i, l;
  if(parametri[1][0] != '\0')
  {
    start_line = atoi(parametri[1]);
  }
  if(parametri[2][0] != '\0')
  {
    end_line = atoi(parametri[2]);
  }
  if(start_line < 0 || end_line < 0 || start_line > end_line)
  {
    *ok = 1;
    return;
  }
  if(start_line >= original_line_count)
  {
    return ;
  }
  if(end_line > original_line_count)
  {
    end_line = original_line_count;
  }
  for(i = 0; i < original_line_count ; i++)
  {//parcurgem toata matricea
   if(i >= start_line && i <= end_line)
   {//daca se afla intre liniile de editat
     l = (max + strlen(original[i]) ) / 2;
     if(strlen(original[i]) == 1)
     { 
        strcpy(result[i], "\n\0");
        continue;
     }
     reverse(original[i], 0, strlen(original[i]) - 1);
     add_space(original[i], l);
     reverse(original[i], 0, strlen(original[i]) - 1);
   }

     strcpy(result[i], original[i]);

  }
  *result_line_count = original_line_count;
  del_end_space(result, *result_line_count);

}

//aliniera la stinga a sirurilor de caractere;
void align_left(char parametri[MAX][MAX], int *ok,
                char original[MAX][MAX], int original_line_count,
                char result[MAX][MAX], int *result_line_count)
{

  int start_line = 0;
  int end_line = original_line_count;
  int i, n = 0;
  if(parametri[1][0] != '0')
  {
    start_line = atoi(parametri[1]);
  }
  if(parametri[2][0] != '\0')
  {
    end_line = atoi(parametri[2]);
  }
 
  if(start_line < 0 || end_line < 0 || start_line > end_line ||
     start_line >= original_line_count)
  {//trateaza erorile
    *ok = 1;
    return;
  }
  for(i = 0; i < original_line_count ; i++)
  {//parcurgem toata matricea
    if(i  >= start_line && i <= end_line)
    {//daca se afla intre liniile de editat
      n = nr_space(original[i]);//aflam numarul de spatii de pus
    }//copiez in result originalul fara spatii
    strcpy(result[i] , original[i] + n );
    n = 0;
  }
  *result_line_count = original_line_count;

}

void align_right(char parametri[MAX][MAX], int *ok,
                 char original[MAX][MAX], int original_line_count, 
                 char result[MAX][MAX], int *result_line_count)
{
  int max = l_max_l(original, original_line_count);
  int start_line = 0;
  int end_line = original_line_count;
  int i;
  if(parametri[3][0] != '\0' )
  {
    *ok = 1;
    return ;
    }
  if(parametri[1][0] != '\0')
  {
    start_line = atoi(parametri[1]);
  }
  if(parametri[2][0] != '\0')
  {
    end_line = atoi(parametri[2]);
  }
  if(start_line >= original_line_count)
  {
    return ;
  }
  if(start_line < 0 || end_line < 0 || start_line > end_line 
                                    || parametri[3][0] != '\0')
  {//tratez erorile
    *ok = 1;
    return;
  }
  if(end_line > original_line_count){end_line = original_line_count;}
  for(i = 0 ; i < original_line_count ; i++)
  {//parcurgem toata matricea
   if(i >= start_line && i <= end_line)
   {//daca se afla in liniile de editat
     if(strlen(original[i]) == 1)
     {
       strcpy(result[i], "\n\0"); continue;
     }
     reverse(original[i], 0, strlen(original[i]) - 1);
     //inversam linia
     strcpy(original[i], original[i] + nr_space(original[i]));
     //adaugam spatii la sfarsit
     add_space(original[i], max - 1);
     //inversam linia
     reverse(original[i], 0, strlen(original[i]) - 1);
   }
    //copiez din original in result
     strcpy(result[i], original[i]);

  }

  *result_line_count = original_line_count;

}

void justify(char parametri[MAX][MAX],
             char original[MAX][MAX], int original_line_count, 
             char result[MAX][MAX], int *result_line_count)
{
  int max = l_max_l(original, original_line_count);
  int i, j, n, k , r;
  int start_line = 0;
  int end_line = original_line_count;
  char temp[MAX][MAX];
  if(parametri[1][0] != '\0') 
  {
    start_line = atoi(parametri[1]);
  }
  if(parametri[2][0] != '\0') 
  {
    end_line = atoi(parametri[2]);
  }
  for(i = 0; i < original_line_count; i++)
  {//parcurgem toata matricea
    if( i <= end_line && i>= start_line)
    {//daca se afla intre liniile de editat
    if(strlen(original[i + 1]) == 1 ||  strlen(original[i]) == 1 
                                 || i + 1 == original_line_count)
    {//daca linia e ultima din paragraf ii facem align left
      strcpy(result[i], original[i] + nr_space(original[i]));
      continue;//trecem peste
    }
      if(original[i][0] == ' ' || original[i][0] == '\t')
      {//fac align left
        strcpy(temp[0], original[i] + nr_space(original[i]) );
        strcpy(original[i], temp[0]);
        
      }
      my_strtok(temp, original[i], ' ', &n);
      //aflam numarul de spatii pe care trebuie sa le adaugam
      j = max - strlen(original[i]); 
      //aflam cum trebuie sa distribuim spatiile
      r = j / (n - 1) ;
      //si scadem din numarul total pe cele distibuite
      j -= r * (n - 1)  ;
      for(k = 0 ; k < n - 1 ; k ++)
      {//adaugam spatiile impartite pe pozita dorita
        if (j == 0)
        {//daca am redistribuit spatiile
          r--;//sdacem r
        }
        add_space(temp[k], strlen(temp[k]) + r );
        strcat(result[i], temp[k]);
        j--;//scad cate un spatiu din cele ramase
      }
        strcat(result[i], temp[k]);//copii linia cu spatii
    }
    else
    {//daca nu e intre linile de formatat
      strcpy(result[i], original[i]);//copiez neformatat
    }
  }
  *result_line_count = original_line_count;
}

void paragrafs(char parametri[MAX][MAX], int *ok,
               char original[MAX][MAX], int original_line_count,
               char result[MAX][MAX], int *result_line_count)
{ 

  int start_line = 0;
  int end_line = original_line_count;
  int i, nr_sp = atoi(parametri[1]) ;
  char spatii[MAX] = MAXSPACE ;
  if(parametri[4][0] != '\0' || parametri[1][0] == '\0')
  {//tratez erorile
    *ok = 1;
    return;
    }
  if(parametri[2][0] != '\0')
  {
    start_line = atoi(parametri[2]);
  }
  if(parametri[3][0] != '\0')
  {
    end_line = atoi(parametri[3]);
  }
  if(start_line >= original_line_count){return ;}
  if(start_line < 0 || end_line < 0 || start_line > end_line)
  {//tratez erorile legate de linii
    *ok = 1;
    return;
  }
  if(end_line > original_line_count)
  {
     end_line = original_line_count;
  }
  for(i = 0 ; i < original_line_count ; i++)
  {//parcurgtoata matricea
    
   if(i >= start_line && i <= end_line)
   {//aplicam aceeasi logica ca la align left
     if(((original[i - 1][0] == '\n') && (original[i][0] != '\n')) || i == 0)
     {  //doar pentru prima linie dintr-un paragraf
        strcpy(spatii + nr_sp , original[i]+ nr_space(original[i]));
        strcpy(result[i], spatii);
        strncpy(spatii, MAXSPACE, nr_sp + 1);
     }
     else
     {
       strcpy(result[i], original[i]);
     }
   }
    else
    {
     strcpy(result[i], original[i]);
    }
  }

  *result_line_count = original_line_count;

}

void list(char parametri[MAX][MAX], int *ok,
          char original[MAX][MAX], int original_line_count,
          char result[MAX][MAX], int *result_line_count)
{
    int i;
    int start_line = 0;
    int end_line = original_line_count;
    char temp[MAX][MAX];
    char type = parametri[1][0];
    char c = parametri[2][0];
   
    if(parametri[3][0] != '\0')
    {
      start_line = atoi(parametri[3]);
    }
    if(parametri[4][0] != '\0')
    {
      end_line = atoi(parametri[4]);
    }
    if(start_line >= original_line_count) 
    {
      return ;
    }
    if(start_line < 0 || end_line < 0 || start_line > end_line || c == '\0')
    {
      *ok = 1;
      return;
    }
    if(end_line > original_line_count)
    {
      end_line = original_line_count;
    }
    if(type == 'n' || type == 'b' || type =='a' || type == 'A')
    {
     del_end_space(original, original_line_count);
    }
    for( i = 0 ; i < original_line_count ; i++)
    {//parcurgem toata matricea
     if( i >= start_line && i <= end_line )
     {//verific tipul listei
        switch (type)
      {//pentru fiecare lista cream un antet ce-l punem in fata liniei
        case 'n'://daca e numerica 
          if( i - start_line < 9)
          {//trebuie adaugat doar o cifra
            temp[i][0] = i - start_line + '1';
            temp[i][1] = c;
            temp[i][2] = ' ';
            strcpy(temp[i] + 3, original[i] + nr_space(original[i]) );
            
          } 
          else
          {//trebuie adaugat un numar de 2 cifre
            sprintf(temp[i], "%c%c%c%c%s", (((i - start_line + 1) / 10)+ '0'),
                    (((i - start_line+ 1) % 10 ) + '0'), c, ' ',
                                         original[i] + nr_space(original[i]));
          }
          break;
        case 'a'://daca e alfabetica
        case 'A':
          sprintf(temp[i], "%c%c%c%s", (i - start_line)+ type, c, ' ',
                                 original[i] + nr_space(original[i]));
          break;
        case 'b'://daca e bullet
          temp[i][0] = c;
          temp[i][1] = ' ';
          strcpy(temp[i] + 2, original[i] + nr_space(original[i]));
          break;
        default://in caz de eroare
          *ok = 1;
          return ;
      }
      
      strcpy(result[i], temp[i] + nr_space(original[i]));
     }
     else
     {
       strcpy(temp[i],original[i]);
     }
     strcpy(original[i], temp[i]);
    }
    copy(original, original_line_count, result, result_line_count);
  *result_line_count = original_line_count; 
}

void order_list(char parametri[MAX][MAX], int *ok,
                char original[MAX][MAX], int original_line_count,
                char result[MAX][MAX], int *result_line_count)
{//acelasi algoritm ca la list doar ca le sortez
    int i, z = 0;
    int start_line = 0;
    int end_line = original_line_count;
    char temp[MAX][MAX];
    char type = parametri[1][0];
    char c = parametri[2][0];
    if(parametri[4][0] != '\0')
    {
      start_line = atoi(parametri[4]);
    }
    if(parametri[5][0] != '\0')
    {
      end_line = atoi(parametri[5]);
      z++;//daca avem limita de sfarsire fac sortera + 1
      }
    if(start_line >= original_line_count)
    {
      return ;
    }
    if(start_line < 0 || end_line < 0 || start_line > end_line ||
      (parametri[3][0] != 'a' && parametri[3][0] != 'z') ) 
    {
      *ok = 1;
      return;
    }
   if(end_line > original_line_count){end_line = original_line_count;}
   
    if(type == 'n' || type == 'b' || type =='a' || type == 'A')
    {
      if(parametri[3][0] == 'a')
      {
        sort_inc(original, start_line, end_line + z);
      }
      if(parametri[3][0] == 'z')
      {
        sort_dec(original, start_line, end_line + z);
      }
      del_end_space(original, original_line_count);
    }
    for( i = 0 ; i < original_line_count  ; i++)
    {
     if( i >= start_line && i <= end_line )
     {
        switch (type)
      {
        case 'n':
          if( i - start_line < 9)
          {
            temp[i][0] = i - start_line + '1';
            temp[i][1] = c;
            temp[i][2] = ' ';
            strcpy(temp[i] + 3, original[i] + nr_space(original[i]));
            
          } 
          else
          {
            sprintf(temp[i], "%c%c%c%c%s", (((i - start_line + 1) / 10 )+ '0'),
                   (((i - start_line+ 1) % 10 ) + '0'), c, ' ',
                                          original[i] + nr_space(original[i]));
          }
          break;
        case 'a':
        case 'A':
          sprintf(temp[i], "%c%c%c%s", (i - start_line)+ type, c, ' ',
                                 original[i] + nr_space(original[i]));
          break;
        case 'b':
          temp[i][0] = c;
          temp[i][1] = ' ';
          strcpy(temp[i] + 2, original[i] + nr_space(original[i]));
          break;
        default:
          * ok = 1;
          return ;
      }
      strcpy(result[i], temp[i] + nr_space(original[i]));
     }
     else
     {
       strcpy(temp[i],original[i]);
     }
    }
    copy(temp, original_line_count, result, result_line_count);
  *result_line_count = original_line_count; 
}

void rezolvare(char *argv[], char buf[MAX],
               char original[MAX][MAX], char result[MAX][MAX])
{
  int original_line_count = 0,  // number of lines in the input file
      result_line_count = 0,    // number of lines in the output file
      i, error = 0, len, n, m, //error - eroarea
      new_line_count = 0;  // numarul de linii pentru back-up
  char operations[MAX][MAX], //operatiile, n - numarul de operatii
       parametri[MAX][MAX], //paramtrei, m - numarul de parametri
       new[MAX][MAX]; //matrice pentru back-up
  //citesc fisierul
  reading(argv[2], original, &original_line_count , buf);
  //back-up in caz de eroare
  copy(original, original_line_count, new, &new_line_count);
  //creare matricii de operatii
  my_strtok(operations, argv[1], ',', &n); 
  if(n > 10)//daca sunt mai mult de 10 operatii
  {
    printf("Too many operations! Only the first 10 will be applied.\n");
    n = 10;//face doar 10
  }
  for(i = 0 ; i < n ; i++)
  {//creare matricii de parametri
    my_strtok(parametri, operations[i], ' ', &m);
    //daca is mai multe operatii wrap, aplic doar ultima
    if( (parametri[0][0] == 'W' || parametri[0][0] == 'w') && 
      ( strchr(operations[i + 1] , 'W') || strchr(operations[i + 1] , 'w')))
    {
      continue;
    }
    //tratarea fiecarui caz aparte
    switch(parametri[0][0])
    {
      case 'W':
      case 'w':
           wrap(parametri, &error, original, original_line_count,
                                     result, &result_line_count);
          break;
      case 'C':
      case 'c':
          center(parametri, &error, original, original_line_count,
                                      result, &result_line_count);
          break;
      case 'L':
      case 'l':
          align_left(parametri, &error, original, original_line_count,
                                          result, &result_line_count);
          break;
      case 'R':
      case 'r':
          align_right(parametri, &error, original, original_line_count,
                                           result, &result_line_count);
          break;
      case 'J':
      case 'j':
          justify(parametri, original, original_line_count,
                               result, &result_line_count);
          break;
      case 'P':
      case 'p':
          paragrafs(parametri, &error, original, original_line_count,
                                         result, &result_line_count);
          break;
      case 'I':
      case 'i':
          list(parametri, &error, original, original_line_count,
                                    result, &result_line_count);
        break;
      case 'O':
      case 'o':
          order_list(parametri, &error, original, original_line_count,
                                          result, &result_line_count);
          break;
      default :
          error = 1;
          break;     
    }
    //golesc matricea de parametri
    del_text(parametri, &m);
    if(i + 1 < n)
    { //daca nu e ultima operatie copiem result in original
      del_text(parametri, &m);
      del_text(original , &original_line_count);
      copy(result, result_line_count , original, &original_line_count);
      //golesc resultul
      del_text(result , &result_line_count);
    }
      len = strlen(result[result_line_count - 1]) - 2;
     if((result[result_line_count - 1][len] == ' '))
     {//daca exista sterg ultimul spartiu din fisier
        result[result_line_count - 1][len] = '\n';
        result[result_line_count - 1][len + 1] = '\0';
     }
  }
  //tratarea erorilor
 if (error)
    {
      if(error == 2)
      {
        printf("Cannot wrap!\n");
      }
      else
      {
        printf("Invalid operation!\n");     
      }
      //copierea back-up
        copy(new, new_line_count, result, &result_line_count);
    }
  //scrierea in fisier
  writing(argv[3], result, result_line_count);
}

int main(int argc, char *argv[]) 
{
  char buf[MAX],               // buffer used for reading from the file
      original[MAX][MAX],     // original text, line by line
      result[MAX][MAX];       // text obtained after applying operations
    if (argc != 4) {  // invalid number of arguments
    fprintf(stderr,
            "Usage: %s operations_string input_file output_file\n",
            argv[0]);
    return -1;
  }
  rezolvare(argv, buf, original, result);
  return 0 ;
}
