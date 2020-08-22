#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct n{
    char adres[20];
    int sayac;		 
    struct n* next;
    struct n* prev;
};
typedef struct n node;

void bastir (node *r){   
    while(r != NULL){
        printf("%s,%d\t",r->adres,r->sayac);
        r = r->next;
    }
    printf("\n");
}

node * ekle(node *r, char x[], int t, int l, int *dif){  
	node *second_last, *sil;
	
	if (r == NULL){  
		r = (node *)malloc(sizeof(node));
        r->next = NULL;
        r->prev = NULL;
        strcpy(r->adres,x);  
        r->sayac = 1;		 
        bastir(r);			 
        return r;
	}
	
	node *iter = r;			
	
    while(iter->next != NULL){  
        if ( !strcmp(x,iter->adres) ){
            iter->sayac++;
            bastir(r);
            return r; 
        }
        iter = iter->next;
    }
    
    if ( !strcmp(x,iter->adres) ){ 
            iter->sayac++;
            
            if ((iter->sayac) > t){  
            	iter->prev->next=NULL;
				iter->prev=NULL;
				iter->next=r;
				iter->next->prev=iter;
				bastir(iter);	
            	return iter;
			}
            			
			bastir(r);	
            return r;
    }   
    											 
    node *temp = (node *)malloc(sizeof(node));	 
    strcpy(temp->adres,x);
    temp->sayac = 1;
	(*dif)++; 
    
    
    if (*dif>l){	
    	second_last = r; 
    while (second_last->next->next != NULL)	
        second_last = second_last->next; 
	
	sil = second_last->next;	
	second_last->next = NULL;
	free(sil);	
	}
    
    temp->prev = NULL;  
    temp->next = r;
    r->prev=temp;
    bastir(temp);	
    return temp;      
}

void temizle(node *r){  
	node *iter;
	
	iter = r->next;
	while (iter != NULL) {   
    r->next = iter->next;	
    iter->next = NULL;		
    free(iter);
    iter = r->next;	
	}
	r->next=NULL;
	r->prev=NULL;
	free(r); 
	printf("Liste silinmistir!");
}

int main (){
	node *root;
    root = NULL;
    int i, t, l, dif=1, listeyi_sil=3, secenek=4;
	char girdi[20], kontrol[]="cikis", ch='A';
	FILE *fp;

	
	while (secenek != 0 && secenek != 1){
		printf("String olarak okumak icin 0'a, 'input.txt' dosyasindan okumak icin 1'e basiniz!\n");
		scanf("%d",&secenek);
		if ( secenek != 0 && secenek != 1)
			printf("\nHatali bir giris yaptiniz! Lutfen tekrar deneyiniz!\n");
	}
	
	if (secenek == 0){
		
		printf("Sayfalar icin esik degerini (T) giriniz: ");
		scanf("%d",&t);
		printf("Buffer'in kapasitesini (L) giriniz: ");
		scanf("%d",&l);
		
		printf("Lutfen sayfa girisi yapiniz, sayfa girisi bittiginde 'cikis' yazip islemi bitirebilirsiniz.\n");
		scanf("%s",girdi);
		while ( strcmp(girdi,kontrol) ){
			root = ekle(root,girdi,t,l,&dif);
			scanf("%s",girdi);
		}	
	}
	
	else{
		fp = fopen("input.txt","r");  
		if (fp == NULL){
			printf("Dosya acilamadi!");
			return 0;
		}
		else{
     	
	do {
		fscanf(fp, "T=%d , L=%d", &t, &l);  
     	if (fscanf(fp,"%s",girdi)){
     		root = ekle(root,girdi,t,l,&dif);  
		 }
  	} while (!feof(fp));
	}
	fclose (fp);	
	}
	
	while (listeyi_sil != 0 && listeyi_sil != 1){
		printf("\nListeyi temizlemek ister misiniz? Temizlemek icin 1'e', temizlemeden sonlandirmak icin  0'a basiniz!\n");
		scanf("%d",&listeyi_sil);
		if (listeyi_sil != 0 && listeyi_sil != 1)
			printf("\nHatali bir giris yaptiniz!");
	}
	
	if (listeyi_sil == 1){
		temizle(root);
		printf("\nProgram basariyla sonlandi. Programdan cikiliyor...");
	}
	else{
		printf("\nProgram basariyla sonlandi. Programdan cikiliyor...");
	}
	return 0;
}
