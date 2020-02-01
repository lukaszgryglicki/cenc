#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>

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

void getpass(char *password) {
  static struct termios old, new;
  tcgetattr(0, &old);
  new = old;
  new.c_lflag &= ~(ECHO);
  tcsetattr(0, TCSANOW, &new);
  if (fgets(password, BUFSIZ, stdin) == NULL) {
    password[0] = '\0';
  } else {
    password[strlen(password)-1] = '\0';
  }
  tcsetattr(0, TCSANOW, &old);
}

int main(int argc, char** argv) {
  int c, i, j, l, n, fin;
  int (*f)(int);
  char *s, *cs;
  unsigned int *pass, p;
  FILE* in;
  in = stdin;
  s = getenv("PASS");
  if (!s || (s && !strcmp(s, ""))) {
    if (!s) {
      printf("password: ");
      s = (char*)malloc(BUFSIZ*sizeof(char));
      getpass(s);
      printf("\n");
    } else {
      strcpy(s, "1");
    }
  }
  l = strlen(s);
  pass = (unsigned int*)malloc(l*sizeof(unsigned int));
  cs = (char*)malloc(2*sizeof(char));
  cs[1] = 0;
  for (i=0;i<l;i++) {
    cs[0] = s[i];
    n = sscanf(cs, "%x", &p);
    if (n == 0) {
      printf("non-hex character #%d '%c' in %s\n", i, s[i], s);
      return 1;
    }
    pass[i] = p;
  }
  f = &dialect;
  s = getenv("F");
  if (s) {
    if (!strcmp(s, "s")) {
      f = &shift;
    } else if (!strcmp(s, "n")) {
      f = &next;
    }
  }
  i = 0;
  fin = 0;
  if (argc > 1) {
    in = fopen(argv[1], "r");
    if (!in) {
      printf("cannot open file: %s\n", argv[1]);
      return 2;
    }
    fin = 1;
  }
  while ((c = fgetc(in)) != EOF) {
    n = pass[i];
    for (j=0;j<n;j++) {
      c = f(c);
    }
    i ++;
    if (i == l) {
      i = 0;
    }
    fputc(c, stdout);
  }
  if (fin == 1) {
    fclose(in);
  }
  return 0;
}
