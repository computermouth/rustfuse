#include <stdio.h>
#include <math.h>
#include <confuse.h>

int double_input(int input) {
    cfg_t *cfg;

    long int zero = 0;

		cfg_opt_t opts[] = {
			CFG_SIMPLE_INT("video_mode", &zero),
			CFG_END()
		};

    cfg = cfg_init(opts, 0);
    
    cfg_free(cfg);

    printf("howdy\n");
    return pow(input * 2, 2);
}
