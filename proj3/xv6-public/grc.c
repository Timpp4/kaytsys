#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "tieto.h"


int
main(int argc, char *argv[])
{
  if (argc > 1) {
	if (argc == 3) {
 		nollaa();
		printf(1, "readcount nollattu!\n");
	} else {
		printf(1, "Nollataksesi laskurin, argc:n oltava 3\n");
		printf(1, "esim: grc a a\n");
	}
  } else {
	getreadcount();
  }
  exit();
}
