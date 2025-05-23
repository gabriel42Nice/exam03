
#include <unistd.h>
#include <stdarg.h>

static void putstr(char *s, int *c) {
    if (!s) s = "(null)";
    while (*s) *c += write(1, s++, 1);
}

static void putnbr(int n, int *c) {
    if (n == -2147483648) return putstr("-2147483648", c);
    if (n < 0) *c += write(1, "-", 1), n = -n;
    if (n > 9) putnbr(n / 10, c);
    *c += write(1, &((char[]){"0"[0] + n % 10}), 1);
}

static void puthex(unsigned int n, int *c) {
    char *h = "0123456789abcdef";
    if (n >= 16) puthex(n / 16, c);
    *c += write(1, &h[n % 16], 1);
}

int ft_printf(const char *f, ...) {
    va_list a; int c = 0;
    va_start(a, f);
    while (*f) {
        if (*f == '%' && *++f)
            *f == 's' ? putstr(va_arg(a, char *), &c) :
            *f == 'd' ? putnbr(va_arg(a, int), &c) :
            *f == 'x' ? puthex(va_arg(a, unsigned int), &c) :
            (c += write(1, f, 1));
        else
            c += write(1, f, 1);
        f++;
    }
    va_end(a);
    return c;
}