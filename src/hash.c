/*
 * Copyright (c) 2009 LAAS/CNRS
 * All rights reserved.
 *
 * Redistribution  and  use  in  source  and binary  forms,  with  or  without
 * modification, are permitted provided that the following conditions are met:
 *
 *   1. Redistributions of  source  code must retain the  above copyright
 *      notice and this list of conditions.
 *   2. Redistributions in binary form must reproduce the above copyright
 *      notice and  this list of  conditions in the  documentation and/or
 *      other materials provided with the distribution.
 *
 * THE SOFTWARE  IS PROVIDED "AS IS"  AND THE AUTHOR  DISCLAIMS ALL WARRANTIES
 * WITH  REGARD   TO  THIS  SOFTWARE  INCLUDING  ALL   IMPLIED  WARRANTIES  OF
 * MERCHANTABILITY AND  FITNESS.  IN NO EVENT  SHALL THE AUTHOR  BE LIABLE FOR
 * ANY  SPECIAL, DIRECT,  INDIRECT, OR  CONSEQUENTIAL DAMAGES  OR  ANY DAMAGES
 * WHATSOEVER  RESULTING FROM  LOSS OF  USE, DATA  OR PROFITS,  WHETHER  IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR  OTHER TORTIOUS ACTION, ARISING OUT OF OR
 * IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 *                                           Anthony Mallet on Sun Dec 20 2009
 */
#include "acgenom.h"

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <err.h>

#include "genom.h"


/* --- local data ---------------------------------------------------------- */

/** hash table entries */
struct hentry_s {
  const char *key;
  void *value;
  void (*release)(void *);

  struct hentry_s *next;
};

/** hash table */
struct hash_s {
  const char *name;	/** a name, for verbose messages */
  unsigned int n;	/** number of entries */

  unsigned int buckets;	/** number of buckets */
  hentry_s *bucket;	/** buckets, array of entries */
};

/** expand hash table beyond this number of entries per bucket on average */
#define hash_maxload	(3.)


static int		hash_expand(hash_s h);
static unsigned long	hstring(const char *key);


/* --- hash_create --------------------------------------------------------- */

/** Create a hash table with the number of expected entries
 */

hash_s
hash_create(const char *name, int entries)
{
  hash_s h;

  h = malloc(sizeof(*h));
  if (!h) return NULL;

  h->name = name;
  h->n = 0;
  h->buckets = entries/hash_maxload + 1;
  if (h->buckets < 1) h->buckets = 1;
  if (h->buckets > 1024) h->buckets = 1024;

  h->bucket = calloc(h->buckets, sizeof(*h->bucket));
  if (!h->bucket) { free(h); return NULL; }

  return h;
}


/* --- hash_destroy -------------------------------------------------------- */

/** Delete a hash table and its entries
 */

void
hash_destroy(hash_s h)
{
  int i;
  hentry_s e;

  if (!h) return;

  for(i=0; i<h->buckets; i++)
    while(h->bucket[i]) {
      e = h->bucket[i];
      h->bucket[i] = e->next;

      free((char *)e->key);
      if (e->release) e->release(e->value);
      free(e);
    }

  free(h->bucket);
  free(h);
}


/* --- hash_insert --------------------------------------------------------- */

/** Create a new hash table entry
 */

int
hash_insert(hash_s h, const char *key, void *value, void (*release)(void *))
{
  unsigned long index;
  hentry_s e;

  if (!h || !key) return EINVAL;

  index = hstring(key) % h->buckets;
  for(e = h->bucket[index]; e; e = e->next)
    if (!strcmp(e->key, key)) {
      xwarnx("attempt to reinsert existing `%s' in %s hash", key, h->name);
      return EEXIST;
    }

  e = malloc(sizeof(*e));
  if (!e) return ENOMEM;
  e->key = strdup(key);
  e->value = value;
  e->release = release;
  if (!e->key) {
    free(e);
    warnx("memory exhausted, cannot insert `%s' in %s hash", key, h->name);
    return ENOMEM;
  }

  if (h->n > h->buckets*hash_maxload) {
    hash_expand(h);
    index = hstring(key) % h->buckets;
  }

  e->next = h->bucket[index];
  h->bucket[index] = e;
  h->n++;

  return 0;
}


/* --- hash_remove --------------------------------------------------------- */

/** Remove an entry from hash table
 */

int
hash_remove(hash_s h, const char *key)
{
  unsigned long index;
  hentry_s e, n;

  if (!h || !key) return EINVAL;

  index = hstring(key) % h->buckets;
  if (!strcmp(h->bucket[index]->key, key)) {
    e = h->bucket[index];
    h->bucket[index] = e->next;
    free((char *)e->key);
    if (e->release) e->release(e->value);
    free(e);
    h->n--;
    return 0;
  } else
    for(n = h->bucket[index]; n->next; n = n->next)
      if (!strcmp(n->next->key, key)) {
	e = n->next;
	n->next = e->next;
	free((char *)e->key);
	if (e->release) e->release(e->value);
	free(e);
	h->n--;
	return 0;
      }

  return ENOENT;
}


/* --- hash_find ----------------------------------------------------------- */

/** Return an entry in hash table
 */

void *
hash_find(hash_s h, const char *key)
{
  unsigned long index;
  hentry_s e;

  if (!h || !key) return NULL;

  index = hstring(key) % h->buckets;
  for(e = h->bucket[index]; e; e = e->next)
    if (!strcmp(e->key, key))
      return e->value;

  return NULL;
}


/* --- hash_pstat ---------------------------------------------------------- */

/** Print statistics regarding the number of entries per bucket
 */

void
hash_pstat(hash_s h)
{
#define hslots (11)
  int count[hslots] = { 0 };
  hentry_s e;
  int i, c;

  /* histogram of bucket usage */
  for(i=0; i<h->buckets; i++) {
    for(c = 0, e = h->bucket[i]; e; c++, e = e->next) /* empty body */;
    count[(c>=hslots)?hslots-1:c]++;
  }

  /* output info */
  warnx("statistics for %s hash", h->name);
  warnx(" %d entries in total, %d buckets (%d empty)",
	h->n, h->buckets, count[0]);
  for(i=1; i<hslots-1; i++)
    warnx(" buckets with %d entries: %d", i, count[i]);
  warnx(" buckets with %d entries or more: %d", hslots-1, count[hslots-1]);
}


/* --- hash_expand --------------------------------------------------------- */

/** Rebuild a bigger hash table
 */

static int
hash_expand(hash_s h)
{
  hentry_s *oldb = h->bucket;
  unsigned int oldn = h->buckets;
  unsigned int n = h->buckets * 2.7;
  unsigned int index;
  hentry_s p, e;
  int i;

  h->bucket = calloc(n, sizeof(*h->bucket));
  if (!h->bucket) { h->bucket = oldb; return ENOMEM; }
  h->buckets = n;

  for(i=0; i<oldn; i++)
    for(p = oldb[i]; p;) {
      e = p;
      p = p->next;

      index = hstring(e->key) % h->buckets;
      e->next = h->bucket[index];
      h->bucket[index] = e;
    }

  free(oldb);
  xwarnx("expanded hash %s with %d entries to %d buckets",
	 h->name, h->n, h->buckets);
  return 0;
}


/* --- hstring ------------------------------------------------------------- */

/** A supposedly good hash function for strings.
 * Ref. http://fr.wikipedia.org/wiki/Table_de_hachage
 */
static unsigned long
hstring(const char *key)
{
  unsigned long hash = 5381;
  if (!key) return 0;

  while(*key) {
    hash = ((hash << 5) + hash) + (unsigned char)*(key++);
  }
  return hash;
}
