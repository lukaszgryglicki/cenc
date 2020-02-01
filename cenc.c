#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int dialect(int c) {
  int u;
  u = 0;
  if (c >= '0' && c <= '9') {
    switch(c) {
      case '0':
        return '0';
      case '1':
        return '2';
      case '2':
        return '4';
      case '3':
        return '8';
      case '4':
        return '6';
      case '5':
        return '3';
      case '6':
        return '5';
      case '7':
        return '9';
      case '8':
        return '7';
      case '9':
        return '1';
    }
  }
  if (c >= 'A' && c <= 'Z') {
    c += 0x20;
    u = 1;
  }
  if (c >= 'a' && c <= 'z') {
    switch(c) {
      case 'a':
        c = 's';
        break;
      case 'b':
        c = 'n';
        break;
      case 'c':
        c = 'v';
        break;
      case 'd':
        c = 'f';
        break;
      case 'e':
        c = 'y';
        break;
      case 'f':
        c = 'g';
        break;
      case 'g':
        c = 'h';
        break;
      case 'h':
        c = 'j';
        break;
      case 'i':
        c = 'o';
        break;
      case 'j':
        c = 'k';
        break;
      case 'k':
        c = 'l';
        break;
      case 'l':
        c = 'a';
        break;
      case 'm':
        c = 'z';
        break;
      case 'n':
        c = 'm';
        break;
      case 'o':
        c = 'e';
        break;
      case 'p':
        c = 'q';
        break;
      case 'q':
        c = 'w';
        break;
      case 'r':
        c = 't';
        break;
      case 's':
        c = 'd';
        break;
      case 't':
        c = 'p';
        break;
      case 'u':
        c = 'i';
        break;
      case 'v':
        c = 'b';
        break;
      case 'w':
        c = 'r';
        break;
      case 'x':
        c = 'c';
        break;
      case 'y':
        c = 'u';
        break;
      case 'z':
        c = 'x';
        break;
    }
    if (u == 1) {
      c -= 0x20;
    }
  }
  return c;
}

int shift(int c) {
  int u;
  u = 0;
  if (c >= '0' && c <= '9') {
    switch(c) {
      case '0':
        return '1';
      case '1':
        return '2';
      case '2':
        return '3';
      case '3':
        return '4';
      case '4':
        return '5';
      case '5':
        return '6';
      case '6':
        return '7';
      case '7':
        return '8';
      case '8':
        return '9';
      case '9':
        return '0';
    }
  }
  if (c >= 'A' && c <= 'Z') {
    c += 0x20;
    u = 1;
  }
  if (c >= 'a' && c <= 'z') {
    switch(c) {
      case 'a':
        c = 's';
        break;
      case 'b':
        c = 'n';
        break;
      case 'c':
        c = 'v';
        break;
      case 'd':
        c = 'f';
        break;
      case 'e':
        c = 'r';
        break;
      case 'f':
        c = 'g';
        break;
      case 'g':
        c = 'h';
        break;
      case 'h':
        c = 'j';
        break;
      case 'i':
        c = 'o';
        break;
      case 'j':
        c = 'k';
        break;
      case 'k':
        c = 'l';
        break;
      case 'l':
        c = 'a';
        break;
      case 'm':
        c = 'z';
        break;
      case 'n':
        c = 'm';
        break;
      case 'o':
        c = 'p';
        break;
      case 'p':
        c = 'q';
        break;
      case 'q':
        c = 'w';
        break;
      case 'r':
        c = 't';
        break;
      case 's':
        c = 'd';
        break;
      case 't':
        c = 'y';
        break;
      case 'u':
        c = 'i';
        break;
      case 'v':
        c = 'b';
        break;
      case 'w':
        c = 'e';
        break;
      case 'x':
        c = 'c';
        break;
      case 'y':
        c = 'u';
        break;
      case 'z':
        c = 'x';
        break;
    }
    if (u == 1) {
      c -= 0x20;
    }
  }
  return c;
}

int next(int c) {
  int u;
  u = 0;
  if (c >= '0' && c <= '8') {
    c ++;
    return c;
  }
  if (c == '9') {
    return '0';
  }
  if (c >= 'A' && c <= 'Z') {
    c += 0x20;
    u = 1;
  }
  if (c >= 'a' && c <= 'y') {
    c ++;
    if (u == 1) {
      c -= 0x20;
    }
    return c;
  }
  if (c == 'z') {
    c = 'a';
    if (u == 1) {
      c -= 0x20;
    }
    return c;
  }
  return c;
}

int main() {
  int c;
  int (*f)(int);
  char* s;
  f = &next;
  s = getenv("F");
  if (s) {
    if (!strcmp(s, "d")) {
      f = &dialect;
    } else if (!strcmp(s, "s")) {
      f = &shift;
    }
  }
  while ((c = fgetc(stdin)) != EOF) {
    c = f(c);
    fputc(c, stdout);
  }
  return 0;
}
