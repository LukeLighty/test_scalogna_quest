#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int nZone =15;
int deleteHead=0;
int deleteTail=0;
int createdMap=0;

typedef struct Zona_segrete{
    struct Zona_segrete *prev;
    int number;
    struct Zona_segrete *succ;
}Mappa;

Mappa *pFirst;
Mappa *pLast;



//HEAD PRINT
void printLista(Mappa *p){
    int n=0;
    while(p!=NULL){
        //printf("%d- %d-(%p) %d\n",n++,p->number,p,nZone);
        printf("%d",p->number);
        
        if((p->succ)==NULL)
            printf("\n");
        else
            printf(" <> ");
        
        p=p->succ;
    }
}

//TAIL PRINT
void printListaCoda(Mappa *p){

    while(p!=NULL){
        printf("%d",p->number);
        
        if((p->prev)==NULL)
            printf("\n");
        else
            printf(" <> ");
        
        p=p->prev;
    }
}



void cancellaZonaMappa(Mappa *lista[],int key){
    
    if(lista[(pFirst->number)]==NULL)
        printf("no nodi");
    else{
        for(int n=(pFirst->number);n<nZone;n++){
            //printf("%d- %d-(%p) %d\n",n,lista[n]->number,lista[n],nZone);
            if((lista[n])->number==key){
                Mappa*temp = (lista[n]->succ);
                
                
                //se si vuole eliminare una zona a posizione n, escluso gli estremi,
                //devono essere reindirizzari i puntatori prev e succ
                
                if((key!=(pFirst->number))&&(key!=(pLast->number))){
                    free(lista[n]);
                    lista[n]=temp;
                    
                    lista[n]->prev = lista[n-1];
                    lista[n-1]->succ=lista[n];
                }
                
                //ad uso per testing printf("\n\n%d - %d\n\n\n\n%d - %d\n\n",nZone,nZone-1,key,n);
                //cancellazione zona di coda della lista
                if(key==(pLast->number)){
                    free(lista[n]);
                    lista[n]=temp;
                    
                    lista[n-1]->succ=NULL;
                    pLast=lista[n-1];
                    deleteTail++;
                }
                
                //cancellazione zona di testa della lista
                if(key==(pFirst->number)){
                    free(lista[n]);
                    lista[n]=temp;
                    
                    lista[n+1]->prev=NULL;
                    pFirst=temp;
                    deleteHead++;
                }
                
                nZone--;
                break;
            }
        }
    }
}



void aggiungiZonaMappa(Mappa *lista[],int key){
    
        
    //AGGIUNGI IN TESTA
    if(key<=(pFirst->number)){
        lista[key] = calloc(1,sizeof(Mappa));
        lista[key]->number=key;
        pFirst->prev=lista[key];
        lista[key]->succ=pFirst;
        
        pFirst=lista[key];
        pFirst->prev=NULL;
    }//AGGIUNGI IN CODA
    else if(key>=(pLast->number)){
        lista[key] = calloc(1,sizeof(Mappa));
        lista[key]->number=key;
        
        pLast->succ=lista[key];
        lista[key]->prev=pLast;
        
        pLast=lista[key];
        pLast->succ=NULL;
    }//AGGIUNGI IN CENTRO
    else{
        Mappa *temp=pFirst;
        for(int n=0;n<nZone;n++){
            if(((temp->number)<=key)&&(((temp->succ)->number)>=key)){
                lista[key] = calloc(1,sizeof(Mappa));
                
                lista[key]->number=key;
                lista[key]->succ=temp->succ;
                lista[key]->prev=temp;
                
                temp->succ=lista[key];
                break;
            }
            temp=temp->succ;
        }
    }
    nZone++;
}


//alloca memoria e linka la lista doppiamente
void creaMappa(Mappa*lista[]){
    
    if(createdMap==0){
        for(int n=0;n<nZone;n++){
            lista[n] =calloc(1,sizeof(Mappa));
            lista[n]->number=n;
            
            if(n!=0){ //primo ciclo del for viene saltato per allocare memoria al successivo
                lista[n]->prev=lista[n-1];
                if(n!=(nZone))
                    lista[n-1]->succ=lista[n];
                else
                    lista[n]->succ=NULL;
            }
            else
                lista[0]->prev=NULL;
        }
        createdMap=1;    
    }else{
        for(int n=1;n<=15;n++){
            //QUESTO CAUSA stack smashing detected
            
            //aggiungiZonaMappa(lista,(pLast->number)+1);
        }
    }
    
}




int main(void){
     
    //alloca uno spazio di memoria per le 15 zone
    Mappa *lista[nZone];
    
    creaMappa(lista);
    
    pFirst = lista[0];
    pLast = lista[nZone-1];
    
    printLista(pFirst);
    
    cancellaZonaMappa(lista,pLast->number);
    printLista(pFirst);
    
    cancellaZonaMappa(lista,pFirst->number);
    printLista(pFirst);
    
    cancellaZonaMappa(lista,pFirst->number);
    printLista(pFirst);
    
    cancellaZonaMappa(lista,5);
    cancellaZonaMappa(lista,6);
    printLista(pFirst);
    printListaCoda(pLast);
    
    aggiungiZonaMappa(lista,0);
    printLista(pFirst);
    printListaCoda(pLast);
    
    aggiungiZonaMappa(lista,15);
    printLista(pFirst);
    printListaCoda(pLast);
    
    aggiungiZonaMappa(lista,0);
    printLista(pFirst);
    
    aggiungiZonaMappa(lista,5);
    printLista(pFirst);
    
    aggiungiZonaMappa(lista,6);
    printLista(pFirst);
    
    
    aggiungiZonaMappa(lista,14);
    printLista(pFirst);
    printf("%d\n",nZone);
    printf("%d\n",createdMap);
    creaMappa(lista);
    /*
    simulo un utente che aggiunge tante zone
    se fatto troppe volte cause malloc(): corrupted top size
    aggiungiZonaMappa(lista,nZone);
    aggiungiZonaMappa(lista,nZone);
    aggiungiZonaMappa(lista,nZone);
    aggiungiZonaMappa(lista,nZone);
    aggiungiZonaMappa(lista,nZone);
    aggiungiZonaMappa(lista,nZone);
    aggiungiZonaMappa(lista,nZone);
    aggiungiZonaMappa(lista,nZone);
    aggiungiZonaMappa(lista,nZone);
    */
    
    printLista(pFirst);
    
    puts("ok");
    return 0;
}