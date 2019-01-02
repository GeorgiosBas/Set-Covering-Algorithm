#include <stdio.h>
#include "genlib.h"
#include "simpio.h"
//afairese = remove
//red checks if universe is already in resault
//yellow checks if universe is already traversed
void afairesi(int a,int b,int pl,int number,int table[pl][number],int arxikoCount[pl],int uncoveredCount[pl],int metablitoCount[pl],int col_table[number],int keep);
bool check(int pl,int uncoveredCount[pl]);
bool red(int keep,int k,int pl,int number,int table[pl][number],int arxikoCount[pl],int uncoveredCount[pl],int metabalomenoCount[pl],int col_table[number]);
bool yellow(int k,int keep,int pl,int uncoveredCount[pl],int metabalomenoCount[pl],int number,int col_table[number]);
//import data
int main(){
    int i,j,pl,number,ap;
    printf("Give max sets(eg people)");
    scanf("%d",&pl);
    printf("Give max universes(eg skills)");
    scanf("%d",&number);
    int table[pl][number];
    for(i=0; i<pl; i++){
        for(j=0; j<number; j++){
            printf("person %d knows skill %d: 0 NO,1 YES: ",i+1,j+1);
            scanf("%d",&ap);
            table[i][j] = ap;
        }
    }
    int resaultCover[pl];
    int uncoveredCount[pl];
    int arxikoCount[pl];
    int metabalomenoCount[pl];
    int col_table[number];
    int sum = 0;
    for(i=0; i<pl; i++){
        resaultCover[i] = 0;
        uncoveredCount[i] = 0;
    }
    for(i=0; i<number; i++){
        for(j=0; j<pl; j++){
            if(table[j][i] == 1)sum = sum + 1;
        }
        col_table[i] = sum;
        sum = 0;
    }
    for(i=0; i<pl; i++){
        for(j=0; j<number; j++){
            if(table[i][j] == 1){
                uncoveredCount[i]++;
            }
        }
        arxikoCount[i] = uncoveredCount[i];
        metabalomenoCount[i] = uncoveredCount[i];
    }
    
    //code starts here
    int keep;
    int max,l;
    int m = 0;
    while(check(pl,uncoveredCount)){
        //finds max number of skills in one set 
        max = uncoveredCount[0];
        keep = 0;
        for(j=1; j<pl; j++){
            if(uncoveredCount[j]>max){
                max = uncoveredCount[j];
                keep = j;
            }
        }
        resaultCover[m] = keep;
        m++;
        //removes this universe from other sets
        afairesi(0,keep,pl,number,table,arxikoCount,uncoveredCount,metabalomenoCount,col_table,keep);
        afairesi(keep+1,pl,pl,number,table,arxikoCount,uncoveredCount,metabalomenoCount,col_table,keep);
        uncoveredCount[keep] = -100;
        for(l=0; l<pl; l++){
            metabalomenoCount[l] = arxikoCount[l];
        }
    }
    //print results
    for(i=0; i<m; i++){
        printf("Accepted: %d\n",resaultCover[i]+1);
    }
    return 0;
}

bool check(int pl,int uncoveredCount[pl]){
    int i,count = 0;
    for(i=0; i<pl; i++){
        if(uncoveredCount[i]>0)count++;
    }
    if(count>0)return TRUE;
    else return FALSE;
}

void afairesi(int a,int b,int pl,int number,int table[pl][number],int arxikoCount[pl],int uncoveredCount[pl],int metabalomenoCount[pl],int col_table[number],int keep){
    int k,l;
    for(k=0; k<number; k++){
            if(table[keep][k] == 1 && !(red(keep,k,pl,number,table,arxikoCount,uncoveredCount,metabalomenoCount,col_table))){
                for(l=a; l<b; l++){
                    if(table[l][k] == 1){
                        uncoveredCount[l]--;
                    }
                }
            }
    }
}

bool red(int keep,int k,int pl,int number,int table[pl][number],int arxikoCount[pl],int uncoveredCount[pl],int metabalomenoCount[pl],int col_table[number]){
    if(table[keep][k] == 1 && yellow(k,keep,pl,uncoveredCount,metabalomenoCount,number,col_table)){
        return TRUE;
    }
    else return FALSE;
}

bool yellow(int k,int keep,int pl,int uncoveredCount[pl],int metabalomenoCount[pl],int number,int col_table[number]){
    if(metabalomenoCount[keep] != uncoveredCount[keep]){
        metabalomenoCount[keep]--;
        return TRUE;
    }
    else{
        if(col_table[k] == 1)return TRUE;
        return FALSE;
    }
}


