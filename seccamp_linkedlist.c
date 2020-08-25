/////////////////////////////////////////////////////////////////////////////////
//
// Security Camp 2020 応募課題 集中コース Y-1
//
// 課題c
// C.1. C言語で双方向リンクリストとそれを操作する関数を作り、ソースコードを提出してください。
// リンクリストを生成する関数、要素を任意の場所に挿入する関数、全ての要素を順に標準出力に印字する関数、の3つがあれば十分です。
// やる気があればもっとたくさんの機能を実装しても構いません！
//
/////////////////////////////////////////////////////////////////////////////////

/**
* @file saccamp_linkedList.c
* @author Yukari Hayashi
* @date 2020-08-25
**/

/*
仕様

command_number
0:操作を終了
1:要素を追加
2:要素を出力

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

// リスト用の構造体を定義
typedef struct node{
  int         alph; // データ
  struct node *next; // 次の要素へのポインタ
  struct node *prev; // 前の要素へのポインタ
}NODE_LINK;

//専用関数を用意
NODE_LINK* new_node(){
  NODE_LINK* node;
  node = (NODE_LINK*)calloc(1,sizeof(NODE_LINK*));

// 例外処理
  if(node == NULL){
    fprintf(stderr, "Error:Memory Allocation Failed.\n");
    exit(1);
  }

// メンバの初期化
  node->alph = 0;
  node->next = NULL;
  node->prev = NULL;

  return node;
}

// コマンド一覧を表示
void print_all_command(){
  printf("command\n");
  printf("0: end\n");
  printf("1: add node to linked list\n");
  printf("2: print all value of the list\n");
  //printf("3: print all command\n", );
}

int add_node(NODE_LINK *head,NODE_LINK *tail,char alp, int list_length,int position){
  NODE_LINK *target,*node;
  int i;

  node = new_node();
  node->alph = alp;

  if(head->next == NULL && tail->prev == NULL){
    head->next = node;
    tail->prev = node;
  }else{
    if(position >= 0){
      target = head;
      for(i=0;i<position;i++){
        target = target->next;
      }

      node->next = target->next;
      if(target->next == NULL){
        tail->prev = node;
      }else{
        target->next->prev = node;
      }
      target->next = node;
      if(target != head){
        node->prev = target;
      }
    }else if(position < 0){
      target = tail;
      for(i=-1;i>position;i--){
        target = target->prev;
      }

      node->prev = target->prev;
      if(target->prev == NULL){
        head->next = node;
      }else{
        target->prev->next = node;
      }

      target->next = node;
      if(target != tail){
        node->next = target;
      }
    }else{
    }
  }

  list_length++;

  return list_length;
}

int add_ui(NODE_LINK *head, NODE_LINK *tail,int list_length){
  char alp;
  char buf[10];
  int position;
  int len;

  printf("Input only one Charactor for value.\n");
  fgets(buf,10,stdin);
  alp = buf[0];

  while(1){
    printf("Input index number.(miuns is invert index)\n");
    fgets(buf,10,stdin);
    if(1 != sscanf(buf,"%d",&position)){
      printf("Invalid index\n");
      continue;
    }

    // 負の値が入力されたときにその絶対値がリストの長さより長いかどうかチェック
    if(abs(position) > list_length){
      printf("Warning: index is overrun.\n");
    }else{
      break;
    }
  }

  len = add_node(head,tail,alp,list_length,position);

  return len;
}

void print_nodes(NODE_LINK *head, NODE_LINK *tail){
  NODE_LINK *node;

  node = head->next;
  while(node!= NULL){
    printf("%c,",node->alph);
    node = node->next;
  }

  printf("\n");
}

int main(void){
  int command_number;
  char buf[10];
  int list_length = 0;

  // ノードを初期化
  NODE_LINK *head,*tail;
  head = new_node();
  tail = new_node();

  printf("Dual Linked List Test Program\n");



  // command_numberが0未満になるまで繰り返す
  while(1){

    // 「コマンドを入力」と表示
    printf("-------------------------------\n");
    printf("Input command number.\n");
    print_all_command();

    fgets(buf,10,stdin);
    if(1 != sscanf(buf,"%d",&command_number)){
      continue;
    }

    switch (command_number) {
      case 0:
      exit(0);
      break;

      case 1:
      list_length = add_ui(head,tail,list_length);
      break;

      case 2:
      print_nodes(head,tail);
      break;

      default:
      printf("Input correct number.\n");
    }
  }

  return 0;
}
