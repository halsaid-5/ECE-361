#include "store.h"
#include <stdlib.h>
#include <math.h>
typedef struct node {int key;record_t record;struct node *left,*right,*same;} node_t;
struct store {node_t *root;size_t count;};
/* Rounding to nearest 0.5: 21.2 -> 21.0; 21.4 -> 21.5.
   This follows nearest-step rounding, not truncation. */
static int key_of(float t){return (int)lroundf(t*2.0f);}
int record_compare(const record_t *a,const record_t *b){int x=key_of(a->reading.temp_c),y=key_of(b->reading.temp_c);return (x>y)-(x<y);}
store_t *store_create(void){return calloc(1,sizeof(store_t));}
int store_insert(store_t *s,record_t record){if(!s)return -1;int key=key_of(record.reading.temp_c);node_t **link=&s->root;while(*link){if(key<(*link)->key)link=&(*link)->left;else if(key>(*link)->key)link=&(*link)->right;else {link=&(*link)->same;while(*link)link=&(*link)->same;break;}}node_t *n=calloc(1,sizeof(*n));if(!n)return -1;n->key=key;n->record=record;*link=n;s->count++;return 0;}
const record_t *store_find(const store_t *s,float temp){if(!s)return NULL;int key=key_of(temp);node_t *n=s->root;while(n){if(key==n->key)return &n->record;n=key<n->key?n->left:n->right;}return NULL;}
static void walk(node_t *n,record_visit_fn fn,void *ctx){if(!n)return;walk(n->left,fn,ctx);for(node_t *p=n;p;p=p->same)fn(&p->record,ctx);walk(n->right,fn,ctx);}
void store_walk(const store_t *s,record_visit_fn fn,void *ctx){if(s&&fn)walk(s->root,fn,ctx);}
size_t store_count(const store_t *s){return s?s->count:0;}
static size_t height(node_t *n){if(!n)return 0;size_t a=height(n->left),b=height(n->right);return 1+(a>b?a:b);}
size_t store_height(const store_t *s){return s?height(s->root):0;}
static void free_nodes(node_t *n){if(!n)return;free_nodes(n->left);free_nodes(n->right);node_t *p=n;while(p){node_t *next=p->same;free(p);p=next;}}
void store_destroy(store_t *s){if(s){free_nodes(s->root);free(s);}}
