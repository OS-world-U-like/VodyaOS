/*
 * V7 formatted input for x86_64.
 * The historical doscan.c took the address of its variadic argument,
 * which is not portable to the System V ABI.  This is a compact
 * va_list-based replacement covering the formats used by V7 code.
 */

#include <stdio.h>

typedef __builtin_va_list va_list;
#define va_start(ap, last)	__builtin_va_start(ap, last)
#define va_arg(ap, type)	__builtin_va_arg(ap, type)
#define va_end(ap)		__builtin_va_end(ap)

extern int strlen(char *);

static int
scan_skip(FILE *fp)
{
	int c;

	do {
		c = getc(fp);
	} while (c == ' ' || c == '\t' || c == '\n' || c == '\r' ||
		 c == '\f' || c == '\v');
	return c;
}

static int
scan_long(FILE *fp, int base, long *out)
{
	int c, neg = 0, any = 0;
	unsigned long v = 0;
	int d;

	c = scan_skip(fp);
	if (c == '-' || c == '+') {
		neg = (c == '-');
		c = getc(fp);
	}
	for (;;) {
		if (c >= '0' && c <= '9') d = c - '0';
		else if (c >= 'a' && c <= 'z') d = c - 'a' + 10;
		else if (c >= 'A' && c <= 'Z') d = c - 'A' + 10;
		else break;
		if (d >= base) break;
		v = v * base + d;
		any = 1;
		c = getc(fp);
	}
	if (c != EOF)
		ungetc(c, fp);
	if (!any)
		return 0;
	*out = neg ? -(long)v : (long)v;
	return 1;
}

static int
scan_double(FILE *fp, double *out)
{
	int c, neg = 0, any = 0;
	double v = 0.0, scale = 1.0;
	int div = 0;

	c = scan_skip(fp);
	if (c == '-' || c == '+') {
		neg = (c == '-');
		c = getc(fp);
	}
	while (c >= '0' && c <= '9') {
		v = v * 10.0 + (c - '0');
		any = 1;
		c = getc(fp);
	}
	if (c == '.') {
		c = getc(fp);
		div = 1;
		while (c >= '0' && c <= '9') {
			scale /= 10.0;
			v += (c - '0') * scale;
			any = 1;
			c = getc(fp);
		}
	}
	(void)div;
	if (c != EOF)
		ungetc(c, fp);
	if (!any)
		return 0;
	*out = neg ? -v : v;
	return 1;
}

static int
vscan(FILE *fp, char *fmt, va_list ap)
{
	int c, n = 0, width, suppress, lng, base, i;
	char *s;
	long lv;
	double dv;

	while ((c = *fmt++) != 0) {
		if (c == ' ' || c == '\t' || c == '\n') {
			c = scan_skip(fp);
			if (c != EOF)
				ungetc(c, fp);
			continue;
		}
		if (c != '%') {
			c = getc(fp);
			if (c != fmt[-1]) {
				if (c != EOF)
					ungetc(c, fp);
				break;
			}
			continue;
		}
		suppress = 0;
		width = 0;
		lng = 0;
		if (*fmt == '*') { suppress = 1; fmt++; }
		while (*fmt >= '0' && *fmt <= '9')
			width = width * 10 + *fmt++ - '0';
		while (*fmt == 'l' || *fmt == 'L' || *fmt == 'h') {
			lng = 1;
			fmt++;
		}
		c = *fmt++;
		base = 10;
		switch (c) {
		case 'd':
			if (!scan_long(fp, 10, &lv)) return n;
			if (!suppress) {
				if (lng) *va_arg(ap, long *) = lv;
				else *va_arg(ap, int *) = (int)lv;
				n++;
			}
			break;
		case 'o':
		case 'O':
			if (!scan_long(fp, 8, &lv)) return n;
			if (!suppress) {
				if (lng) *va_arg(ap, long *) = lv;
				else *va_arg(ap, int *) = (int)lv;
				n++;
			}
			break;
		case 'x':
		case 'X':
			if (!scan_long(fp, 16, &lv)) return n;
			if (!suppress) {
				if (lng) *va_arg(ap, long *) = lv;
				else *va_arg(ap, int *) = (int)lv;
				n++;
			}
			break;
		case 'u':
			if (!scan_long(fp, 10, &lv)) return n;
			if (!suppress) {
				if (lng) *va_arg(ap, unsigned long *) = (unsigned long)lv;
				else *va_arg(ap, unsigned *) = (unsigned)lv;
				n++;
			}
			break;
		case 'f':
		case 'e':
		case 'g':
			if (!scan_double(fp, &dv)) return n;
			if (!suppress) {
				if (lng) *va_arg(ap, double *) = dv;
				else *va_arg(ap, float *) = (float)dv;
				n++;
			}
			break;
		case 'c':
			c = getc(fp);
			if (c == EOF) return n;
			if (!suppress) {
				*va_arg(ap, char *) = c;
				n++;
			}
			break;
		case 's':
			c = scan_skip(fp);
			if (c == EOF) return n;
			s = va_arg(ap, char *);
			i = 0;
			while (c != EOF && c != ' ' && c != '\t' && c != '\n' &&
			       c != '\r' && c != '\f' && c != '\v') {
				if (width && i >= width) {
					ungetc(c, fp);
					break;
				}
				if (!suppress)
					s[i++] = c;
				c = getc(fp);
			}
			if (c != EOF && (width == 0 || i < width))
				ungetc(c, fp);
			if (!suppress) {
				s[i] = 0;
				n++;
			}
			break;
		case '%':
			c = getc(fp);
			if (c != '%') {
				if (c != EOF) ungetc(c, fp);
				return n;
			}
			break;
		default:
			return n;
		}
	}
	return n;
}

int
scanf(char *fmt, ...)
{
	va_list ap;
	int n;

	va_start(ap, fmt);
	n = vscan(stdin, fmt, ap);
	va_end(ap);
	return n;
}

int
fscanf(FILE *fp, char *fmt, ...)
{
	va_list ap;
	int n;

	va_start(ap, fmt);
	n = vscan(fp, fmt, ap);
	va_end(ap);
	return n;
}

int
sscanf(char *str, char *fmt, ...)
{
	va_list ap;
	FILE f;
	int n;

	f._flag = _IOREAD | _IOSTRG;
	f._ptr = str;
	f._cnt = strlen(str);
	f._base = str;
	f._file = -1;
	va_start(ap, fmt);
	n = vscan(&f, fmt, ap);
	va_end(ap);
	return n;
}
