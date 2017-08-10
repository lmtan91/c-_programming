
all: $(ALL_TARGETS)

clean: $(CLEAN_DEPS)
	rm -f $(CLEAN_OBJS) $(EXTRA_CLEAN) .depend

realclean real-clean: $(REAL_CLEAN_DEPS)
	rm -rf $(REALCLEAN_OBJS) $(EXTRA_CLEAN) $(ALL_OBJ_DIRS) .depend

distclean: $(DISTCLEAN_DEPS)
	rm -rf $(DISTCLEAN_OBJS) $(EXTRA_CLEAN) $(ALL_OBJ_DIRS) .depend

real-clean-subdirs: realclean

dist-clean-subdirs: distclean

apply_patches:
	@set -e ; \
	pfiles="$(wildcard $(TOPDIR)/patches/$(JH_PROJECT_NAME)/*.patch)" ; \
	if [ -n "$$pfiles" -a -x $(TOPDIR)/patches/patch-kernel-jethead.sh ]; then \
		$(TOPDIR)/patches/patch-kernel-jethead.sh $(TOPDIR) $(TOPDIR)/patches/$(JH_PROJECT_NAME) \*.patch ; \
	fi

unapply_patches:
	@set -e ; \
	pfiles="$(wildcard $(TOPDIR)/patches/$(JH_PROJECT_NAME)/*.patch)" ; \
	if [ -n "$$pfiles" -a -x $(TOPDIR)/patches/patch-kernel-jethead.sh ]; then \
		$(TOPDIR)/patches/patch-kernel-jethead.sh -R $(TOPDIR) $(TOPDIR)/patches/$(JH_PROJECT_NAME) \*.patch ; \
	fi

.DEFAULT:

.SUFFIXES: ;

.PHONY: all clean realclean real-clean distclean FORCE

