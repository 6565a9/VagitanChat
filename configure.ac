AC_INIT([VagitanChat], [0.1], [dalbaeb228@mail.i2p])
AC_PROG_CC([g++])
AC_PROG_CXX([g++])
AC_CONFIG_FILES([
	Makefile
	src/Makefile
])
#AC_SEARCH_LIBS([lcrypto])
#AC_CHECK_LIBS([lcrypto])
AC_CONFIG_SRCDIR([src/vagitanchat.cpp])
PKG_CHECK_MODULES([libssl], [libssl], [pthread], [libpthread])
AM_INIT_AUTOMAKE
AC_OUTPUT



