#ifndef AAPCS_VFP
# if __arm__
#  define AAPCS_VFP __attribute__((pcs("aapcs-vfp")))
# else
#  define AAPCS_VFP
# endif
#endif