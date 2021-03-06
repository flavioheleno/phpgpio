dnl config.m4 for extension phpgpio

PHP_ARG_WITH(
  [phpgpio],
  [for phpgpio support],
  [AS_HELP_STRING(
    [--with-phpgpio],
    [Include phpgpio support]
  )]
)

PHP_ARG_WITH(
  [libgpiod-dir],
  [for system library directory],
  [AS_HELP_STRING(
    [--with-libgpiod-dir[=DIR]],
    [Set the path to libgpiod install prefix.]
  )],
  [lib],
  [no]
)

if test "$PHP_PHPGPIO" != "no"; then
  PKG_CHECK_MODULES([LIBGPIOD], [libgpiod >= 1.6.3])
  PHP_EVAL_INCLINE($LIBGPIOD_CFLAGS)
  PHP_EVAL_LIBLINE($LIBGPIOD_LIBS, PHPGPIO_SHARED_LIBADD)
  PHP_SUBST(PHPGPIO_SHARED_LIBADD)

  AC_DEFINE(HAVE_PHPGPIO, 1, [ Have phpgpio support ])

  PHP_NEW_EXTENSION(phpgpio, phpgpio.c src/line.c src/bulk.c src/exception.c src/chip.c, $ext_shared)
fi
