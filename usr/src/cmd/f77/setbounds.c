#include "defs"
/*
 * setbounds(name, ndim, dims)
 *
 * Reconstructed placeholder.  The V7 f77 pass-1 grammar (gram.dcl) calls
 * setbounds() when processing DIMENSION declarations, but the file that
 * defined it was lost from the flattened source tree.  It would have
 * recorded the declared dimension bounds on the nameblock entry.  This
 * no-op keeps f77pass1 linkable; bounds checking is degraded.
 */
setbounds(np, nd, dims)
struct nameblock *np;
int nd;
ftnint dims[];
{
	return 0;
}
