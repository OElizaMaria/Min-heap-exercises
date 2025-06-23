#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct BTreeNode
{
    int frecventa;
    char nume[506];
    struct BTreeNode *left, *right;
} BTreeNode;

typedef struct MinHeap
{
    int data[500];
    char nume[500][500];
    int length;
} MinHeap;

void swap (int *a, int *b)
{
    int aux;
    aux=*a;
    *a=*b;
    *b=aux;
}

void swap2(char a[501], char b[501])
{
    char aux[506];
    strcpy(aux,a);
    strcpy(a,b);
    strcpy(b,aux);
    
   
}

void sortForHeap(MinHeap *h)
{
    int ok = 1;

    while (ok == 1)
    {
        ok = 0;
        for (int i = 0; i < h->length - 1; i++)
        {
            if (h->data[i] > h->data[i + 1])
            {
                swap(&h->data[i], &h->data[i + 1]);
                swap2(h->nume[i], h->nume[i + 1]);
                ok = 1;
            }

            if (h->data[i] == h->data[i + 1])
            {
                if (strcmp(h->nume[i], h->nume[i + 1]) > 0)
                {
                    swap(&h->data[i], &h->data[i + 1]);
                    swap2(h->nume[i],h->nume[i + 1]);
                    ok = 1;
                }
            }
        }
    }
}


void extrage_si_creeaza(MinHeap *h, int n)
{       
    // adauga nodurile necesare pentru formarea
    //  arborelui
    // iar apoi face call la functia
    // initializare_BTree
    int nr_nou;

    int i = 0;
    while (h->length < 2 * n - 1)
    {
        nr_nou = h->data[i] + h->data[i + 1];
        char nume_nou[260];

        strcpy(nume_nou, h->nume[i]);
        strcat(nume_nou, h->nume[i + 1]);
        h->data[h->length] = nr_nou;
        strcpy(h->nume[h->length], nume_nou);
        h->length = h->length + 1;
        sortForHeap(h);
        i = i + 2;
    }
}

void initializare_nod(BTreeNode *b, int n, char *s)
{

    b->frecventa = n;
    strcpy(b->nume, s);
    b->left = NULL;
    b->right = NULL;
}

BTreeNode *initializare_arbore_binar(MinHeap h)
{
    BTreeNode *radacina;
    radacina = (BTreeNode *)malloc(sizeof(BTreeNode));
    initializare_nod(radacina, h.data[h.length - 1], h.nume[h.length - 1]);

    BTreeNode *q[100];
    BTreeNode *temp;
    int back = -1;
    q[++back] = radacina;
    int i = h.length - 2;
    // dupa ce am stabilit radacina
    // trecem la urmatorul element

    while (i > 0)
    {
        int front = -1;
        int back = -1;
        q[++back] = radacina;
        // resetam de fiecare data
        // dupa ce am adaugat elemente noi
        while (front != back)
        {
            temp = q[++front];
            int nr = h.data[i] + h.data[i - 1];
           
            if ( nr == temp->frecventa && strstr(temp->nume,h.nume[i])!=0)
            {
                BTreeNode *left;
                BTreeNode *right;
                left = (BTreeNode *)malloc(sizeof(BTreeNode ));
                if( left ==NULL)
                printf("Alocare esuata\n");
                right = (BTreeNode *)malloc(sizeof(BTreeNode ));
                if(right == NULL)
                printf("Alocare esuata\n");
                initializare_nod(left, h.data[i - 1], h.nume[i - 1]);
                initializare_nod(right, h.data[i], h.nume[i]);
                temp->left = left;
                temp->right = right;
                i = i - 2;
                // adaugam daca am gasit
                q[++back] = left;
                q[++back] = right;
                // adaugam in queue noile elemente
                // care trebuie verificate
                // break;
            }

            else
            {
                if (temp->left)
                    q[++back] = temp->left;
                if (temp->right)
                    q[++back] = temp->right;
                // daca nu am gasit adaugam in elementele ce trebuie
                // verificate mai departe
            }
        }
    }
    

    return radacina;
}



void print_binary(BTreeNode *radacina, FILE* fout)
{
    BTreeNode *q[100];
    int front = -1;
    int back = -1;
    q[++back] = radacina;
    while (front != back)
    {
        int cate = back - front;

        for (int i = 0; i < cate - 1; i++)
        {
            BTreeNode *temp = q[++front];
            fprintf(fout,"%d-%s ", temp->frecventa, temp->nume);

            if (temp->left != NULL)
                q[++back] = temp->left;
            if (temp->right != NULL)
                q[++back] = temp->right;
        }

        // caz special
        // ultimul element pt a nu avea
        // trailing whitespace in out
        BTreeNode *temp = q[++front];
        fprintf(fout,"%d-%s", temp->frecventa, temp->nume);
        if (temp->left != NULL)
            q[++back] = temp->left;
        if (temp->right != NULL)
            q[++back] = temp->right;
        fprintf(fout,"\n");
    }
}


void decodificare(char *s, BTreeNode *radacina, FILE* fout)
{
    int n = strlen(s);
    BTreeNode *temp;
    temp = radacina;

    for (int i = 0; i < n; i++)
    {   
       if (s[i]=='\n') {
            if (temp->right ==NULL && temp->left ==NULL)
                fprintf(fout,"%s", temp->nume);
            fprintf(fout, "\n");
       }
        
         if ((int)(s[i] - '0') == 0)
        {
            if (!temp->left)
            {
                fprintf(fout,"%s ", temp->nume);
             
                if(s[i]!='\n')
                temp = radacina;
            }
                temp = temp->left;
        }

        else if ((int)(s[i] - '1') == 0)
        {
            if (!temp->right)
            {
                fprintf(fout,"%s ", temp->nume);
             
                if(s[i]!='\n')
                temp = radacina;
            }
            
                temp = temp->right;
        }
    }
}


void codificare(char *s, BTreeNode *radacina, FILE* fout)
{

    BTreeNode *temp;
    temp = radacina;


    while (1)
    {
        if(strcmp(temp->nume,s)==0)
        break;

        else if (temp->left && strstr(temp->left->nume, s))
        { 
                fprintf(fout,"0");
             temp = temp->left;

        
        }
        else if (temp->right && strstr(temp->right->nume, s))
        {  
          
                fprintf(fout,"1");
            temp = temp->right;
        
        }

        else break;
    }
}

int verifica(char** s, char* nume, int n)
{
    int ok=1;
    for(int i=0;i<n; i++)
    {
        if(!strstr(nume,s[i]))
        ok = 0;
    }
    return ok;
}

void parinte(char** s, BTreeNode* radacina, int n,FILE *fout)
{
    BTreeNode* temp;
    temp=radacina;
    while(1)
    {
        if(verifica(s,temp->left->nume,n)==1)
        temp=temp->left;

        else if(verifica(s,temp->right->nume,n)==1)
        temp=temp->right;

        else break;
    }
    fprintf(fout,"%s\n",temp->nume);
}

void free_tree(BTreeNode *nod)
{
    if(nod != NULL)
    {  
        if(nod->right != NULL)
        free_tree(nod->right);
        if(nod->left != NULL)
        free_tree(nod->left);
        free(nod);
    }
}


int main(int argc, char **argv)
{
    
    struct MinHeap h;

    int c1 = 0, c2 = 0, c3 = 0, c4 = 0;

    // stabilim care e cerintele ce trebuie completate
   
        if (strcmp(argv[1], "-c1") == 0)
            c1++;
        if (strcmp(argv[1], "-c2") == 0)
            c2++;
        if (strcmp(argv[1], "-c3") == 0)
            c3++;
        if (strcmp(argv[1], "-c4") == 0)
            c4++;
      

    FILE *fid=fopen(argv[argc - 2],"r");

    //  INCEPEM CITIREA
    
    int nr_sateliti;
    fscanf(fid,"%d",&nr_sateliti);
    FILE *fout=fopen(argv[argc-1],"w");
 

    h.length=nr_sateliti;
    
    for (int i = 0; i < nr_sateliti; i++)
    {   
        fscanf(fid,"%d %s",&h.data[i],h.nume[i]);
        h.nume[i][strlen(h.nume[i])]='\0';   
    }

    sortForHeap(&h);

    extrage_si_creeaza(&h, nr_sateliti);
    
    BTreeNode *radacina;
    radacina = (BTreeNode *)malloc(sizeof(BTreeNode ));
    radacina = initializare_arbore_binar(h);
    if(c1 != 0)
   { print_binary(radacina,fout);
    free_tree(radacina);
   }
    if(c2 != 0)
    {   int nr_codif;
        fscanf(fid,"%d",&nr_codif);
        
        char s[500];
        for (int i=0; i<=nr_codif;i++)
        {
            fgets(s,500,fid);
            //
            if(s[0]=='\n')
            s[0]=' ';

   
            decodificare(s, radacina,fout);
        }



    }
    
    if (c3 != 0)
    {   int nr_de_codificat;
       
        fscanf(fid,"%d",&nr_de_codificat);
        //printf("%d\n",nr_de_codificat);
        char *s2 = malloc(20 * sizeof(char));
        if(s2==NULL)
        printf("Alocare esuata\n");
      

        for (int i = 0; i < nr_de_codificat; i++)
        {
            fscanf(fid,"%s", s2);
            codificare(s2, radacina,fout);
        }
        //printf("\n");
        free(s2);
    }

    if (c4 !=0 )
    {
        int numar;
        fscanf(fid,"%d",&numar);
      

        char **s3 = malloc(sizeof(char*));
        if (s3 == NULL)
        printf("Alocare esuata\n");

        for (int i = 0; i < numar; i++)
        {
            
            s3[i]=malloc(20*sizeof(char));
            fscanf(fid,"%s",s3[i]);
           
        }
        parinte(s3,radacina,numar,fout);

      
}
    fclose(fid);
    fclose(fout);
    
    
}
