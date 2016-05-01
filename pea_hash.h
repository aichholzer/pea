
typedef  unsigned long  int  ub4;   /* unsigned 4-byte quantities */
typedef  unsigned       char ub1;

#define hashsize(n) ((ub4)1<<(n))
#define hashmask(n) (hashsize(n)-1)

ub4 hash(
  register ub1 *k,        /* the key */
  register ub4  length,   /* the length of the key */
  register ub4  initval    /* the previous hash, or an arbitrary value */
);

ub4 hash2(
  register ub4 *k,        /* the key */
  register ub4  length,   /* the length of the key, in ub4s */
  register ub4  initval   /* the previous hash, or an arbitrary value */
);
