/*
 * V7 formatted output for the x86_64 port.
 * The original doprnt.s/fltpr.s used the PDP-11 calling convention,
 * which cannot express C varargs on the System V ABI.
 */

#include <stdio.h>

typedef __builtin_va_list va_list;
#define va_start(ap, last)	__builtin_va_start(ap, last)
#define va_arg(ap, type)	__builtin_va_arg(ap, type)
#define va_end(ap)		__builtin_va_end(ap)

extern int strlen(char *);
extern char *strcpy(char *, char *);

static int
fmt_uint(char *buf, unsigned long v, int base, int upper)
{
	char digits[] = "0123456789abcdef";
	char DIGITS[] = "0123456789ABCDEF";
	char tmp[80];
	int n = 0, i;

	if (v == 0) {
		buf[0] = '0';
		buf[1] = 0;
		return 1;
	}
	while (v) {
		tmp[n++] = upper ? DIGITS[v % base] : digits[v % base];
		v /= base;
	}
	for (i = 0; i < n; i++)
		buf[i] = tmp[n - 1 - i];
	buf[n] = 0;
	return n;
}

static int
fmt_float(char *buf, double value, int prec, int style)
{
	char tmp[200];
	char *p = tmp;
	int neg = 0, exp = 0, i, n;
	double v = value;

	if (prec < 0)
		prec = 6;
	if (prec > 17)
		prec = 17;
	if (v != v) {
		strcpy(buf, "nan");
		return 3;
	}
	if (v < 0) {
		neg = 1;
		v = -v;
	}
	if (v > 1.0e300) {
		strcpy(buf, "inf");
		return 3;
	}
	if (style == 'e' || style == 'E' || style == 'g' || style == 'G') {
		if (v != 0.0) {
			while (v >= 10.0) { v /= 10.0; exp++; }
			while (v < 1.0) { v *= 10.0; exp--; }
		}
	}
	if (neg)
		*p++ = '-';
	n = (int)v;
	p += fmt_uint(p, (unsigned long)n, 10, 0);
	if (prec > 0) {
		*p++ = '.';
		v -= (double)n;
		for (i = 0; i < prec; i++) {
			v *= 10.0;
			n = (int)v;
			v -= (double)n;
			*p++ = '0' + n;
		}
	}
	if (style == 'e' || style == 'E') {
		*p++ = style;
		if (exp < 0) { *p++ = '-'; exp = -exp; }
		else *p++ = '+';
		if (exp < 10) *p++ = '0';
		p += fmt_uint(p, (unsigned long)exp, 10, 0);
	}
	*p = 0;
	n = p - tmp;
	for (i = 0; i < n; i++)
		buf[i] = tmp[i];
	buf[i] = 0;
	return n;
}

static int
emit(FILE *fp, char *s, int len, int width, int left, int zero)
{
	int i, padn = width > len ? width - len : 0;

	if (!left && zero && len > 0 && (s[0] == '-' || s[0] == '+')) {
		putc(s[0], fp);
		s++;
		len--;
	}
	if (!left)
		for (i = 0; i < padn; i++)
			putc(zero ? '0' : ' ', fp);
	for (i = 0; i < len; i++)
		putc(s[i], fp);
	if (left)
		for (i = 0; i < padn; i++)
			putc(' ', fp);
	return len + padn;
}

static int
vformat(FILE *fp, char *fmt, va_list ap)
{
	char buf[256];
	char *s;
	int c, n = 0, left, zero, width, prec, lng, base, upper, len, i;
	unsigned long uv;
	long sv;
	double dv;

	while ((c = *fmt++) != 0) {
		if (c != '%') {
			putc(c, fp);
			n++;
			continue;
		}
		left = zero = 0;
		width = 0;
		prec = -1;
		lng = 0;
		for (;;) {
			if (*fmt == '-') { left = 1; fmt++; }
			else if (*fmt == '0') { zero = 1; fmt++; }
			else break;
		}
		while (*fmt >= '0' && *fmt <= '9')
			width = width * 10 + *fmt++ - '0';
		if (*fmt == '.') {
			fmt++;
			prec = 0;
			while (*fmt >= '0' && *fmt <= '9')
				prec = prec * 10 + *fmt++ - '0';
		}
		while (*fmt == 'l' || *fmt == 'L' || *fmt == 'h') {
			lng = 1;
			fmt++;
		}
		c = *fmt++;
		base = 10;
		upper = 0;
		len = 0;
		switch (c) {
		case 'd':
		case 'i':
			sv = lng ? va_arg(ap, long) : (long)va_arg(ap, int);
			uv = sv < 0 ? (unsigned long)-sv : (unsigned long)sv;
			len = fmt_uint(buf, uv, 10, 0);
			if (sv < 0) {
				for (i = len; i >= 0; i--)
					buf[i + 1] = buf[i];
				buf[0] = '-';
				len++;
			}
			break;
		case 'D':
			sv = va_arg(ap, long);
			uv = sv < 0 ? (unsigned long)-sv : (unsigned long)sv;
			len = fmt_uint(buf, uv, 10, 0);
			if (sv < 0) {
				for (i = len; i >= 0; i--)
					buf[i + 1] = buf[i];
				buf[0] = '-';
				len++;
			}
			break;
		case 'u':
		case 'U':
			uv = lng ? va_arg(ap, unsigned long)
				 : (unsigned long)va_arg(ap, unsigned);
			len = fmt_uint(buf, uv, 10, 0);
			break;
		case 'o':
		case 'O':
			uv = lng ? va_arg(ap, unsigned long)
				 : (unsigned long)va_arg(ap, unsigned);
			len = fmt_uint(buf, uv, 8, 0);
			break;
		case 'x':
		case 'X':
			uv = lng ? va_arg(ap, unsigned long)
				 : (unsigned long)va_arg(ap, unsigned);
			len = fmt_uint(buf, uv, 16, c == 'X');
			break;
		case 'c':
			buf[0] = va_arg(ap, int);
			len = 1;
			break;
		case 's':
			s = va_arg(ap, char *);
			if (s == 0)
				s = "(null)";
			len = strlen(s);
			if (prec >= 0 && len > prec)
				len = prec;
			n += emit(fp, s, len, width, left, 0);
			continue;
		case 'f':
		case 'e':
		case 'E':
		case 'g':
		case 'G':
			dv = va_arg(ap, double);
			len = fmt_float(buf, dv, prec, c);
			break;
		case '%':
			buf[0] = '%';
			len = 1;
			break;
		default:
			buf[0] = c;
			len = 1;
			break;
		}
		n += emit(fp, buf, len, width, left, zero);
		(void)base;
		(void)upper;
	}
	return n;
}

int
printf(char *fmt, ...)
{
	va_list ap;
	int n;

	va_start(ap, fmt);
	n = vformat(stdout, fmt, ap);
	va_end(ap);
	return n;
}

int
fprintf(FILE *fp, char *fmt, ...)
{
	va_list ap;
	int n;

	va_start(ap, fmt);
	n = vformat(fp, fmt, ap);
	va_end(ap);
	return n;
}

char *
sprintf(char *str, char *fmt, ...)
{
	va_list ap;
	FILE f;

	f._flag = _IOWRT | _IOSTRG;
	f._ptr = str;
	f._cnt = 32767;
	f._base = str;
	f._file = -1;
	va_start(ap, fmt);
	vformat(&f, fmt, ap);
	va_end(ap);
	*f._ptr = 0;
	return str;
}
