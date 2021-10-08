#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int max(int a, int b){
  return a>b ? a : b ;
}
int min (int a, int b){
  return a<b ? a : b;
}
int evaluate(char* input,char player,int lastA,int lastB){
  int i;
  if( player =='A' ){
    if(lastA==0){
      if (input[lastA+1]=='0'){
        return 0;
      }
    }
    else if(lastA == strlen(input)-1){
      if (input[lastA-1]=='0'){
        return 0;
      }
    }
    else{
      if (input[lastA-1]=='0' || input[lastA+1]=='0'){
        return 0;
      }
    }
    return -1000;
  }
  else{
    if (lastB==-1){
      for (i=0;i<strlen(input);i++){
        if (input[i]=='0') return 0;
      }
    }
    else if(lastB==0){
      if (input[lastB+1]=='0'){
        return 0;
      }
    }
    else if(lastB == strlen(input)-1){
      if (input[lastB-1]=='0'){
        return 0;
      }
    }
    else{
      if (input[lastB-1]=='0' || input[lastB+1]=='0'){
        return 0;
      }
    }

    return 1000;
  }
}

int minimax(char*input, char player,int lastA, int lastB){
  //checkBfirst == 1 then this is the first time B goes
  int score = evaluate(input,player,lastA,lastB);
  // if we know either A or B win
  if (score != 0){
    // printf("%s\n",input);
    return score;
  }
  // if turn A - maximizier
  if (player == 'A'){
    int best =-10000,i;
    //Traverse all positions
    if(lastA==0){
      input[lastA+1]='A';
      best = max (best,minimax(input,'B',lastA+1,lastB));
      input[lastA+1]='0';
      if(best>0) return best;
    }
    else if (lastA==strlen(input)-1){
      input[lastA-1]='A';
      best = max (best,minimax(input,'B',lastA-1,lastB));
      input[lastA-1]='0';
      if(best>0) return best;
    }
    else{
      if (input[lastA+1]=='0'){
        input[lastA+1]='A';
        best = max (best,minimax(input,'B',lastA+1,lastB));
        input[lastA+1]='0';
        if(best>0) return best;
      }
      if(input[lastA-1]=='0'){
        input[lastA-1]='A';
        best = max (best,minimax(input,'B',lastA-1,lastB));
        input[lastA-1]='0';
        if(best>0) return best;
      }
    }
    return best;
  }
  // Turn B - minimizier
  else{
    int best=10000,i;
    if(lastB==-1){
      for(int i=0;i<strlen(input);i++){
        if(input[i]=='0'){
          input[i]='B';
          best= min (best,minimax(input,'A',lastA,i));
          input[i]='0';
          if(best<0) return best;
        }
      }
    }
    else if(lastB==0){
        if(input[lastB+1]=='0'){
          input[lastB+1]='B';
          best=min(best,minimax(input,'A',lastA,lastB+1));
          input[lastB+1]='0';
          if(best<0) return best;
        }
      }
    else if(lastB==strlen(input)-1){
      if(input[lastB-1]=='0'){
        input[lastB-1]='B';
        best=min(best,minimax(input,'A',lastA,lastB-1));
        input[lastB-1]='0';
        if(best<0) return best;
      }
    }
    else{
      if (input[lastB+1]=='0'){
        input[lastB+1]='B';
        best = min (best,minimax(input,'A',lastA,lastB+1));
        input[lastB+1]='0';
        if(best<0) return best;
      }
      if(input[lastB-1]=='0'){
        input[lastB-1]='B';
        best = min (best,minimax(input,'A',lastA,lastB-1));
        input[lastB-1]='0';
        if(best<0) return best;
      }
    }
    return best;
  }
}
char* solution(char* input)
{
    //write code here
    int i,result=0;
    for (i=0;i<strlen(input);i++){
      if(input[i]=='0'){
        input[i]='A';
        // printf("%d \n",i);
        result = minimax(input,'B',i,-1);
        input[i]='0';
        if(result>0) return "A";
      }
    }
    return "B";
    //return a string and not a char . Look below template of return.
    //return "A";
    //return "B"
}

int main(void) {

	int max = 100000;
	char *s=(char*)malloc(max*sizeof(char));
	scanf("%s",s);
	char *ans=solution(s);
  printf("%s",ans);
	return 0;
}
