/* Ofront+ 1.0 -sC -88 */
#include "SYSTEM.oh"

typedef
  SET ecoBigSets_CHARSET[7];




export void ecoBigSets_Difference (SET *firstSet, INTEGER firstSet__len, SET *secondSet, INTEGER secondSet__len, SET *destSet, INTEGER destSet__len);
export void ecoBigSets_Empty (SET *set, INTEGER set__len);
export void ecoBigSets_Excl (SET *set, INTEGER set__len, INTEGER element);
export void ecoBigSets_ExclRange (SET *set, INTEGER set__len, INTEGER firstElement, INTEGER lastElement);
export BOOLEAN ecoBigSets_In (SET *set, INTEGER set__len, INTEGER element);
export void ecoBigSets_Incl (SET *set, INTEGER set__len, INTEGER element);
export void ecoBigSets_InclRange (SET *set, INTEGER set__len, INTEGER firstElement, INTEGER lastElement);
export void ecoBigSets_Intersection (SET *firstSet, INTEGER firstSet__len, SET *secondSet, INTEGER secondSet__len, SET *destSet, INTEGER destSet__len);
export BOOLEAN ecoBigSets_IsEmpty (SET *set, INTEGER set__len);
export void ecoBigSets_SymmetricDiff (SET *firstSet, INTEGER firstSet__len, SET *secondSet, INTEGER secondSet__len, SET *destSet, INTEGER destSet__len);
export void ecoBigSets_Union (SET *firstSet, INTEGER firstSet__len, SET *secondSet, INTEGER secondSet__len, SET *destSet, INTEGER destSet__len);


/*============================================================================*/

void ecoBigSets_Empty (SET *set, INTEGER set__len)
{
  INTEGER index;
  index = 0;
  while (index < set__len) {
    set[__X(index, set__len, (CHAR*)"ecoBigSets", 10773)] = 0x0;
    index += 1;
  }
}

/*----------------------------------------------------------------------------*/
BOOLEAN ecoBigSets_IsEmpty (SET *set, INTEGER set__len)
{
  INTEGER index;
  BOOLEAN empty;
  empty = 1;
  index = 0;
  while (empty && index < set__len) {
    empty = set[__X(index, set__len, (CHAR*)"ecoBigSets", 14111)] == 0x0;
    index += 1;
  }
  return empty;
}

/*----------------------------------------------------------------------------*/
BOOLEAN ecoBigSets_In (SET *set, INTEGER set__len, INTEGER element)
{
  INTEGER index, bit;
  index = __ASHR(element, 5, INTEGER);
  bit = __MASK(element, -32);
  return __IN(bit, set[__X(index, set__len, (CHAR*)"ecoBigSets", 17693)]);
}

/*----------------------------------------------------------------------------*/
void ecoBigSets_Incl (SET *set, INTEGER set__len, INTEGER element)
{
  INTEGER index, bit;
  index = __ASHR(element, 5, INTEGER);
  bit = __MASK(element, -32);
  set[__X(index, set__len, (CHAR*)"ecoBigSets", 20505)] |= __SETOF(bit);
}

/*----------------------------------------------------------------------------*/
void ecoBigSets_Excl (SET *set, INTEGER set__len, INTEGER element)
{
  INTEGER index, bit;
  index = __ASHR(element, 5, INTEGER);
  bit = __MASK(element, -32);
  set[__X(index, set__len, (CHAR*)"ecoBigSets", 23321)] &= ~__SETOF(bit);
}

/*----------------------------------------------------------------------------*/
void ecoBigSets_InclRange (SET *set, INTEGER set__len, INTEGER firstElement, INTEGER lastElement)
{
  INTEGER index, bit, count;
  index = __ASHR(firstElement, 5, INTEGER);
  bit = __MASK(firstElement, -32);
  count = (lastElement - firstElement) + 1;
  while (count > 0) {
    set[__X(index, set__len, (CHAR*)"ecoBigSets", 26907)] |= __SETOF(bit);
    bit += 1;
    if (bit == 32) {
      bit = 0;
      index += 1;
    }
    count -= 1;
  }
}

/*----------------------------------------------------------------------------*/
void ecoBigSets_ExclRange (SET *set, INTEGER set__len, INTEGER firstElement, INTEGER lastElement)
{
  INTEGER index, bit, count;
  index = __ASHR(firstElement, 5, INTEGER);
  bit = __MASK(firstElement, -32);
  count = (lastElement - firstElement) + 1;
  while (count > 0) {
    set[__X(index, set__len, (CHAR*)"ecoBigSets", 32283)] &= ~__SETOF(bit);
    bit += 1;
    if (bit == 32) {
      bit = 0;
      index += 1;
    }
    count -= 1;
  }
}

/*----------------------------------------------------------------------------*/
void ecoBigSets_Union (SET *firstSet, INTEGER firstSet__len, SET *secondSet, INTEGER secondSet__len, SET *destSet, INTEGER destSet__len)
{
  INTEGER index, maxIndex;
  index = 0;
  maxIndex = (SHORTINT)firstSet__len;
  while (index < maxIndex) {
    destSet[__X(index, destSet__len, (CHAR*)"ecoBigSets", 36923)] = firstSet[__X(index, firstSet__len, (CHAR*)"ecoBigSets", 36923)] | secondSet[__X(index, secondSet__len, (CHAR*)"ecoBigSets", 36923)];
    index += 1;
  }
}

/*----------------------------------------------------------------------------*/
void ecoBigSets_Difference (SET *firstSet, INTEGER firstSet__len, SET *secondSet, INTEGER secondSet__len, SET *destSet, INTEGER destSet__len)
{
  INTEGER index, maxIndex;
  index = 0;
  maxIndex = (SHORTINT)firstSet__len;
  while (index < maxIndex) {
    destSet[__X(index, destSet__len, (CHAR*)"ecoBigSets", 40251)] = firstSet[__X(index, firstSet__len, (CHAR*)"ecoBigSets", 40251)] & ~secondSet[__X(index, secondSet__len, (CHAR*)"ecoBigSets", 40251)];
    index += 1;
  }
}

/*----------------------------------------------------------------------------*/
void ecoBigSets_Intersection (SET *firstSet, INTEGER firstSet__len, SET *secondSet, INTEGER secondSet__len, SET *destSet, INTEGER destSet__len)
{
  INTEGER index, maxIndex;
  index = 0;
  maxIndex = (SHORTINT)firstSet__len;
  while (index < maxIndex) {
    destSet[__X(index, destSet__len, (CHAR*)"ecoBigSets", 43579)] = firstSet[__X(index, firstSet__len, (CHAR*)"ecoBigSets", 43579)] & secondSet[__X(index, secondSet__len, (CHAR*)"ecoBigSets", 43579)];
    index += 1;
  }
}

/*----------------------------------------------------------------------------*/
void ecoBigSets_SymmetricDiff (SET *firstSet, INTEGER firstSet__len, SET *secondSet, INTEGER secondSet__len, SET *destSet, INTEGER destSet__len)
{
  INTEGER index, maxIndex;
  index = 0;
  maxIndex = (SHORTINT)firstSet__len;
  while (index < maxIndex) {
    destSet[__X(index, destSet__len, (CHAR*)"ecoBigSets", 46907)] = firstSet[__X(index, firstSet__len, (CHAR*)"ecoBigSets", 46907)] ^ secondSet[__X(index, secondSet__len, (CHAR*)"ecoBigSets", 46907)];
    index += 1;
  }
}

/*----------------------------------------------------------------------------*/

export void *ecoBigSets__init (void)
{
  __DEFMOD;
  __REGMOD("ecoBigSets", 0);
/* BEGIN */
  __ENDMOD;
}
