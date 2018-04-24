#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENTS 350000
#define MAX_VALUE 15000

extern void start_timer(unsigned int *);
extern unsigned get_elapsed_time(unsigned int *);
extern unsigned int start_tm;

void upheap(int *, int);
void downheap(int *, int, int);

void insert(int *, int, int);
void replace(int *, int, int);
int delete_root(int *, int *);

void construct_1(int *, int);
void construct_2(int *, int);
void heapsort(int *, int);

int main(int argc, char *argv[]) {
  int i, t;
  int operation, value, status; // For heap maintainance

  /*
    heap構築時、自分の好きなデータ数、値で検証したい場合はここを変える。
    (実行時は、引数に0以下の値を与える)
    nの値がヒープを構築するデータ数である。(配列の1～n番目を利用する)
  */
  int n = 7, A[MAX_ELEMENTS] = {-1, 5, 2, 7, 13, 1, 6, 8};
  /*
    注意: ヒープ構造は、n番目と2n, 2n+1番目の要素との順序関係が規定されたもので
    あるため、C系の言語の「配列の添え字は0から始まる」ルールの通りにヒープの先
    頭の要素を0番目(n=0)とするとプログラムがややこしくなってしまう(コードの解
    釈が無駄に難解になる)。要素1つ分のメモリが無駄にはなるが、「それに比べて、
    ヒープ構造を利用することで得られる恩恵の方が大きい」と考えて添え字「1」から
    データが始まるものとする(A[0]=-1は便宜上、埋めただけでアルゴリズムとしての
    意味はない)。
  */

  if (argc <= 1) { // heap maintainance
    // ヒープ維持操作(メンテナンス、前提として既にヒープ構造ができあがっている)
    n = 0;

    while (1) {
      printf("*** Initial Condition *** \n");
      for (i = 1; i <= n; i++) {
        printf(" A[%5d] = %5d \n", i, A[i]);
      }

      printf("Give a command.   format : [opeartion]  [value]\n ->");
      status = scanf("%d %d", &operation, &value);
      if (status != 2) {
        printf("Execution was halted. (Illegal format)\n");
        exit(1);
      }

      // ヒープ構築維持本体(関数呼び出し)はここ
      switch (operation) {
      case 0:
        insert(A, value, ++n); // 末尾に値挿入
        break;

      case 1:
        if (n < 1) {
          printf("Error: Heap is empty. ( no value to replace)\n");
          break;
        }
        replace(A, value, n); // 根の値置き換え
        break;

      case 2:
        if (n < 1) {
          printf("Error: Heap is empty. ( no value to delete)\n");
          break;
        }
        status = delete_root(A, &n); // 根の値削除
        printf("%d was removed from Binary tree due to heap opeartion.\n",
               status);
        break;

      case 3:
        if (n < 1) {
          printf("Error: Heap is empty. ( no value to delete)\n");
          break;
        }
        heapsort(A, n);         // ヒープソート
        break;

      default:
        printf("Error: Opeartion was not defined.\n");
        break;
      }
      // 維持本体ここまで

      printf("*** After Operation *** \n");
      for (i = 1; i <= n; i++) {
        printf(" A[%5d] = %5d \n", i, A[i]);
      }

      printf("\n");
    }

  } else { // heap construction

    /* ヒープ構築の初期データ(でたらめ) */
    value = atoi(argv[1]);
    if (value >= MAX_ELEMENTS) {
      printf("Error: Number of elements are exceeded the limit.\n");
      exit(1);
    }
    if (value > 0) {
      n = value;
      // generate n random integers.
      srand(n);
      for (i = 1; i <= n; i++) {
        t = rand();
        if (t < MAX_VALUE)
          A[i] = t;
        else
          A[i] = t % MAX_VALUE;
#ifdef DEBUG
        printf(" A[%5d] = %5d \n", i, A[i]);
#endif
      }
    } else {
      printf("*** Initial Condition *** \n");
      for (i = 1; i <= n; i++) {
        printf(" A[%5d] = %5d \n", i, A[i]);
      }
    }

    // ヒープ構築操作本体(関数呼び出し)はここ
    /* 時間計測するときはここから */
    start_timer(&start_tm);

    /* construct_1(A, n); // upheapで構築 */
    /* construct_2(A, n); // downheapで構築 */
    heapsort(A,n);         // ヒープソート

    /* ここまで時間計測 */
    printf("%5d : elapsed time is %10.3f milliseconds. \n", n,
    get_elapsed_time(&start_tm)*1.0e-3);
    // 操作本体ここまで

    if (value > 0) {
#ifdef DEBUG
      printf("*** After Operation *** \n");
      for (i = 1; i <= n; i++) {
        printf(" A[%5d] = %5d \n", i, A[i]);
      }
#endif
    } else {
      printf("*** After Operation *** \n");
      for (i = 1; i <= n; i++) {
        printf(" A[%5d] = %5d \n", i, A[i]);
      }
    }
  }

  return 0;
}

/*
  !!ここがヒープ構成のコアパーツ!!
  「ある１組の親子間の大小関係が維持されているかをチェック、関係が壊れているな
  ら修復する」
  どこをどう変えると、maximum heap, minimum heapになるかを見出す事
*/

// upheapによってヒープチェック・メンテナンスを行う関数
void upheap(int *A, int k) {
  int v; // 一時退避用の変数。ヒープチェックの際にチェックする値を一時的に退避
         // させること

  v = A[k];
  while (k > 1 && v < A[k / 2]) {
    A[k] = A[k / 2];
    k = k / 2;
  }
  A[k] = v;
}

// downheapによってヒープチェック・メンテナンスを行う関数
void downheap(int *A, int k, int n) {
  int j;
  int v; // 一時退避用の変数。使い方はupheapと同様に

  v = A[k];
  while (k <= n / 2) {
    j = k*2; // 子ノードへ移る

    if (j < n && A[j] > A[j+1])
      j++; // ２つの子ノードのうち、どちらと比較すればいいか
    if (v < A[j])
      break;

    A[k] = A[j];
    k = j;
  }
  A[k] = v;
}
/*
  コアパーツここまで。抽象的に見れば、ここだけ理解すれば全部できたのと同値。
  ここをとにかく解読して理解すること!
  これより以下は、これらの具体的な利用方法。
*/

// これより以下、ヒープ操作の具体的な関数
// いずれも upheap、downheapのいずれかを中で利用する

/* 既に完成しているヒープに対するメンテナンス操作 */

// 挿入(引数: ヒープの配列、新規挿入する値、挿入後のデータ数)
void insert(int *A, int v, int n) {
  A[n] = v;
  upheap(A, n);
}

// 根の値の置き換え(引数: ヒープの配列、置き換える値、データ数)
void replace(int *A, int v, int n) {
  A[1] = v;
  downheap(A, 1, n);
}

// 根の値の削除(引数: ヒープの配列、削除前のデータ数を保持する「アドレス」)
// アドレス渡し化...ヒープ操作の全ての機能をハンドアウト通りに実装したときに、
// 起こりうる不整合を防ぐため
int delete_root(int *A, int *n) {
  int v = A[1];

  A[1] = A[*n];
  (*n)--;
  downheap(A, 1, *n);

  return v; // 戻り値: ヒープから削除された値
}

// ヒープが完成していない(完成しているかどうか保証されない木構造)に対するヒープ
// 構築操作
void construct_1(int *A, int n) { // upheapで構築
  int i;
  for (i = 0; i <= n; i++) {
    upheap(A, i);
  }
}

void construct_2(int *A, int n) { // downheapで構築
  int i;
  for (i = n/2; i >= 1; i--) {
    downheap(A, i, n);
  }
}

// ヒープソート(ヒープの構造を利用したソート、まだソートされていない部分は
// ヒープ構造が維持されている)
void heapsort(int *A, int n) {
  int i, tmp;
  construct_2(A, n); // 先にヒープを作っておいて…

  for (i = n; i >= 2; i--) {
    tmp = A[1];
    A[1] = A[i];
    A[i] = tmp;

    downheap(A, 1, i-1);
    /* tmp = i-1; */
    /* A[i] = delete_root(A, &tmp); */
  }
}
