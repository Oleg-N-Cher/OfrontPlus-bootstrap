/* Ofront+ 1.0 -s2 -48 */
#include "SYSTEM.oh"
#include "arStringList.oh"
#include "arStrings.oh"

typedef
  struct arStringAssoc_Assoc__rec *arStringAssoc_Assoc;

typedef
  struct arStringAssoc_Assoc__rec {
    arStrings_StringPtr key, value;
    arStringAssoc_Assoc next;
  } arStringAssoc_Assoc__rec;



export void **arStringAssoc_Assoc__rec__typ;

export arStringAssoc_Assoc arStringAssoc_Find (arStringAssoc_Assoc assoc, CHAR *key, INTEGER key__len);
export arStringAssoc_Assoc arStringAssoc_FindValue (arStringAssoc_Assoc assoc, CHAR *key, INTEGER key__len);
export arStrings_StringPtr arStringAssoc_Get (arStringAssoc_Assoc assoc, CHAR *key, INTEGER key__len);
export arStringList_List arStringAssoc_GetAll (arStringAssoc_Assoc assoc, CHAR *key, INTEGER key__len);
export arStrings_StringPtr arStringAssoc_GetKey (arStringAssoc_Assoc assoc, CHAR *value, INTEGER value__len);
export void arStringAssoc_Set (arStringAssoc_Assoc *assoc, CHAR *key, INTEGER key__len, CHAR *value, INTEGER value__len);
export void arStringAssoc_Set0 (arStringAssoc_Assoc *assoc, CHAR *key, INTEGER key__len, CHAR *value, INTEGER value__len);


/*============================================================================*/

arStringAssoc_Assoc arStringAssoc_Find (arStringAssoc_Assoc assoc, CHAR *key, INTEGER key__len)
{
  arStrings_StringPtr _ptr__2 = NIL;
  __DUP(key, key__len);
  while (assoc != NIL) {
    if (_ptr__2 = assoc->key, 
      arStrings_Equal((void*)key, key__len, _ptr__2->data, _ptr__2->len[0])) {
      return assoc;
    }
    assoc = assoc->next;
  }
  return NIL;
}

/*----------------------------------------------------------------------------*/
arStringAssoc_Assoc arStringAssoc_FindValue (arStringAssoc_Assoc assoc, CHAR *key, INTEGER key__len)
{
  arStrings_StringPtr _ptr__4 = NIL;
  __DUP(key, key__len);
  while (assoc != NIL) {
    if (_ptr__4 = assoc->value, 
      arStrings_Equal((void*)key, key__len, _ptr__4->data, _ptr__4->len[0])) {
      return assoc;
    }
    assoc = assoc->next;
  }
  return NIL;
}

/*----------------------------------------------------------------------------*/
void arStringAssoc_Set0 (arStringAssoc_Assoc *assoc, CHAR *key, INTEGER key__len, CHAR *value, INTEGER value__len)
{
  arStringAssoc_Assoc binding = NIL;
  __DUP(key, key__len);
  __DUP(value, value__len);
  __NEW(binding, arStringAssoc_Assoc__rec);
  binding->key = arStringList_Copy(key, key__len);
  binding->value = arStringList_Copy(value, value__len);
  binding->next = *assoc;
  *assoc = binding;
}

/*----------------------------------------------------------------------------*/
void arStringAssoc_Set (arStringAssoc_Assoc *assoc, CHAR *key, INTEGER key__len, CHAR *value, INTEGER value__len)
{
  arStringAssoc_Assoc binding = NIL;
  __DUP(key, key__len);
  __DUP(value, value__len);
  binding = arStringAssoc_Find(*assoc, key, key__len);
  if (binding != NIL) {
    binding->value = arStringList_Copy(value, value__len);
  } else {
    arStringAssoc_Set0(assoc, key, key__len, value, value__len);
  }
}

/*----------------------------------------------------------------------------*/
arStrings_StringPtr arStringAssoc_Get (arStringAssoc_Assoc assoc, CHAR *key, INTEGER key__len)
{
  arStringAssoc_Assoc binding = NIL;
  __DUP(key, key__len);
  binding = arStringAssoc_Find(assoc, key, key__len);
  if (binding != NIL) {
    return binding->value;
  }
  return NIL;
}

/*----------------------------------------------------------------------------*/
arStrings_StringPtr arStringAssoc_GetKey (arStringAssoc_Assoc assoc, CHAR *value, INTEGER value__len)
{
  arStringAssoc_Assoc binding = NIL;
  __DUP(value, value__len);
  binding = arStringAssoc_FindValue(assoc, value, value__len);
  if (binding != NIL) {
    return binding->key;
  }
  return NIL;
}

/*----------------------------------------------------------------------------*/
arStringList_List arStringAssoc_GetAll (arStringAssoc_Assoc assoc, CHAR *key, INTEGER key__len)
{
  arStringList_List result = NIL;
  arStrings_StringPtr _ptr__7 = NIL;
  __DUP(key, key__len);
  result = NIL;
  while (assoc != NIL) {
    if (_ptr__7 = assoc->key, 
      arStrings_Equal((void*)key, key__len, _ptr__7->data, _ptr__7->len[0])) {
      arStringList_Add(&result, assoc->value);
    }
    assoc = assoc->next;
  }
  return result;
}

/*----------------------------------------------------------------------------*/
__TDESC(arStringAssoc_Assoc__rec__desc, 2, 3) = {__TDFLDS("Assoc__rec", 12), {0, 4, 8, -16}};

export void *arStringAssoc__init (void)
{
  __DEFMOD;
  __IMPORT(arStrings__init);
  __IMPORT(arStringList__init);
  __REGMOD("arStringAssoc", 0);
  __INITYP(arStringAssoc_Assoc__rec, arStringAssoc_Assoc__rec, 0);
/* BEGIN */
  __ENDMOD;
}
